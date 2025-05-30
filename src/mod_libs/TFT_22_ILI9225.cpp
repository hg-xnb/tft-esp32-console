#include "TFT_22_ILI9225.h"

//#define DEBUG
#ifdef DEBUG
    #define DB_PRINT( ... ) { char dbgbuf[60]; sprintf( dbgbuf,   __VA_ARGS__ ) ; Serial.println( dbgbuf ); }
#else
    #define DB_PRINT(  ... ) ;
#endif

#ifndef ARDUINO_STM32_FEATHER
    #include "pins_arduino.h"
    #ifndef RASPI
        #include "wiring_private.h"
    #endif
#endif
#include <limits.h>
#ifdef __AVR__
    #include <avr/pgmspace.h>
#elif defined(ESP8266) || defined(ESP32)
    #include <pgmspace.h>
#endif

// Many (but maybe not all) non-AVR board installs define macros
// for compatibility with existing PROGMEM-reading AVR code.
// Do our own checks and defines here for good measure...

#ifndef pgm_read_byte
    #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
    #define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
    #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#endif

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
    #define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
#else
    #define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
#endif

// Control pins

#ifdef USE_FAST_PINIO
    #define SPI_DC_HIGH()           *dcport |=  dcpinmask
    #define SPI_DC_LOW()            *dcport &= ~dcpinmask
    #define SPI_CS_HIGH()           *csport |=  cspinmask
    #define SPI_CS_LOW()            *csport &= ~cspinmask
#else
    #define SPI_DC_HIGH()           digitalWrite(_rs, HIGH)
    #define SPI_DC_LOW()            digitalWrite(_rs, LOW)
    #define SPI_CS_HIGH()           digitalWrite(_cs, HIGH)
    #define SPI_CS_LOW()            digitalWrite(_cs, LOW)
#endif

// Software SPI Macros

#ifdef USE_FAST_PINIO
    #define SSPI_MOSI_HIGH()        *mosiport |=  mosipinmask
    #define SSPI_MOSI_LOW()         *mosiport &= ~mosipinmask
    #define SSPI_SCK_HIGH()         *clkport |=  clkpinmask
    #define SSPI_SCK_LOW()          *clkport &= ~clkpinmask
#else
    #define SSPI_MOSI_HIGH()        digitalWrite(_sdi, HIGH)
    #define SSPI_MOSI_LOW()         digitalWrite(_sdi, LOW)
    #define SSPI_SCK_HIGH()         digitalWrite(_clk, HIGH)
    #define SSPI_SCK_LOW()          digitalWrite(_clk, LOW)
#endif

#define SSPI_BEGIN_TRANSACTION()
#define SSPI_END_TRANSACTION()
#define SSPI_WRITE(v)               _spiWrite(v)
#define SSPI_WRITE16(s)             SSPI_WRITE((s) >> 8); SSPI_WRITE(s)
#define SSPI_WRITE32(l)             SSPI_WRITE((l) >> 24); SSPI_WRITE((l) >> 16); SSPI_WRITE((l) >> 8); SSPI_WRITE(l)
#define SSPI_WRITE_PIXELS(c,l)      for(uint32_t i=0; i<(l); i+=2){ SSPI_WRITE(((uint8_t*)(c))[i+1]); SSPI_WRITE(((uint8_t*)(c))[i]); }

// Hardware SPI Macros
#ifndef ESP32
    #ifdef SPI_CHANNEL
        extern SPIClass SPI_CHANNEL; 
        #define SPI_OBJECT  SPI_CHANNEL
    #else
        #define SPI_OBJECT  SPI
    #endif
#else
    #define SPI_OBJECT  _spi
#endif

#if defined (__AVR__) || defined(TEENSYDUINO) || defined(ARDUINO_ARCH_STM32F1)
    #define HSPI_SET_CLOCK() SPI_OBJECT.setClockDivider(SPI_CLOCK_DIV2);
