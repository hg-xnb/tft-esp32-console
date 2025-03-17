## Hi!
This mod version of TFT_22_ILI9225.h is dev for quick draw an image with color-array in stead of bit-map. In my point of view, it will easyer for start or understand (or not). I also add draw line text function to quick draw a line in TFT screen.
## Changed
- Add function has been dev with Orientation=0 (or 2)
- By default, HSPI will be used under the object named spi_obj
- Constructor function has been reduced to 2 parametters (for RST and RS pin)
- Add begin() method with some default properties: 
  - Orientation=0
  - BackgroundColor=0x0
  - Font=FreeSerif9pt7b
  - Start H-SPI
- Add clearTextLine()
- Add drawColorImage()
- Add drawGFXTextLine() with two overload function, one for single text (msg), one using variadic template for multiple text (msg). I using template to make more plexible in passing variable without casting (in overload).