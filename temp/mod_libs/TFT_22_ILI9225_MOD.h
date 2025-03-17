#ifndef TFT_22_ILI9225_MOD_H
#define TFT_22_ILI9225_MOD_H

#if SHOW_AUTHOR_MESSAGE == true
    #pragma message("\nIncluded TFT_22_ILI9225_MOD.h!\n")
#endif

#include <SPI.h>
#include "TFT_22_ILI9225.h"

#ifndef CUSTOM_FONT
#include "fonts/FreeSerif9pt7b.h"
#define CUSTOM_FONT FreeSerif9pt7b
#endif

#ifndef TFT_RST_PIN
/// @note RST pin im TFT <-> GPIO2 is default
#define TFT_RST_PIN 2
#endif

#ifndef TFT_RS_PIN
/// @note RS pin im TFT <-> GPIO4 is default
#define TFT_RS_PIN 4
#endif

#ifndef SPI_BUS_TYPE
/// @note Set #define SPI_BUS_TYPE before include TFT_22_ILI9225_MOD.h
/// to change SPI_BUS_TYPE.
/// @note Check2 your physical board, normally, there are two type is vspi and hspi.
#define SPI_BUS_TYPE HSPI
#endif

/// @note An SPI object to using SPI communication.
SPIClass spi_obj(SPI_BUS_TYPE);

/// @brief The modified of TFT_22_ILI9225 to add somes functions (drawimage, quick add text)
class TFT_22_ILI9225_MOD : public TFT_22_ILI9225
{
private:
    /// none :v
public:

    /// Declare new TFT_22_ILI9225_MOD object
    /// @note Using default pin for HSPI :
    /// @note HSPI-CLK <-> (GPIO14)
    /// @note HSPI-MOSI <-> (GPIO13)
    /// @note HSPI-CS <-> (GPIO15)
    /// @note The type of pin must be <int8_t>.
    TFT_22_ILI9225_MOD()
    :TFT_22_ILI9225(TFT_RST_PIN, TFT_RS_PIN, (int8_t) 15, (int8_t) 0, (uint8_t) 255)
    {
        spi_obj.begin();
        /// hehe :v
    }

    /// Declare new TFT_22_ILI9225_MOD object
    /// @param rst RST pin, any available GPIO 
    /// @param rs  RS pin, any available GPIO 
    /// @note Using default pin for HSPI :
    /// @note HSPI-CLK <-> (GPIO14)
    /// @note HSPI-MOSI <-> (GPIO13)
    /// @note HSPI-CS <-> (GPIO15)
    /// @note The type of pin must be <int8_t>.
    TFT_22_ILI9225_MOD(int8_t rst, int8_t rs)
    :TFT_22_ILI9225(rst, rs, (int8_t) 15, (int8_t) 0, (uint8_t) 255)
    {
        spi_obj.begin();
        /// hehe :v
    }

    /// Declare new TFT_22_ILI9225_MOD object
    /// @param rst RST pin, any available GPIO 
    /// @param rs  RS pin, any available GPIO 
    /// @param cs  RS pin, any available GPIO 
    /// @param others more pins paramerters can be declared, check the original header to know!
    template<class... Tpins>
    TFT_22_ILI9225_MOD(int8_t rst, int8_t rs, int8_t cs, Tpins... others )
    :TFT_22_ILI9225(rst, rs, cs, others...)
    {
        spi_obj.begin();
    }

    /// Initial tft
    /// @param Orientation orientation, 0=portrait, 1=right rotated landscape, 2=reverse portrait, 3=left rotated landscape
    /// @param BackgroundColor BackgroundColor,16bit-color to set the color of background
    void begin(
        uint8_t Orientation = 0,
        uint16_t BackgroundColor = 0x0
    )
    {
        spi_obj.begin();
        TFT_22_ILI9225::begin(spi_obj);
        // TFT_22_ILI9225::setGFXFont(&CUSTOM_FONT);
        // TFT_22_ILI9225::setBackgroundColor(BackgroundColor);
        TFT_22_ILI9225::setOrientation(Orientation);
        TFT_22_ILI9225::clear();
    }

};



#endif