#elif defined (__arm__)
    #define HSPI_SET_CLOCK() SPI_OBJECT.setClockDivider(11);
#elif defined(ESP8266) || defined(ESP32)
    #define HSPI_SET_CLOCK() SPI_OBJECT.setFrequency(SPI_DEFAULT_FREQ);
#elif defined(RASPI)
    #define HSPI_SET_CLOCK() SPI_OBJECT.setClock(SPI_DEFAULT_FREQ);
#elif defined(ARDUINO_ARCH_STM32F1)
    #define HSPI_SET_CLOCK() SPI_OBJECT.setClock(SPI_DEFAULT_FREQ);
#else
    #define HSPI_SET_CLOCK()
#endif

#ifdef SPI_HAS_TRANSACTION
    #define HSPI_BEGIN_TRANSACTION() SPI_OBJECT.beginTransaction(SPISettings(SPI_DEFAULT_FREQ, MSBFIRST, SPI_MODE0))
    #define HSPI_END_TRANSACTION()   SPI_OBJECT.endTransaction()
#else
    #define HSPI_BEGIN_TRANSACTION() HSPI_SET_CLOCK(); SPI_OBJECT.setBitOrder(MSBFIRST); SPI_OBJECT.setDataMode(SPI_MODE0)
    #define HSPI_END_TRANSACTION()
#endif

#ifdef ESP32
    #define SPI_HAS_WRITE_PIXELS
#endif
#if defined(ESP8266) || defined(ESP32)
    // Optimized SPI (ESP8266 and ESP32)
    #define HSPI_READ()              SPI_OBJECT.transfer(0)
    #define HSPI_WRITE(b)            SPI_OBJECT.write(b)
    #define HSPI_WRITE16(s)          SPI_OBJECT.write16(s)
    #define HSPI_WRITE32(l)          SPI_OBJECT.write32(l)
    #ifdef SPI_HAS_WRITE_PIXELS
        #define SPI_MAX_PIXELS_AT_ONCE  32
        #define HSPI_WRITE_PIXELS(c,l)   SPI_OBJECT.writePixels(c,l)
    #else
        #define HSPI_WRITE_PIXELS(c,l)   for(uint32_t i=0; i<((l)/2); i++){ HSPI_WRITE16(((uint16_t*)(c))[i]); }
    #endif
#elif defined ( __STM32F1__ )
    #define HSPI_WRITE(b)            SPI_OBJECT.write(b)
    #define HSPI_WRITE16(s)          SPI_OBJECT.write16(s)

#else
    // Standard Byte-by-Byte SPI

    #if defined(__AVR_ATmega4809__)
    static inline uint8_t _avr_spi_read(void) __attribute__((always_inline));
    static inline uint8_t _avr_spi_read(void) {
        uint8_t r = 0;
        SPI0_DATA = r;
        while(!(SPI0_INTFLAGS & _BV(SPI_IF_bp)));
        r = SPI0_DATA;
        return r;
    }
        #define HSPI_WRITE(b)        {SPI0_DATA = (b); while(!(SPI0_INTFLAGS & _BV(SPI_IF_bp)));}
        // #define HSPI_READ()          _avr_spi_read()
    #elif defined (__AVR__) || defined(TEENSYDUINO)
        static inline uint8_t _avr_spi_read(void) __attribute__((always_inline));
        static inline uint8_t _avr_spi_read(void) {
            uint8_t r = 0;
            SPDR = r;
            while(!(SPSR & _BV(SPIF)));
            r = SPDR;
            return r;
        }
        #define HSPI_WRITE(b)        {SPDR = (b); while(!(SPSR & _BV(SPIF)));}
        // #define HSPI_READ()          _avr_spi_read()
    #else
        #define HSPI_WRITE(b)        SPI_OBJECT.transfer((uint8_t)(b))
        // #define HSPI_READ()          HSPI_WRITE(0)
    #endif
    // #define HSPI_WRITE16(s)          HSPI_WRITE((s) >> 8); HSPI_WRITE(s)
    // #define HSPI_WRITE32(l)          HSPI_WRITE((l) >> 24); HSPI_WRITE((l) >> 16); HSPI_WRITE((l) >> 8); HSPI_WRITE(l)
    // #define HSPI_WRITE_PIXELS(c,l)   for(uint32_t i=0; i<(l); i+=2){ HSPI_WRITE(((uint8_t*)(c))[i+1]); HSPI_WRITE(((uint8_t*)(c))[i]); }
