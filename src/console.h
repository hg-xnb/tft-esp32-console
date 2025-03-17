#include "mod_libs/TFT_22_ILI9225.h"

#ifndef TFT_RST_PIN
    /// @note RST pin im TFT <-> GPIO2 is default
    #define TFT_RST_PIN 2
#endif

#ifndef TFT_RS_PIN
    #define TFT_RS_PIN 4
#endif

#ifndef SPI_BUS_TYPE
    #define SPI_BUS_TYPE HSPI
#endif

SPIClass spi_obj(SPI_BUS_TYPE);

TFT_22_ILI9225 tft_screen(TFT_RST_PIN, TFT_RS_PIN, (int8_t) 15, (int8_t) 0, (uint8_t) 255);

void init_tft_screen(){
    spi_obj.begin();
    tft_screen.begin(spi_obj);
    tft_screen.setOrientation(0);
}

/// CONSOLE ------------------------------------------------------------------------ ///

/// make a canvas
uint16_t const maxX=220, maxY=178, background_color = 0x0;
uint16_t xpp = 0, ypp = 0; /// pp : print pointer

#include <vector>

std::vector<std::vector<bool>>canvas(maxX, std::vector<bool>(maxY, 0)),
                                  old_canvas(maxX, std::vector<bool>(maxY, 0));

/// flags
enum print_pointer_flags {
    xpp_INCR=0x1, ypp_INCR=0x2, xpp_DECR=0x4, ypp_DECR=0x8,
    OUT_OF_RANGE=0x10, NO_CHANGED=0x20
}; 
enum tft_screen_flags {
    CLEARED_SCREEN=0x1, SCREEN_SHIFTED_UP=0x2, NOT_SHIFTED_UP=0x4
}; 

/// macros
#define __set_flag(flag) |= (flag)
#define __remove_flag(flag) &= (~(flag))
#define __has_flag(flag) & (flag)
#define __forall_x_in(__min_x, __max_x) for(uint16_t x=(__min_x); x <= (__max_x); ++x )
#define __forall_y_in(__min_y, __max_y) for(uint16_t y=(__min_y); y <= (__max_y); ++y )

///  functions

inline void print_pixel(uint16_t x, uint16_t y, uint16_t print_color = background_color){
    tft_screen.drawPixel(y, x, print_color);
}

void clear_canvas(uint16_t reset_color = background_color){
    __forall_x_in(0, maxX-1){
        __forall_y_in(0, maxY-1){
            canvas[x][y] = reset_color;
        }
    }
}

void show_canvas(bool full = false){
    __forall_x_in(0, maxX-1){
        __forall_y_in(0, maxY-1){
            if(full)
                print_pixel(x, y, canvas[x][y]?0xFFFF:0x0);
            else
                if(old_canvas[x][y] != canvas[x][y]){
                    print_pixel(x, y, canvas[x][y]?0xFFFF:0x0);
                    old_canvas[x][y] = canvas[x][y];
                }
        }
    }
}

uint16_t shift_screen_up(uint16_t shifted_pixels = 1, uint16_t reset_color = background_color){
    if(shifted_pixels == 0) return NOT_SHIFTED_UP;
    if(shifted_pixels >= maxX){
        clear_canvas();
        return CLEARED_SCREEN;
    }
    __forall_x_in(0, maxX-shifted_pixels-1)
        __forall_y_in(0, maxY-1)
            canvas[x][y] = canvas[x+shifted_pixels][y];

    __forall_x_in(maxX-shifted_pixels, maxX-1)
        __forall_y_in(0, maxY-1)
            canvas[x][y] = reset_color;

    return SCREEN_SHIFTED_UP;
}

uint16_t set_print_pointer(uint16_t x, uint16_t y){
    uint16_t status = 0x0;
    if(x >= maxX){
        status __set_flag(OUT_OF_RANGE | xpp_INCR);
    }else{
        xpp = x;
    }
    if(y >= maxY){
        status __set_flag(OUT_OF_RANGE | ypp_INCR);
    }else{
        ypp = y;
    }
    return status;
}

