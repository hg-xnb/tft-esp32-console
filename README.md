# ```console``` for TFT 2.2" ILI9225 screen with esp32

Too lazy too write anything...

## Note

- This code has been written and compiled in Ubuntu 24.04.

## Macros

**main.cpp:**

- DHT_DAT_PIN: GPIO16
- DHTTYPE: DHT11
- PRINT_MSG/PRINT_MSG2: The logger use to print info (log2ser or log2screen or something else defined by you).
- WIFI_SSID: Your WiFi SSID
- WIFI_PWD: Your WiFi passphase
- DATABASE_URL: Your Firebase URL
- API_KEY: The API (this API in my code will removed soon :v)
- EMAIL: Firebase account (with restricted abilities).
- PASSWORD: Password of the Firebase account

**console.h:**

- TFT_RST_PIN: GPIO2 (reset pin of tft screen)
- TFT_RS_PIN: GPIO4 (register select of tft screen)
- SPI_BUS_TYPE: HSPI (type of SPI bus)

## Vars/Objs

- dht (type: `DHT`) : object to mesure the humidity and termperature via `readHumidity` and `readTemperature` method.
- tft_screen (type: `TFT_22_ILI9225`): object to control tft screen. (Note that TFT_22_ILI9225 has been modified to make it simpler).
- maxX: Max rows (start from **0**)
- maxY: Max cols (start from **0**)
- background_color: Background color (but in this version, only two color is 0xFFFF - white or 0x0 - black).
- canvas (type: `std::vector<std::vector<bool>>`): Store the screen in ESP32 before it's being shown.
- old_canvas (same type with `canvas`): store shown screen, make showing process faster in most case.

## Features

- `void clear_canvas(uint16_t reset_color = background_color)`: clear local canvas.
- `void show_canvas(bool full = false)`: Show changed canvas if `full=false`; otherwise, show all local screen.
- `uint16_t set_print_pointer(uint16_t x, uint16_t y)`: Set print pointer.
- `void reset_print_pointer()`: Reset print pointer to (0;0).
- `uint16_t print_string(String text, bool wrap_text = false)`: Print a string with wrap text feature.
- `void log2screen(Tmsgs... msgs)`: Draw text in local canvas with uptime from milis(). E.g: `[1357] Hello!`.
- `void log2screen2(Tmsgs... msgs)`: Draw text in local canvas with uptime from milis() then call `show_canvas()`.
- 

## Review

<img src="imgs/image.png" style="width:300px;" alt="img">