#endif

// Final SPI Macros

#if defined (ARDUINO_ARCH_ARC32)
    #define SPI_DEFAULT_FREQ         16000000
#elif defined (__AVR__) || defined(TEENSYDUINO)
    #define SPI_DEFAULT_FREQ         8000000
#elif defined(ESP8266) || defined(ESP32)
    #define SPI_DEFAULT_FREQ         40000000
#elif defined(RASPI)
    #define SPI_DEFAULT_FREQ         80000000
#elif defined(ARDUINO_ARCH_STM32F1)
    #define SPI_DEFAULT_FREQ         18000000
    //#define SPI_DEFAULT_FREQ         36000000
#else
    #define SPI_DEFAULT_FREQ         24000000
#endif

#define SPI_BEGIN()             if(_clk < 0){SPI_OBJECT.begin();}
#define SPI_BEGIN_TRANSACTION() if(_clk < 0){HSPI_BEGIN_TRANSACTION();}
#define SPI_END_TRANSACTION()   if(_clk < 0){HSPI_END_TRANSACTION();}
// #define SPI_WRITE16(s)          if(_clk < 0){HSPI_WRITE16(s);}else{SSPI_WRITE16(s);}
// #define SPI_WRITE32(l)          if(_clk < 0){HSPI_WRITE32(l);}else{SSPI_WRITE32(l);}
// #define SPI_WRITE_PIXELS(c,l)   if(_clk < 0){HSPI_WRITE_PIXELS(c,l);}else{SSPI_WRITE_PIXELS(c,l);}


// Constructor when using software SPI.  All output pins are configurable.
TFT_22_ILI9225::TFT_22_ILI9225(int8_t rst, int8_t rs, int8_t cs, int8_t sdi, int8_t clk, int8_t led) {
    _rst  = rst;
    _rs   = rs;
    _cs   = cs;
    _sdi  = sdi;
    _clk  = clk;
    _led  = led;
    _brightness = 255; // Set to maximum brightness
    hwSPI = false;
    writeFunctionLevel = 0;
    gfxFont = NULL;
}


// Constructor when using software SPI.  All output pins are configurable. Adds backlight brightness 0-255
TFT_22_ILI9225::TFT_22_ILI9225(int8_t rst, int8_t rs, int8_t cs, int8_t sdi, int8_t clk, int8_t led, uint8_t brightness) {
    _rst  = rst;
    _rs   = rs;
    _cs   = cs;
    _sdi  = sdi;
    _clk  = clk;
    _led  = led;
    _brightness = brightness;
    hwSPI = false;
    writeFunctionLevel = 0;
    gfxFont = NULL;
}


// Constructor when using hardware SPI.  Faster, but must use SPI pins
// specific to each board type (e.g. 11,13 for Uno, 51,52 for Mega, etc.)
TFT_22_ILI9225::TFT_22_ILI9225(int8_t rst, int8_t rs, int8_t cs, int8_t led) {
    _rst  = rst;
    _rs   = rs;
    _cs   = cs;
    _sdi  = _clk = -1;
    _led  = led;
    _brightness = 255; // Set to maximum brightness
    hwSPI = true;
    writeFunctionLevel = 0;
    gfxFont = NULL;
}


