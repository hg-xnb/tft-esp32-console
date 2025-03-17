# About

The C++ program to convert an JPG image to BIN image (that can be read and displayed in `agiftforcrush`). All image in `imgs` folder will be resized and crop to **hxw=220x172** the export to **\*.bin** (destination output) and **\*.jpg** (preview output).

## Dependencies

This C++ program requires `libjpeg` to read/write JPG image file and `g++` to compile `*.cpp` files.

```bash
sudo apt update
sudo apt upgrade
sudo apt install g++
sudo apt install make
sudo apt install libjpeg-dev
```

## Working Tree

NOTE: Cause of ```.gitignore```, some directorys will not be appeared in this repository. You need to manually create them.

```text
utils
├──── imgs                                  : original imgs (input img source)
│     ├──── *.jgp / *.JPG
│     └──── ...
├──── bins                                  : bin imgs (target output)
│     ├──── img1.bin 
│     └──── ...
├──── resized_imgs                          : resized imgs (preview output)
│     ├──── resized_img_1.jpg 
│     └──── ...
├──── img2bin.cpp                           : the C++ program to convert JPG img -> BIN img
├──── Makefile
├──── readme.md 
└──── .gitignore
```

Re-create working tree

```bash
mkdir -p \
./bins \
./archived \
./imgs \
./resized_imgs
```

## Useage

### Makefile

First, change the path to SDCard, the simple way, open SDCard dir, then ```ctrl+l```, then copy them. The example below.

