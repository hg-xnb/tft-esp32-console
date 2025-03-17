## ```agiftforcursh``` project
Hi! <br>
This project is made with special name is ```agiftforcursh```. I made it for my ```non-existed crush``` :>. Finally, it just a project.

## Hardware
- ESP-WROOM32 (esp32doit-devkit-v1)
- TFT LCD Screen (2.2")
- DHT11 sensor
- Joystick
- Resistors
- LEDs
  
## Sorfware
- Visualt Studio Code
- VSCode's Extensions: PlatformIO
  
## Programming Language
- C++11
  
## Content
In this project, i has made some classes for do somethings:
- POINT<Tpoint = uint16_t> : point's object; methods: operator=, X(), Y() 
- IMAGE<Timage> : image's object; methods: operator=, image_vector(), height(), width(), fill(), crop(), pixel(), contrustors, ... 
- CANVAS<Tcanvas> : canvas's object; methods: operator=, ), H(), W(), refill(), resize(), show(), clear(), insert_text(), insert_bitmap_image(), insert_color_image(), insert_line(), contrustors, ...

CANVAS class is made for UI design, with my own fucntion for draw, process current canvas... Although I has had ```TFT 22 ILI9225``` lib of **nkawu**, but i want to made my own lib to learn and practice knowledgement about algorithm, and knowledgement related to represent geometry in matrix pixel, IoT's protocols, ... The things what i has implement from  ```TFT 22 ILI9225``` is ```drawPixel(x, y)```, ```begin()```, ```clear()``` method.
p/s: I have modified ```TFT 22 ILI9225``` lib of **nkawu** to add a function for inserting an 565-color image, [here](https://github.com/ngxx-fus/TFT_22_ILI9225_MOD.git) is the mod version.

## UI Preview
|    |    |    |
|:--:|:--:|:--:|
|<img src="https://github.com/user-attachments/assets/a4337c0f-4a27-4d5c-9758-9d42d6d7a2f7" alt="demo0" style="width: 150px;"/>|<img src="https://github.com/user-attachments/assets/77e80268-7111-4120-9815-e06380eb2bf6" alt="demo1" style="width: 150px;"/>|<img src="https://github.com/user-attachments/assets/62f3a9f1-e5f2-4681-9cc6-5bcd12ed43ed" alt="demo2" style="width: 150px;"/>|
|<img src="https://github.com/user-attachments/assets/57a74e81-983f-470a-a947-f26a9358fb0e" alt="demo3" style="width: 150px;"/>|<img src="https://github.com/user-attachments/assets/a62f6bda-be75-4091-b6ab-8399d77415f5" alt="demo4" style="width: 150px;"/>|<img src="https://github.com/user-attachments/assets/2608c0ca-1dee-4f68-955e-29e6da5038e8" alt="demo5" style="width: 150px;"/>|
|<img src="https://github.com/user-attachments/assets/c2bfa7ae-f121-4d09-9495-6632ea713d3c" alt="demo6" style="width: 150px;"/>|<img src="https://github.com/user-attachments/assets/2773fbf3-ce89-427b-8c0d-a0fbfcfe1250" alt="demo7" style="width: 150px;"/>|<img src="https://github.com/user-attachments/assets/543cf145-e043-4f39-9fb5-f373b0661265" alt="demo8" style="width: 150px;"/>|

## Product Preview
v.3.0
|    |    |    |
|:--:|:--:|:--:|
|<img src="https://github.com/user-attachments/assets/915bc990-8b94-4750-8c77-2634e9bd6e94" alt="preview0" style="width: 150px;"/>|<img src="https://github.com/user-attachments/assets/efc32539-a637-4e28-b3d8-d24e574531ea" alt="preview0" style="width: 150px;"/>|  <img src="https://github.com/user-attachments/assets/f3fbfb9a-278e-489b-a8e8-99dabbf045b0" alt="preview0" style="width: 150px;"/>  |

v.2.0

|    |    |    |
|:--:|:--:|:--:|
|<img src="https://github.com/user-attachments/assets/c5ccf7fb-b355-42e7-ac97-4338d27a062b" alt="preview0" style="width: 150px;"/>|<img src="https://github.com/user-attachments/assets/2b1f1c54-aa25-4484-b9b0-69b92d5a4b47" alt="preview0" style="width: 150px;"/>|  <img src="https://github.com/user-attachments/assets/3d31c5d9-b428-46c1-9e01-d384613b1570" alt="preview0" style="width: 150px;"/>  |