// Constructor when using hardware SPI.  Faster, but must use SPI pins
// specific to each board type (e.g. 11,13 for Uno, 51,52 for Mega, etc.)
// Adds backlight brightness 0-255
TFT_22_ILI9225::TFT_22_ILI9225(int8_t rst, int8_t rs, int8_t cs, int8_t led, uint8_t brightness) {
    _rst  = rst;
    _rs   = rs;
    _cs   = cs;
    _sdi  = _clk = -1;
    _led  = led;
    _brightness = brightness;
    hwSPI = true;
    writeFunctionLevel = 0;
    gfxFont = NULL;
}

#ifdef ESP32
void TFT_22_ILI9225::begin(SPIClass &spi)
#else
void TFT_22_ILI9225::begin()
#endif
{
#ifdef ESP32
    _spi = spi;
#endif
    // Set up reset pin
    if (_rst > 0) {
        pinMode(_rst, OUTPUT);
        digitalWrite(_rst, LOW);
    }
    // Set up backlight pin, turn off initially
    if (_led > 0) {
        pinMode(_led, OUTPUT);
        setBacklight(false);
    }

    // Control pins
    pinMode(_rs, OUTPUT);
    digitalWrite(_rs, LOW);
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);

#ifdef USE_FAST_PINIO
    csport    = portOutputRegister(digitalPinToPort(_cs));
    cspinmask = digitalPinToBitMask(_cs);
    dcport    = portOutputRegister(digitalPinToPort(_rs));
    dcpinmask = digitalPinToBitMask(_rs);