```Makefile
[line 25] SDCARD_TARGET   := /media/ngxxfus/SD_CARD
```
![Kooha-2025-02-02-07-23-00](https://github.com/user-attachments/assets/006b843c-4742-4468-aaed-486077f839e0)


Seccond, copy all images (which you want to be converted) into ```imgs``` directory.

Third, run with ```make```. Make sure ```make``` has been installed in yours. If ```make``` hasn't been installed, install via ```apt```.

|Make commands          | Decription    |
| :--                   | :--           |
| make / make all       | build object file ```img2bin.o``` and excutable file ```img2bin``` |
| make clean            | remove  ```img2bin.o```, ```img2bin```, ```utils/resized_imgs/*```, ```utils/bins/*```|
| make rebuild          | remove  ```img2bin.o```, ```img2bin```, ```utils/resized_imgs/*```, ```utils/bins/*``` then re-build ```img2bin.o``` and ```img2bin```|
| make convert_images   | if doesn't exist ```img2bin.o```, ```img2bin```, then build ```img2bin.o```, ```img2bin```, then run ```img2bin.o``` to convert images in ```utils/resized_imgs/``` to binary file image ```utils/bins/*``` and preview image ```utils/resized_imgs/``` (includes resize, crop).|
| make copy2sdcard      | Copy binary file image into ```imgs``` directory in SDCard. |

A recommended make command to run
```bash
    make convert_images copy2sdcard
```

![Kooha-2025-02-02-07-28-41](https://github.com/user-attachments/assets/44ff4df7-bc8b-42b3-8846-39c1922c4ce5)

## Classes

|         |          |
| :----   | :----    |
|<img src="https://github.com/user-attachments/assets/12d3f5ac-19d3-46b5-aa32-f46e2b225348" style="width:500px;"/> |<img src="https://github.com/user-attachments/assets/2a55547b-21ec-41fa-8f0c-aa35a963e12a" style="width:500px;"/> | 
| <img src="https://github.com/user-attachments/assets/6a3b7227-abbd-4a71-91f1-f5765d2ea931" style="width:500px;"/>|     |

<details>
<summary>
LOG
</summary>

<pre><font color="#80F1E8">ngxxfus&apos;s </font><font color="#D4DBDD">utils/ </font><font color="#FFFFFF">on</font><font color="#F6F32E"> master ≡ </font>                                                                                                                          <font color="#85C980">RAM:9/11GB </font><font color="#D0CFCC">┋</font><font color="#FFFFFF"> 6ms </font>
<font color="#4796F1">⮞ </font> ll
total 188
drwxrwxrwx 1 root root 24576 Feb  2 07:26 <span style="background-color:#26A269"><font color="#12488B">bins</font></span>/
drwxrwxrwx 1 root root 28672 Feb  2 07:26 <span style="background-color:#26A269"><font color="#12488B">resized_imgs</font></span>/
-rwxrwxrwx 1 root root 37632 Feb  2 07:25 <font color="#26A269"><b>img2bin</b></font>*
drwxrwxrwx 1 root root  4096 Feb  2 07:25 <span style="background-color:#26A269"><font color="#12488B">.</font></span>/
-rwxrwxrwx 1 root root 31632 Feb  2 07:25 <font color="#26A269"><b>img2bin.o</b></font>*
-rwxrwxrwx 1 root root  2835 Feb  2 07:23 <font color="#26A269"><b>readme.md</b></font>*
-rwxrwxrwx 1 root root  1618 Feb  2 07:23 <font color="#26A269"><b>Makefile</b></font>*
drwxrwxrwx 1 root root  4096 Feb  2 07:09 <span style="background-color:#26A269"><font color="#12488B">archived</font></span>/
-rwxrwxrwx 1 root root 17533 Feb  2 06:42 <font color="#26A269"><b>img2bin.cpp</b></font>*
drwxrwxrwx 1 root root 24576 Feb  1 22:11 <span style="background-color:#26A269"><font color="#12488B">imgs</font></span>/
drwxrwxrwx 1 root root  4096 Dec 31 18:35 <span style="background-color:#26A269"><font color="#12488B">..</font></span>/
<font color="#80F1E8">ngxxfus&apos;s </font><font color="#D4DBDD">utils/ </font><font color="#FFFFFF">on</font><font color="#F6F32E"> master ≡ </font>                                                                                                                          <font color="#85C980">RAM:9/11GB </font><font color="#D0CFCC">┋</font><font color="#FFFFFF"> 7ms </font>
<font color="#4796F1">⮞ </font> make convert_images copy2sdcard 
Converting images...
@imgs/IMG_4208.JPG

Processing arg[1] : imgs/IMG_4208.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4208.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4208.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x7e4b81260010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4209.JPG

Processing arg[1] : imgs/IMG_4209.JPG
&lt;RGB_IMG id=4165433610&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=4165433610&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=4165433610&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=4165433610&gt; Image saved to: ./resized_imgs/IMG_4209.jpg
&lt;RGB_IMG id=4165433610&gt; Image saved to binary file: ./bins/IMG_4209.bin
&lt;RGB_IMG id=4165433610&gt; delete[] pixels=0x77bff8060010
&lt;RGB_IMG id=4165433610&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4210.JPG

Processing arg[1] : imgs/IMG_4210.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4210.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4210.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x7a2f93149010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4211.JPG

Processing arg[1] : imgs/IMG_4211.JPG
&lt;RGB_IMG id=1816623370&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1816623370&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1816623370&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1816623370&gt; Image saved to: ./resized_imgs/IMG_4211.jpg
&lt;RGB_IMG id=1816623370&gt; Image saved to binary file: ./bins/IMG_4211.bin
&lt;RGB_IMG id=1816623370&gt; delete[] pixels=0x7fcc6c060010
&lt;RGB_IMG id=1816623370&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4212.JPG

Processing arg[1] : imgs/IMG_4212.JPG
&lt;RGB_IMG id=854091786&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=854091786&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=854091786&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=854091786&gt; Image saved to: ./resized_imgs/IMG_4212.jpg
&lt;RGB_IMG id=854091786&gt; Image saved to binary file: ./bins/IMG_4212.bin
&lt;RGB_IMG id=854091786&gt; delete[] pixels=0x732ac3a84010
&lt;RGB_IMG id=854091786&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4213.JPG

Processing arg[1] : imgs/IMG_4213.JPG
&lt;RGB_IMG id=945092618&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=945092618&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=945092618&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=945092618&gt; Image saved to: ./resized_imgs/IMG_4213.jpg
&lt;RGB_IMG id=945092618&gt; Image saved to binary file: ./bins/IMG_4213.bin
&lt;RGB_IMG id=945092618&gt; delete[] pixels=0x7977a9032010
&lt;RGB_IMG id=945092618&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4214.JPG

Processing arg[1] : imgs/IMG_4214.JPG
&lt;RGB_IMG id=1368897034&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1368897034&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1368897034&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1368897034&gt; Image saved to: ./resized_imgs/IMG_4214.jpg
&lt;RGB_IMG id=1368897034&gt; Image saved to binary file: ./bins/IMG_4214.bin
&lt;RGB_IMG id=1368897034&gt; delete[] pixels=0x727823060010
&lt;RGB_IMG id=1368897034&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4215.JPG

Processing arg[1] : imgs/IMG_4215.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4215.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4215.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x7982cda93010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4216.JPG

Processing arg[1] : imgs/IMG_4216.JPG
&lt;RGB_IMG id=2174269450&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2174269450&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2174269450&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2174269450&gt; Image saved to: ./resized_imgs/IMG_4216.jpg
&lt;RGB_IMG id=2174269450&gt; Image saved to binary file: ./bins/IMG_4216.bin
&lt;RGB_IMG id=2174269450&gt; delete[] pixels=0x74200ca32010
&lt;RGB_IMG id=2174269450&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4217.JPG

Processing arg[1] : imgs/IMG_4217.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4217.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4217.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x7279fccad010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4218.JPG

Processing arg[1] : imgs/IMG_4218.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4218.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4218.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x7e7151a32010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4219.JPG

Processing arg[1] : imgs/IMG_4219.JPG
&lt;RGB_IMG id=1854372106&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1854372106&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1854372106&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1854372106&gt; Image saved to: ./resized_imgs/IMG_4219.jpg
&lt;RGB_IMG id=1854372106&gt; Image saved to binary file: ./bins/IMG_4219.bin
&lt;RGB_IMG id=1854372106&gt; delete[] pixels=0x76c86e5c8010
&lt;RGB_IMG id=1854372106&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4220.JPG

Processing arg[1] : imgs/IMG_4220.JPG
&lt;RGB_IMG id=3282417162&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3282417162&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3282417162&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3282417162&gt; Image saved to: ./resized_imgs/IMG_4220.jpg
&lt;RGB_IMG id=3282417162&gt; Image saved to binary file: ./bins/IMG_4220.bin
&lt;RGB_IMG id=3282417162&gt; delete[] pixels=0x75378c549010
&lt;RGB_IMG id=3282417162&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4221.JPG

Processing arg[1] : imgs/IMG_4221.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4221.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4221.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x78bca6549010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4222.JPG

Processing arg[1] : imgs/IMG_4222.JPG
&lt;RGB_IMG id=3446110474&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3446110474&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3446110474&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3446110474&gt; Image saved to: ./resized_imgs/IMG_4222.jpg
&lt;RGB_IMG id=3446110474&gt; Image saved to binary file: ./bins/IMG_4222.bin
&lt;RGB_IMG id=3446110474&gt; delete[] pixels=0x76abcd344010
&lt;RGB_IMG id=3446110474&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4223.JPG

Processing arg[1] : imgs/IMG_4223.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4223.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4223.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x7919cd485010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4224.JPG

Processing arg[1] : imgs/IMG_4224.JPG
&lt;RGB_IMG id=1068629002&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1068629002&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1068629002&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1068629002&gt; Image saved to: ./resized_imgs/IMG_4224.jpg
&lt;RGB_IMG id=1068629002&gt; Image saved to binary file: ./bins/IMG_4224.bin
&lt;RGB_IMG id=1068629002&gt; delete[] pixels=0x77404d8aa010
&lt;RGB_IMG id=1068629002&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4225.JPG

Processing arg[1] : imgs/IMG_4225.JPG
&lt;RGB_IMG id=1661434122&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1661434122&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1661434122&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1661434122&gt; Image saved to: ./resized_imgs/IMG_4225.jpg
&lt;RGB_IMG id=1661434122&gt; Image saved to binary file: ./bins/IMG_4225.bin
&lt;RGB_IMG id=1661434122&gt; delete[] pixels=0x72ed630a9010
&lt;RGB_IMG id=1661434122&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4226.JPG

Processing arg[1] : imgs/IMG_4226.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4226.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4226.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x7b92c289e010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4227.JPG

Processing arg[1] : imgs/IMG_4227.JPG
&lt;RGB_IMG id=3351037706&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3351037706&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3351037706&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3351037706&gt; Image saved to: ./resized_imgs/IMG_4227.jpg
&lt;RGB_IMG id=3351037706&gt; Image saved to binary file: ./bins/IMG_4227.bin
&lt;RGB_IMG id=3351037706&gt; delete[] pixels=0x7664bb860010
&lt;RGB_IMG id=3351037706&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4228.JPG

Processing arg[1] : imgs/IMG_4228.JPG
&lt;RGB_IMG id=2317651466&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2317651466&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2317651466&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2317651466&gt; Image saved to: ./resized_imgs/IMG_4228.jpg
&lt;RGB_IMG id=2317651466&gt; Image saved to binary file: ./bins/IMG_4228.bin
&lt;RGB_IMG id=2317651466&gt; delete[] pixels=0x722035a84010
&lt;RGB_IMG id=2317651466&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4229.JPG

Processing arg[1] : imgs/IMG_4229.JPG
&lt;RGB_IMG id=1870127882&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1870127882&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1870127882&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1870127882&gt; Image saved to: ./resized_imgs/IMG_4229.jpg
&lt;RGB_IMG id=1870127882&gt; Image saved to binary file: ./bins/IMG_4229.bin
&lt;RGB_IMG id=1870127882&gt; delete[] pixels=0x791567485010
&lt;RGB_IMG id=1870127882&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4230.JPG

Processing arg[1] : imgs/IMG_4230.JPG
&lt;RGB_IMG id=2290579722&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2290579722&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2290579722&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2290579722&gt; Image saved to: ./resized_imgs/IMG_4230.jpg
&lt;RGB_IMG id=2290579722&gt; Image saved to binary file: ./bins/IMG_4230.bin
&lt;RGB_IMG id=2290579722&gt; delete[] pixels=0x76ce88460010
&lt;RGB_IMG id=2290579722&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4231.JPG

Processing arg[1] : imgs/IMG_4231.JPG
&lt;RGB_IMG id=310868234&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=310868234&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=310868234&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=310868234&gt; Image saved to: ./resized_imgs/IMG_4231.jpg
&lt;RGB_IMG id=310868234&gt; Image saved to binary file: ./bins/IMG_4231.bin
&lt;RGB_IMG id=310868234&gt; delete[] pixels=0x792512889010
&lt;RGB_IMG id=310868234&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4232.JPG

Processing arg[1] : imgs/IMG_4232.JPG
&lt;RGB_IMG id=969315338&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=969315338&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=969315338&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=969315338&gt; Image saved to: ./resized_imgs/IMG_4232.jpg
&lt;RGB_IMG id=969315338&gt; Image saved to binary file: ./bins/IMG_4232.bin
&lt;RGB_IMG id=969315338&gt; delete[] pixels=0x7a7b1af49010
&lt;RGB_IMG id=969315338&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4233.JPG

Processing arg[1] : imgs/IMG_4233.JPG
&lt;RGB_IMG id=2646998794&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2646998794&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2646998794&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2646998794&gt; Image saved to: ./resized_imgs/IMG_4233.jpg
&lt;RGB_IMG id=2646998794&gt; Image saved to binary file: ./bins/IMG_4233.bin
&lt;RGB_IMG id=2646998794&gt; delete[] pixels=0x776f83eae010
&lt;RGB_IMG id=2646998794&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4234.JPG

Processing arg[1] : imgs/IMG_4234.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4234.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4234.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x70ac664df010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4235.JPG

Processing arg[1] : imgs/IMG_4235.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4235.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4235.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x722b588df010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4236.JPG

Processing arg[1] : imgs/IMG_4236.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4236.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4236.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x70d4198df010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4240.JPG

Processing arg[1] : imgs/IMG_4240.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4240.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4240.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x7c88330df010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4241.JPG

Processing arg[1] : imgs/IMG_4241.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4241.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4241.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x780047adf010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4242.JPG

Processing arg[1] : imgs/IMG_4242.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4242.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4242.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x787fd99c8010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4243.JPG

Processing arg[1] : imgs/IMG_4243.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4243.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4243.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x7c4065357010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4244.JPG

Processing arg[1] : imgs/IMG_4244.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4244.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4244.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x76cce009d010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4245.JPG

Processing arg[1] : imgs/IMG_4245.JPG
&lt;RGB_IMG id=1408905738&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=1408905738&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=1408905738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1408905738&gt; Image saved to: ./resized_imgs/IMG_4245.jpg
&lt;RGB_IMG id=1408905738&gt; Image saved to binary file: ./bins/IMG_4245.bin
&lt;RGB_IMG id=1408905738&gt; delete[] pixels=0x78deeba96010
&lt;RGB_IMG id=1408905738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4248.JPG

Processing arg[1] : imgs/IMG_4248.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4248.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4248.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x704e7a86e010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4249.JPG

Processing arg[1] : imgs/IMG_4249.JPG
&lt;RGB_IMG id=2963765514&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=2963765514&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=2963765514&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2963765514&gt; Image saved to: ./resized_imgs/IMG_4249.jpg
&lt;RGB_IMG id=2963765514&gt; Image saved to binary file: ./bins/IMG_4249.bin
&lt;RGB_IMG id=2963765514&gt; delete[] pixels=0x74a5b066e010
&lt;RGB_IMG id=2963765514&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4250.JPG

Processing arg[1] : imgs/IMG_4250.JPG
&lt;RGB_IMG id=2969281546&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=2969281546&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=2969281546&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2969281546&gt; Image saved to: ./resized_imgs/IMG_4250.jpg
&lt;RGB_IMG id=2969281546&gt; Image saved to binary file: ./bins/IMG_4250.bin
&lt;RGB_IMG id=2969281546&gt; delete[] pixels=0x79b48088b010
&lt;RGB_IMG id=2969281546&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4252.JPG

Processing arg[1] : imgs/IMG_4252.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4252.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4252.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x7d53ad093010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4256.JPG

Processing arg[1] : imgs/IMG_4256.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4256.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4256.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x70b484cae010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4258.JPG

Processing arg[1] : imgs/IMG_4258.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4258.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4258.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x7897f7c9a010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4259.JPG

Processing arg[1] : imgs/IMG_4259.JPG
&lt;RGB_IMG id=3410703370&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3410703370&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3410703370&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3410703370&gt; Image saved to: ./resized_imgs/IMG_4259.jpg
&lt;RGB_IMG id=3410703370&gt; Image saved to binary file: ./bins/IMG_4259.bin
&lt;RGB_IMG id=3410703370&gt; delete[] pixels=0x73fb3ac84010
&lt;RGB_IMG id=3410703370&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4260.JPG

Processing arg[1] : imgs/IMG_4260.JPG
&lt;RGB_IMG id=3305301770&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3305301770&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3305301770&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3305301770&gt; Image saved to: ./resized_imgs/IMG_4260.jpg
&lt;RGB_IMG id=3305301770&gt; Image saved to binary file: ./bins/IMG_4260.bin
&lt;RGB_IMG id=3305301770&gt; delete[] pixels=0x7b52a1749010
&lt;RGB_IMG id=3305301770&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4261.JPG

Processing arg[1] : imgs/IMG_4261.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4261.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4261.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x739c1629c010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4262.JPG

Processing arg[1] : imgs/IMG_4262.JPG
&lt;RGB_IMG id=3117392394&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3117392394&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3117392394&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3117392394&gt; Image saved to: ./resized_imgs/IMG_4262.jpg
&lt;RGB_IMG id=3117392394&gt; Image saved to binary file: ./bins/IMG_4262.bin
&lt;RGB_IMG id=3117392394&gt; delete[] pixels=0x724c13c9a010
&lt;RGB_IMG id=3117392394&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4263.JPG

Processing arg[1] : imgs/IMG_4263.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4263.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4263.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x727c0b349010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4264.JPG

Processing arg[1] : imgs/IMG_4264.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4264.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4264.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x72c69b2df010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4265.JPG

Processing arg[1] : imgs/IMG_4265.JPG
&lt;RGB_IMG id=2527557898&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2527557898&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2527557898&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2527557898&gt; Image saved to: ./resized_imgs/IMG_4265.jpg
&lt;RGB_IMG id=2527557898&gt; Image saved to binary file: ./bins/IMG_4265.bin
&lt;RGB_IMG id=2527557898&gt; delete[] pixels=0x7b1b96aaa010
&lt;RGB_IMG id=2527557898&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4266.JPG

Processing arg[1] : imgs/IMG_4266.JPG
&lt;RGB_IMG id=849836298&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=849836298&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=849836298&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=849836298&gt; Image saved to: ./resized_imgs/IMG_4266.jpg
&lt;RGB_IMG id=849836298&gt; Image saved to binary file: ./bins/IMG_4266.bin
&lt;RGB_IMG id=849836298&gt; delete[] pixels=0x78b6327c8010
&lt;RGB_IMG id=849836298&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4267.JPG

Processing arg[1] : imgs/IMG_4267.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4267.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4267.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x728f56fc8010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4268.JPG

Processing arg[1] : imgs/IMG_4268.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4268.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4268.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x795c81edf010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4269.JPG

Processing arg[1] : imgs/IMG_4269.JPG
&lt;RGB_IMG id=2969030666&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2969030666&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2969030666&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2969030666&gt; Image saved to: ./resized_imgs/IMG_4269.jpg
&lt;RGB_IMG id=2969030666&gt; Image saved to binary file: ./bins/IMG_4269.bin
&lt;RGB_IMG id=2969030666&gt; delete[] pixels=0x704e7b349010
&lt;RGB_IMG id=2969030666&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4270.JPG

Processing arg[1] : imgs/IMG_4270.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4270.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4270.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x7159e4e32010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4271.JPG

Processing arg[1] : imgs/IMG_4271.JPG
&lt;RGB_IMG id=3383195914&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3383195914&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3383195914&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3383195914&gt; Image saved to: ./resized_imgs/IMG_4271.jpg
&lt;RGB_IMG id=3383195914&gt; Image saved to binary file: ./bins/IMG_4271.bin
&lt;RGB_IMG id=3383195914&gt; delete[] pixels=0x7f71c9660010
&lt;RGB_IMG id=3383195914&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4272.JPG

Processing arg[1] : imgs/IMG_4272.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4272.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4272.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x7283e905d010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4273.JPG

Processing arg[1] : imgs/IMG_4273.JPG
&lt;RGB_IMG id=2900850954&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2900850954&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2900850954&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2900850954&gt; Image saved to: ./resized_imgs/IMG_4273.jpg
&lt;RGB_IMG id=2900850954&gt; Image saved to binary file: ./bins/IMG_4273.bin
&lt;RGB_IMG id=2900850954&gt; delete[] pixels=0x7db0aca32010
&lt;RGB_IMG id=2900850954&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4274.JPG

Processing arg[1] : imgs/IMG_4274.JPG
&lt;RGB_IMG id=930279946&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=930279946&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=930279946&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=930279946&gt; Image saved to: ./resized_imgs/IMG_4274.jpg
&lt;RGB_IMG id=930279946&gt; Image saved to binary file: ./bins/IMG_4274.bin
&lt;RGB_IMG id=930279946&gt; delete[] pixels=0x7a1d34a99010
&lt;RGB_IMG id=930279946&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4275.JPG

Processing arg[1] : imgs/IMG_4275.JPG
&lt;RGB_IMG id=3267852554&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3267852554&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3267852554&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3267852554&gt; Image saved to: ./resized_imgs/IMG_4275.jpg
&lt;RGB_IMG id=3267852554&gt; Image saved to binary file: ./bins/IMG_4275.bin
&lt;RGB_IMG id=3267852554&gt; delete[] pixels=0x72afc2949010
&lt;RGB_IMG id=3267852554&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4276.JPG

Processing arg[1] : imgs/IMG_4276.JPG
&lt;RGB_IMG id=3790379274&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3790379274&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3790379274&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3790379274&gt; Image saved to: ./resized_imgs/IMG_4276.jpg
&lt;RGB_IMG id=3790379274&gt; Image saved to binary file: ./bins/IMG_4276.bin
&lt;RGB_IMG id=3790379274&gt; delete[] pixels=0x76bbbfa95010
&lt;RGB_IMG id=3790379274&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4277.JPG

Processing arg[1] : imgs/IMG_4277.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4277.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4277.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x77b21f032010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4278.JPG

Processing arg[1] : imgs/IMG_4278.JPG
&lt;RGB_IMG id=1770664970&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1770664970&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1770664970&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1770664970&gt; Image saved to: ./resized_imgs/IMG_4278.jpg
&lt;RGB_IMG id=1770664970&gt; Image saved to binary file: ./bins/IMG_4278.bin
&lt;RGB_IMG id=1770664970&gt; delete[] pixels=0x77b5df0c4010
&lt;RGB_IMG id=1770664970&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4279.JPG

Processing arg[1] : imgs/IMG_4279.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4279.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4279.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x7b6ecde60010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4280.JPG

Processing arg[1] : imgs/IMG_4280.JPG
&lt;RGB_IMG id=2955376906&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2955376906&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2955376906&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2955376906&gt; Image saved to: ./resized_imgs/IMG_4280.jpg
&lt;RGB_IMG id=2955376906&gt; Image saved to binary file: ./bins/IMG_4280.bin
&lt;RGB_IMG id=2955376906&gt; delete[] pixels=0x72e7afe32010
&lt;RGB_IMG id=2955376906&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4281.JPG

Processing arg[1] : imgs/IMG_4281.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4281.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4281.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x7fe0f84b4010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4282.JPG

Processing arg[1] : imgs/IMG_4282.JPG
&lt;RGB_IMG id=1960451594&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1960451594&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1960451594&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1960451594&gt; Image saved to: ./resized_imgs/IMG_4282.jpg
&lt;RGB_IMG id=1960451594&gt; Image saved to binary file: ./bins/IMG_4282.bin
&lt;RGB_IMG id=1960451594&gt; delete[] pixels=0x7092208a3010
&lt;RGB_IMG id=1960451594&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4283.JPG

Processing arg[1] : imgs/IMG_4283.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4283.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4283.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x76b08ddc8010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4284.JPG

Processing arg[1] : imgs/IMG_4284.JPG
&lt;RGB_IMG id=3824257034&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3824257034&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3824257034&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3824257034&gt; Image saved to: ./resized_imgs/IMG_4284.jpg
&lt;RGB_IMG id=3824257034&gt; Image saved to binary file: ./bins/IMG_4284.bin
&lt;RGB_IMG id=3824257034&gt; delete[] pixels=0x7d0f8b099010
&lt;RGB_IMG id=3824257034&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4285.JPG

Processing arg[1] : imgs/IMG_4285.JPG
&lt;RGB_IMG id=325224970&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=325224970&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=325224970&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=325224970&gt; Image saved to: ./resized_imgs/IMG_4285.jpg
&lt;RGB_IMG id=325224970&gt; Image saved to binary file: ./bins/IMG_4285.bin
&lt;RGB_IMG id=325224970&gt; delete[] pixels=0x715aad8b4010
&lt;RGB_IMG id=325224970&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4286.JPG

Processing arg[1] : imgs/IMG_4286.JPG
&lt;RGB_IMG id=3020001546&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=3020001546&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=3020001546&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3020001546&gt; Image saved to: ./resized_imgs/IMG_4286.jpg
&lt;RGB_IMG id=3020001546&gt; Image saved to binary file: ./bins/IMG_4286.bin
&lt;RGB_IMG id=3020001546&gt; delete[] pixels=0x73488b0df010
&lt;RGB_IMG id=3020001546&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4287.JPG

Processing arg[1] : imgs/IMG_4287.JPG
&lt;RGB_IMG id=684161290&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=684161290&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=684161290&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=684161290&gt; Image saved to: ./resized_imgs/IMG_4287.jpg
&lt;RGB_IMG id=684161290&gt; Image saved to binary file: ./bins/IMG_4287.bin
&lt;RGB_IMG id=684161290&gt; delete[] pixels=0x7ae4289c8010
&lt;RGB_IMG id=684161290&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4288.JPG

Processing arg[1] : imgs/IMG_4288.JPG
&lt;RGB_IMG id=4277749002&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=4277749002&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=4277749002&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=4277749002&gt; Image saved to: ./resized_imgs/IMG_4288.jpg
&lt;RGB_IMG id=4277749002&gt; Image saved to binary file: ./bins/IMG_4288.bin
&lt;RGB_IMG id=4277749002&gt; delete[] pixels=0x729d7a880010
&lt;RGB_IMG id=4277749002&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4289.JPG

Processing arg[1] : imgs/IMG_4289.JPG
&lt;RGB_IMG id=1999075594&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1999075594&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1999075594&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1999075594&gt; Image saved to: ./resized_imgs/IMG_4289.jpg
&lt;RGB_IMG id=1999075594&gt; Image saved to binary file: ./bins/IMG_4289.bin
&lt;RGB_IMG id=1999075594&gt; delete[] pixels=0x7e7477287010
&lt;RGB_IMG id=1999075594&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4292.JPG

Processing arg[1] : imgs/IMG_4292.JPG
&lt;RGB_IMG id=1311209738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=1311209738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=1311209738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1311209738&gt; Image saved to: ./resized_imgs/IMG_4292.jpg
&lt;RGB_IMG id=1311209738&gt; Image saved to binary file: ./bins/IMG_4292.bin
&lt;RGB_IMG id=1311209738&gt; delete[] pixels=0x7aa74de32010
&lt;RGB_IMG id=1311209738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4293.JPG

Processing arg[1] : imgs/IMG_4293.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4293.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4293.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x73d825d49010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4294.JPG

Processing arg[1] : imgs/IMG_4294.JPG
&lt;RGB_IMG id=543621898&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=543621898&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=543621898&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=543621898&gt; Image saved to: ./resized_imgs/IMG_4294.jpg
&lt;RGB_IMG id=543621898&gt; Image saved to binary file: ./bins/IMG_4294.bin
&lt;RGB_IMG id=543621898&gt; delete[] pixels=0x7907312df010
&lt;RGB_IMG id=543621898&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4295.JPG

Processing arg[1] : imgs/IMG_4295.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4295.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4295.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x79b0ba060010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4296.JPG

Processing arg[1] : imgs/IMG_4296.JPG
&lt;RGB_IMG id=73738&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=73738&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=73738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=73738&gt; Image saved to: ./resized_imgs/IMG_4296.jpg
&lt;RGB_IMG id=73738&gt; Image saved to binary file: ./bins/IMG_4296.bin
&lt;RGB_IMG id=73738&gt; delete[] pixels=0x7e6e508c1010
&lt;RGB_IMG id=73738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4297.JPG

Processing arg[1] : imgs/IMG_4297.JPG
&lt;RGB_IMG id=2187819274&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=2187819274&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=2187819274&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2187819274&gt; Image saved to: ./resized_imgs/IMG_4297.jpg
&lt;RGB_IMG id=2187819274&gt; Image saved to binary file: ./bins/IMG_4297.bin
&lt;RGB_IMG id=2187819274&gt; delete[] pixels=0x7bde826b6010
&lt;RGB_IMG id=2187819274&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4298.JPG

Processing arg[1] : imgs/IMG_4298.JPG
&lt;RGB_IMG id=1049065738&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=1049065738&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=1049065738&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1049065738&gt; Image saved to: ./resized_imgs/IMG_4298.jpg
&lt;RGB_IMG id=1049065738&gt; Image saved to binary file: ./bins/IMG_4298.bin
&lt;RGB_IMG id=1049065738&gt; delete[] pixels=0x71693e8b2010
&lt;RGB_IMG id=1049065738&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4299.JPG

Processing arg[1] : imgs/IMG_4299.JPG
&lt;RGB_IMG id=1088911626&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=1088911626&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=1088911626&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=1088911626&gt; Image saved to: ./resized_imgs/IMG_4299.jpg
&lt;RGB_IMG id=1088911626&gt; Image saved to binary file: ./bins/IMG_4299.bin
&lt;RGB_IMG id=1088911626&gt; delete[] pixels=0x7d4540e81010
&lt;RGB_IMG id=1088911626&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4300.JPG

Processing arg[1] : imgs/IMG_4300.JPG
&lt;RGB_IMG id=10&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/IMG_4300.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/IMG_4300.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x74115c23b010
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4301.JPG

Processing arg[1] : imgs/IMG_4301.JPG
&lt;RGB_IMG id=3309948682&gt; initialized h=4000 w=5328 c=3
&lt;RGB_IMG id=3309948682&gt; size_reducing::SUCCESS - New size: 240x319
&lt;RGB_IMG id=3309948682&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=3309948682&gt; Image saved to: ./resized_imgs/IMG_4301.jpg
&lt;RGB_IMG id=3309948682&gt; Image saved to binary file: ./bins/IMG_4301.bin
&lt;RGB_IMG id=3309948682&gt; delete[] pixels=0x795fe7691010
&lt;RGB_IMG id=3309948682&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/IMG_4302.JPG

Processing arg[1] : imgs/IMG_4302.JPG
&lt;RGB_IMG id=2474299914&gt; initialized h=4000 w=6000 c=3
&lt;RGB_IMG id=2474299914&gt; size_reducing::SUCCESS - New size: 240x360
&lt;RGB_IMG id=2474299914&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=2474299914&gt; Image saved to: ./resized_imgs/IMG_4302.jpg
&lt;RGB_IMG id=2474299914&gt; Image saved to binary file: ./bins/IMG_4302.bin
&lt;RGB_IMG id=2474299914&gt; delete[] pixels=0x7ba4a4b49010
&lt;RGB_IMG id=2474299914&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;

@imgs/avt.jpg

Processing arg[1] : imgs/avt.jpg
&lt;RGB_IMG id=10&gt; initialized h=640 w=480 c=3
&lt;RGB_IMG id=10&gt; size_reducing::SUCCESS - New size: 256x192
&lt;RGB_IMG id=10&gt; crop::SUCCESS - New size: 220x172
&lt;RGB_IMG id=10&gt; Image saved to: ./resized_imgs/avt.jpg
&lt;RGB_IMG id=10&gt; Image saved to binary file: ./bins/avt.bin
&lt;RGB_IMG id=10&gt; delete[] pixels=0x576f2011ad80
&lt;RGB_IMG id=10&gt; done!

&gt;&gt;&gt;&gt; done &gt;&gt;&gt;&gt;
rm -rf /media/ngxxfus/SD_CARD/imgs/*
mkdir -p /media/ngxxfus/SD_CARD/imgs
cp -rf bins/IMG_4208.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4209.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4210.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4211.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4212.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4213.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4214.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4215.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4216.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4217.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4218.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4219.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4220.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4221.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4222.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4223.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4224.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4225.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4226.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4227.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4228.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4229.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4230.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4231.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4232.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4233.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4234.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4235.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4236.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4240.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4241.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4242.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4243.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4244.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4245.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4248.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4249.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4250.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4252.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4256.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4258.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4259.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4260.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4261.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4262.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4263.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4264.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4265.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4266.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4267.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4268.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4269.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4270.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4271.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4272.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4273.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4274.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4275.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4276.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4277.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4278.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4279.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4280.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4281.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4282.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4283.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4284.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4285.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4286.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4287.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4288.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4289.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4292.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4293.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4294.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4295.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4296.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4297.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4298.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4299.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4300.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4301.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/IMG_4302.bin /media/ngxxfus/SD_CARD/imgs/
cp -rf bins/avt.bin /media/ngxxfus/SD_CARD/imgs/
<font color="#80F1E8">ngxxfus&apos;s </font><font color="#D4DBDD">utils/ </font><font color="#FFFFFF">on</font><font color="#F6F32E"> master ≡ </font>                                                                                                                    <font color="#85C980">RAM:9/11GB </font><font color="#D0CFCC">┋</font><font color="#FFFFFF"> 38s 929ms </font>
<font color="#4796F1">⮞ </font> 
</pre>

</details>