void reset_print_pointer(){
    xpp=ypp=0;
}

uint16_t xpp_incr(uint16_t amount = 1){
    if(amount == 0) return NO_CHANGED;
    if(xpp+amount >= maxX) {
        return OUT_OF_RANGE;
    }
    xpp+=amount;
    return 0x0;
}

uint16_t xpp_decr(uint16_t amount = 1){
    if(amount == 0) return NO_CHANGED;
    if(xpp == 0){
        return OUT_OF_RANGE;
    }
    xpp-=amount;
    return 0x0;
}


uint16_t ypp_incr(uint16_t amount = 1){
    if(amount == 0) return NO_CHANGED;
    if(ypp+amount >= maxY) {
        return OUT_OF_RANGE;
    }
    ypp+=amount;
    return 0x0;
}

uint16_t ypp_decr(uint16_t amount = 1){
    if(amount == 0) return NO_CHANGED;
    if(xpp == 0){
        return OUT_OF_RANGE;
    }
    xpp-=amount;
    return 0x0;
}

const uint16_t max_char_per_line = 32, row_gap = 9;

uint16_t print_char(char c, uint16_t pp_shift_flag = ypp_INCR, uint16_t text_color = 0xFFFF) {
    
    if( c == '\n')
        return set_print_pointer(xpp+row_gap, 0);
    if( c == '\r')
        return set_print_pointer(xpp, 0);

    uint16_t status = 0x0;

    if (c < 32 || c > 127) {
        c = '?';
        status __set_flag(OUT_OF_RANGE);
    }

    int charIndex = c - 32;                     // Offset from ASCII 32 (space)
    int offset = 4 + charIndex * 7;             // Skip 4-byte header, assume 7 bytes per char
    uint8_t byteCount = Terminal6x8[offset];    // Number of bytes for this char

    if (xpp + 8 >= maxX || ypp + byteCount - 1 >= maxY) {
        return OUT_OF_RANGE | pp_shift_flag;
    }

    for (int col = 1; col <= byteCount; col++) {
        uint8_t column = Terminal6x8[offset + col];
        for (int row = 0; row < 8; row++) {
            if (column & (1 << row)) {
                canvas[xpp + row][ypp + col-1] = text_color;
            }
        }
    }
    if (pp_shift_flag __has_flag(xpp_INCR)) status |= xpp_incr(8); 
    if (pp_shift_flag __has_flag(ypp_INCR)) status |= ypp_incr(byteCount); 
    if (pp_shift_flag __has_flag(xpp_DECR)) status |= xpp_decr(8);
    if (pp_shift_flag __has_flag(ypp_DECR)) status |= ypp_decr(byteCount);

    return status;
}

uint16_t print_string(String text, bool wrap_text = false){
    for(uint16_t i = 0; i < text.length(); ++i){
        if(xpp + row_gap >= maxX){
            shift_screen_up(row_gap, background_color);
            set_print_pointer(xpp-row_gap, 0);
        }
        if(ypp+9 <= maxY){
            print_char(text.charAt(i));
        }else{
            if(wrap_text){
                if(xpp_incr(row_gap) __has_flag(OUT_OF_RANGE)){
                    shift_screen_up(row_gap, background_color);
                    set_print_pointer(xpp-row_gap, 0);
                    print_char(text.charAt(i));
                    continue;
                }
                set_print_pointer(xpp, 0);
                print_char(text.charAt(i));
            }else{
                set_print_pointer(xpp, 0);
                return OUT_OF_RANGE;
            }
        }
    }
    return 0;
}

template<class Tvalue>
String __concat_all(Tvalue value){
    return String(value);
}

template<class Tvalue, class... Tvalues>
String __concat_all(Tvalue value, Tvalues... values){
    String res = String(value);
    res.concat(__concat_all(values...));
    return res;
}

template<class... Tmsgs>
void log2screen(Tmsgs... msgs){
    print_string(__concat_all("[", millis(), "] ", msgs...), true);
    print_char('\n');
    show_canvas(); 
}