#endif

    // Software SPI
    if (_clk >= 0) {
        pinMode(_sdi, OUTPUT);
        digitalWrite(_sdi, LOW);
        pinMode(_clk, OUTPUT);
        digitalWrite(_clk, HIGH);
#ifdef USE_FAST_PINIO
        clkport     = portOutputRegister(digitalPinToPort(_clk));
        clkpinmask  = digitalPinToBitMask(_clk);
        mosiport    = portOutputRegister(digitalPinToPort(_sdi));
        mosipinmask = digitalPinToBitMask(_sdi);
        SSPI_SCK_LOW();
        SSPI_MOSI_LOW();
    } else {
        clkport     = 0;
        clkpinmask  = 0;
        mosiport    = 0;
        mosipinmask = 0;
#endif
    }

    // Hardware SPI
    SPI_BEGIN();

    // Initialization Code
    if (_rst > 0) {
        digitalWrite(_rst, HIGH); // Pull the reset pin high to release the ILI9225C from the reset status
        delay(1); 
        digitalWrite(_rst, LOW); // Pull the reset pin low to reset ILI9225
        delay(10);
        digitalWrite(_rst, HIGH); // Pull the reset pin high to release the ILI9225C from the reset status
        delay(50);
    }

    /* Start Initial Sequence */

    /* Set SS bit and direction output from S528 to S1 */
    startWrite();
    _writeRegister(ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
    _writeRegister(ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
    _writeRegister(ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
    _writeRegister(ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
    _writeRegister(ILI9225_POWER_CTRL5, 0x0000); // Set VCOMH/VCOML voltage
    endWrite();
    delay(40); 

    // Power-on sequence
    startWrite();
    _writeRegister(ILI9225_POWER_CTRL2, 0x0018); // Set APON,PON,AON,VCI1EN,VC
    _writeRegister(ILI9225_POWER_CTRL3, 0x6121); // Set BT,DC1,DC2,DC3
    _writeRegister(ILI9225_POWER_CTRL4, 0x006F); // Set GVDD   /*007F 0088 */
    _writeRegister(ILI9225_POWER_CTRL5, 0x495F); // Set VCOMH/VCOML voltage
    _writeRegister(ILI9225_POWER_CTRL1, 0x0800); // Set SAP,DSTB,STB
    endWrite();
    delay(10);
    startWrite();
    _writeRegister(ILI9225_POWER_CTRL2, 0x103B); // Set APON,PON,AON,VCI1EN,VC
    endWrite();
    delay(50);

    startWrite();
    _writeRegister(ILI9225_DRIVER_OUTPUT_CTRL, 0x011C); // set the display line number and display direction
    _writeRegister(ILI9225_LCD_AC_DRIVING_CTRL, 0x0100); // set 1 line inversion
    _writeRegister(ILI9225_ENTRY_MODE, 0x1038); // set GRAM write direction and BGR=1.
    _writeRegister(ILI9225_DISP_CTRL1, 0x0000); // Display off
    _writeRegister(ILI9225_BLANK_PERIOD_CTRL1, 0x0808); // set the back porch and front porch
    _writeRegister(ILI9225_FRAME_CYCLE_CTRL, 0x1100); // set the clocks number per line
    _writeRegister(ILI9225_INTERFACE_CTRL, 0x0000); // CPU interface
    _writeRegister(ILI9225_OSC_CTRL, 0x0D01); // Set Osc  /*0e01*/
    _writeRegister(ILI9225_VCI_RECYCLING, 0x0020); // Set VCI recycling
    _writeRegister(ILI9225_RAM_ADDR_SET1, 0x0000); // RAM Address
    _writeRegister(ILI9225_RAM_ADDR_SET2, 0x0000); // RAM Address

    /* Set GRAM area */
    _writeRegister(ILI9225_GATE_SCAN_CTRL, 0x0000); 
    _writeRegister(ILI9225_VERTICAL_SCROLL_CTRL1, 0x00DB); 
    _writeRegister(ILI9225_VERTICAL_SCROLL_CTRL2, 0x0000); 
    _writeRegister(ILI9225_VERTICAL_SCROLL_CTRL3, 0x0000); 
    _writeRegister(ILI9225_PARTIAL_DRIVING_POS1, 0x00DB); 
    _writeRegister(ILI9225_PARTIAL_DRIVING_POS2, 0x0000); 
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF); 
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000); 
    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB); 
    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000); 

    /* Set GAMMA curve */
    _writeRegister(ILI9225_GAMMA_CTRL1, 0x0000); 
    _writeRegister(ILI9225_GAMMA_CTRL2, 0x0808); 
    _writeRegister(ILI9225_GAMMA_CTRL3, 0x080A); 
    _writeRegister(ILI9225_GAMMA_CTRL4, 0x000A); 
    _writeRegister(ILI9225_GAMMA_CTRL5, 0x0A08); 
    _writeRegister(ILI9225_GAMMA_CTRL6, 0x0808); 
    _writeRegister(ILI9225_GAMMA_CTRL7, 0x0000); 
    _writeRegister(ILI9225_GAMMA_CTRL8, 0x0A00); 
    _writeRegister(ILI9225_GAMMA_CTRL9, 0x0710); 
    _writeRegister(ILI9225_GAMMA_CTRL10, 0x0710); 

    _writeRegister(ILI9225_DISP_CTRL1, 0x0012); 
    endWrite();
    delay(50); 
    startWrite();
    _writeRegister(ILI9225_DISP_CTRL1, 0x1017);
    endWrite();

    // Turn on backlight
    setBacklight(true);
    setOrientation(0);

    // Initialize variables
    // setBackgroundColor( COLOR_BLACK );

    // clear();
}


void TFT_22_ILI9225::_spiWrite(uint8_t b) {
    if (_clk < 0) {
        HSPI_WRITE(b);
        return;
    }
    // Fast SPI bitbang swiped from LPD8806 library
    for (uint8_t bit = 0x80; bit; bit >>= 1) {
        if ((b) & bit) {
            SSPI_MOSI_HIGH();
        } else {
            SSPI_MOSI_LOW();
        }
        SSPI_SCK_HIGH();
        SSPI_SCK_LOW();
    }
}


