# Programming the MCU #

To compile the code, you will need an avr-gcc compiler on your computer (for Windows, see [WinAVR](http://winavr.sourceforge.net/)). In a console, navigate to the project folder which contains main.c and type "`make all`". The hex file will be compiled into the current folder. Load the hex file onto the AVR using avrdude (comes with WinAVR), or configuring your avrdude settings inside the Makefile for your programmer and chip, then typing "`make program`".

As there are plenty of online resources covering avr-gcc coding, compiling and programming, it is not going to be covered in detail here.