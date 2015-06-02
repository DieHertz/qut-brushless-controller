# Required Tools And Equipment #

There are a certain number of items you will need to build and program your ESC:


## Reprogramming A Commercial ESC ##

If taking this approach, all of the circuits and wires will be built for you. You only really need a programmer, but analysis tools will help with debugging.

_**Required**_
  * AVR Programmer. [Digikey](http://search.digikey.com/us/en/products/ATAVRISP2/ATAVRISP2-ND/898891), [Adafruit](https://www.adafruit.com/products/46).
  * Some way to provide input, either a servo tester ([Hobbyking](http://www.hobbyking.com/hobbyking/store/__470__189__Servos_and_parts-Servo_Tester.html) has a few), or another circuit providing servo pulses (e.g. an arduino).
  * Power source. Commercial ESCs usually require 6-12V.

_**Optional**_
  * Multimeter
  * Oscilloscope (4 channels are nice, but 2 channels will be plenty).
  * Soldering iron, just in case.


## Building An ESC From Scratch ##

This option will give you a lot more customisation and make the debugging process a lot easier.

_**Required**_
  * AVR Programmer. [Digikey](http://search.digikey.com/us/en/products/ATAVRISP2/ATAVRISP2-ND/898891), [Adafruit](https://www.adafruit.com/products/46).
  * Input. Very customisable, can use standard RC servo pulses, I2C, or serial. Will need another microcontroller to send the input signal.
  * Power source. Depends on the motor you will be driving.
  * PCB Fabrication tools. This ESC will work on a breadboard, but high current draw from a large motor will burn out the narrow tracks, so it is advisable to use at least through hole components on stripboard for permanent use. Board design and construction is not covered in this wiki.

_**Optional (But Recommended)**_
  * Multimeter.
  * Oscilloscope (4 channels are nice, but 2 channels will be plenty).
  * MAX232 chip and a serial cable, to get debug information from the computer.