void TFT_22_ILI9225::_spiWrite16(uint16_t s) {
    // Attempt to use HSPI_WRITE16 if available
#ifdef HSPI_WRITE16
    if (_clk < 0) {
        HSPI_WRITE16(s);
        return;
    }
#endif
    // Fallback to SSPI_WRITE16 if HSPI_WRITE16 not available
    SSPI_WRITE16(s);
}


void TFT_22_ILI9225::_spiWriteCommand(uint8_t c) {
    SPI_DC_LOW();
    SPI_CS_LOW();
    _spiWrite(c);
    SPI_CS_HIGH();
}


void TFT_22_ILI9225::_spiWriteData(uint8_t c) {
    SPI_DC_HIGH();
    SPI_CS_LOW();
    _spiWrite(c);
    SPI_CS_HIGH();
}


void TFT_22_ILI9225::_orientCoordinates(uint16_t &x1, uint16_t &y1) {

    switch (_orientation) {
        case 0:  // ok
            break;
        case 1: // ok
            y1 = _maxY - y1 - 1;
            _swap(x1, y1);
            break;
        case 2: // ok
            x1 = _maxX - x1 - 1;
            y1 = _maxY - y1 - 1;
            break;
        case 3: // ok
            x1 = _maxX - x1 - 1;
            _swap(x1, y1);
            break;
    }
}


void TFT_22_ILI9225::_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    _setWindow( x0, y0, x1, y1, TopDown_L2R ); // default for drawing characters
}


void TFT_22_ILI9225::_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, autoIncMode_t mode) {
    DB_PRINT( "setWindows( x0=%d, y0=%d, x1=%d, y1=%d, mode=%d", x0,y0,x1,y1,mode );
    
    // clip to TFT-Dimensions
    x0 = min( x0, (uint16_t) (_maxX-1) );
    x1 = min( x1, (uint16_t) (_maxX-1) );
    y0 = min( y0, (uint16_t) (_maxY-1) );
    y1 = min( y1, (uint16_t) (_maxY-1) );
    _orientCoordinates(x0, y0);
    _orientCoordinates(x1, y1);

    if (x1<x0) _swap(x0, x1);
    if (y1<y0) _swap(y0, y1);
    
    startWrite();
    // autoincrement mode
    if ( _orientation > 0 ) mode = modeTab[_orientation-1][mode];
    _writeRegister(ILI9225_ENTRY_MODE, 0x1000 | ( mode<<3) );
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1,x1);
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2,x0);

    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1,y1);
    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2,y0);
    DB_PRINT( "gedreht: x0=%d, y0=%d, x1=%d, y1=%d, mode=%d", x0,y0,x1,y1,mode );
    // starting position within window and increment/decrement direction
    switch ( mode>>1 ) {
        case 0:
            _writeRegister(ILI9225_RAM_ADDR_SET1,x1);
            _writeRegister(ILI9225_RAM_ADDR_SET2,y1);
            break;
        case 1:
            _writeRegister(ILI9225_RAM_ADDR_SET1,x0);
            _writeRegister(ILI9225_RAM_ADDR_SET2,y1);
            break;
        case 2:
            _writeRegister(ILI9225_RAM_ADDR_SET1,x1);
            _writeRegister(ILI9225_RAM_ADDR_SET2,y0);
            break;
        case 3:
            _writeRegister(ILI9225_RAM_ADDR_SET1,x0);
            _writeRegister(ILI9225_RAM_ADDR_SET2,y0);
            break;
    }
    _writeCommand16( ILI9225_GRAM_DATA_REG );

    //_writeRegister(ILI9225_RAM_ADDR_SET1,x0);
    //_writeRegister(ILI9225_RAM_ADDR_SET2,y0);

    //_writeCommand(0x00, 0x22);

    endWrite();
}


void TFT_22_ILI9225::_resetWindow() {
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF); 
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000); 
    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB); 
    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000); 

}



void TFT_22_ILI9225::invert(boolean flag) {
    startWrite();
    _writeCommand16(flag ? ILI9225C_INVON : ILI9225C_INVOFF);
    //_writeCommand(0x00, flag ? ILI9225C_INVON : ILI9225C_INVOFF);
    endWrite();
}


void TFT_22_ILI9225::setBacklight(boolean flag) {
    blState = flag;
#ifndef ESP32
    if (_led) analogWrite(_led, blState ? _brightness : 0);
#endif
}


void TFT_22_ILI9225::setBacklightBrightness(uint8_t brightness) {
    _brightness = brightness;
    setBacklight(blState);
}


void TFT_22_ILI9225::setDisplay(boolean flag) {
    if (flag) {
        startWrite();
        _writeRegister(0x00ff, 0x0000);
        _writeRegister(ILI9225_POWER_CTRL1, 0x0000);
        endWrite();
        delay(50);
        startWrite();
        _writeRegister(ILI9225_DISP_CTRL1, 0x1017);
        endWrite();
        delay(200);
    } else {
        startWrite();
        _writeRegister(0x00ff, 0x0000);
        _writeRegister(ILI9225_DISP_CTRL1, 0x0000);
        endWrite();
        delay(50);
        startWrite();
        _writeRegister(ILI9225_POWER_CTRL1, 0x0003);
        endWrite();
        delay(200);
    }
}


void TFT_22_ILI9225::setOrientation(uint8_t orientation) {

    _orientation = orientation % 4;

    switch (_orientation) {
    case 0:
        _maxX = ILI9225_LCD_WIDTH;
        _maxY = ILI9225_LCD_HEIGHT;
        break;
    case 1:
        _maxX = ILI9225_LCD_HEIGHT;
        _maxY = ILI9225_LCD_WIDTH;
        break;
    case 2:
        _maxX = ILI9225_LCD_WIDTH;
        _maxY = ILI9225_LCD_HEIGHT;
        break;
    case 3:
        _maxX = ILI9225_LCD_HEIGHT;
        _maxY = ILI9225_LCD_WIDTH;
        break;
    }
}


uint8_t TFT_22_ILI9225::getOrientation() {
    return _orientation;
}

void TFT_22_ILI9225::drawPixel(uint16_t x1, uint16_t y1, uint16_t color) {

    if((x1 >= _maxX) || (y1 >= _maxY)) return;

    _orientCoordinates(x1, y1);
    startWrite();
    _writeRegister(ILI9225_RAM_ADDR_SET1,x1);
    _writeRegister(ILI9225_RAM_ADDR_SET2,y1);
    _writeRegister(ILI9225_GRAM_DATA_REG,color);
    
    endWrite();
}


uint16_t TFT_22_ILI9225::maxX() {
    return _maxX;
}


uint16_t TFT_22_ILI9225::maxY() {
    return _maxY;
}


void TFT_22_ILI9225::_swap(uint16_t &a, uint16_t &b) {
    uint16_t w = a;
    a = b;
    b = w;
}


// Utilities

void TFT_22_ILI9225::_writeCommand16(uint16_t command) {
    SPI_DC_LOW();
    SPI_CS_LOW();
    if ( _clk < 0 ) {
# ifdef HSPI_WRITE16
        HSPI_WRITE16(command);
#else 
        HSPI_WRITE(command >> 8);
        HSPI_WRITE(0x00ff & command);
#endif
    } else {
        // Fast SPI bitbang swiped from LPD8806 library
        for (uint16_t bit = 0x8000; bit; bit >>= 1) {
            if ((command) & bit) {
                SSPI_MOSI_HIGH();
            } else {
                SSPI_MOSI_LOW();
            }
            SSPI_SCK_HIGH();
            SSPI_SCK_LOW();
        }
    }
    SPI_CS_HIGH();
}


void TFT_22_ILI9225::_writeData16(uint16_t data) {
    SPI_DC_HIGH();
    SPI_CS_LOW();
    if (_clk < 0) {
# ifdef HSPI_WRITE16
        HSPI_WRITE16(data);
#else 
        HSPI_WRITE(data >> 8);
        HSPI_WRITE(0x00ff & data);
#endif
    } else {
        // Fast SPI bitbang swiped from LPD8806 library
        for (uint16_t bit = 0x8000; bit; bit >>= 1) {
            if((data) & bit) {
                SSPI_MOSI_HIGH();
            } else {
                SSPI_MOSI_LOW();
            }
            SSPI_SCK_HIGH();
            SSPI_SCK_LOW();
        }
    }
    SPI_CS_HIGH();
}

void TFT_22_ILI9225::_writeRegister(uint16_t reg, uint16_t data) {
    _writeCommand16(reg);
    _writeData16(data);
}



// internal function for drawing bitmaps with/without transparent bg, or from ram or progmem
void TFT_22_ILI9225::_drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg, bool transparent, bool progmem,bool Xbit) {
    bool noAutoInc = false;     // Flag set when transparent pixel was 'written'
    int16_t i, j, byteWidth = (w + 7) / 8;
    int16_t wx0, wy0, wx1, wy1, wh;  // Window-position and size
	// int16_t ww;
    uint8_t byte, maskBit;
	byte = 0;
    maskBit = Xbit? 0x01:0x80;
    // adjust window hight/width to displaydimensions
    DB_PRINT( "DrawBitmap.. maxX=%d, maxY=%d", _maxX,_maxY );
    wx0 = x < 0 ? 0 : x;
    wy0 = y < 0 ? 0 : y;
    wx1 = (x + w > _maxX ?_maxX : x + w ) - 1;
    wy1 = (y + h > _maxY ?_maxY : y + h ) - 1;
    wh  = wy1 - wy0 + 1;
    // ww  = wx1 - wx0 + 1;
    _setWindow(wx0, wy0, wx1, wy1, L2R_TopDown);
    startWrite();
    for (j = y>=0?0:-y; j < (y>=0?0:-y)+wh; j++) {
        for (i = 0; i < w; i++ ) {
            if (i & 7) { 
                if ( Xbit ) byte >>=1; else byte <<= 1; 
            }
            else {
                if ( progmem ) byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
                else           byte   = bitmap[j * byteWidth + i / 8];
            }
            if ( x+i >= wx0 && x+i <= wx1 ) {
                // write only if pixel is within window
                if (byte & maskBit) {
                    if (noAutoInc) {
                        //there was a transparent area, set pixelkoordinates again
                        drawPixel(x + i, y + j, color);
                        noAutoInc = false;
                    }
                    else  { 
                        _writeData16(color);
                    }
                }
                else  {
                    if (transparent) noAutoInc = true; // no autoincrement in transparent area!
                    else _writeData16( bg);
                }
            }
        }
    }
    endWrite();
}



void TFT_22_ILI9225::startWrite(void) {
    if (writeFunctionLevel++ == 0) {
        SPI_BEGIN_TRANSACTION();
        SPI_CS_LOW();
    }
}


void TFT_22_ILI9225::endWrite(void) {
    if (--writeFunctionLevel == 0) {
        SPI_CS_HIGH();
        SPI_END_TRANSACTION();
    }
}


void TFT_22_ILI9225::getGFXCharExtent(uint8_t c, int16_t *gw, int16_t *gh, int16_t *xa) {
    uint8_t first = pgm_read_byte(&gfxFont->first),
            last  = pgm_read_byte(&gfxFont->last);
    // Char present in this font?
    if((c >= first) && (c <= last)) {
        GFXglyph *glyph = &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c - first]);
        *gw = pgm_read_byte(&glyph->width);
        *gh = pgm_read_byte(&glyph->height);
        *xa = pgm_read_byte(&glyph->xAdvance);
        // int8_t  xo = pgm_read_byte(&glyph->xOffset),
        //         yo = pgm_read_byte(&glyph->yOffset);
    }
}
