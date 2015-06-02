# Circuit Elements #

An ESC is made up of smaller sub-circuits all working together to complete it's tasks. Some of these are optional, and the overall circuit can be broken down into a modular design. This section is of most use to someone building their own ESC rather than reprogramming a current model.

To skip to the example circuit, **[click here](circuit#Example_Circuit.md)**.


## Required ##

An ESC requires these to function. They are not optional.


### Power Supply ###

The power supply provides power for running the motor, and is also regulated down to a level appropriate for logic (3.3V or 5V). If using an Atmega8 chip, the very popular 7805 power regulator can be used. It is advisable to place a large capacitor across the power supply lines to smooth any voltage drops caused by motor operation. Anything in the range of 330uF to 1000uF should do. A smaller 0.1uF capacitor should be placed as close to the MCU Vcc pin as possible. A sample circuit is shown below (put the large capacitor in place of the 0.33uF one)

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/7805.gif' />
</p>
<p align='center'>
<b>Figure 1. Simple 7805 circuit.</b>
</p>


### Microcontroller (MCU) ###

This sub-circuit will contain the MCU itself, an oscillator (recommended) with accompanying capacitors, and ISP headers of some form. You should mark pin 1 on your header for correct orientation. All relevant inputs and outputs will connect to the microcontroller, which will be covered later.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/avrisp.png' />
</p>
<p align='center'>
<b>Figure 2. AVR ISP header layout. The 6-pin (a) variant is the most modern.</b>
</p>


### Speed Reference Input ###

The input signal can come in multiple forms (RC pulse, I<sup>2</sup>C, serial). The easiest is to use another MCU which reads a potentiometer, and adjusts it's output accordingly. This will not be covered in this wiki.


### Power Delivery Stage ###

This module contains the MOSFETs and necessary MOSFET driving circuitry to interface with MCU logic level voltage. There will be 3 identical power stages, one for each phase (A, B, and C). More information [here](mosfetdrive.md).


### Back-EMF Conditioning ###

The voltage coming from the motor will be as high as the power supply voltage (sometimes higher due to inductive spikes). This sub-circuit reduces that voltage down to a safe level to feed into the MCU, and also contructs the virtual neutral voltage of the motor for use with the MCU's internal comparator. This module is also mirrored 3 times, once for each phase. An example is shown below. Common resistor values for a 6-12V power supply are `R1 & R3` = 47k, `R2` = 10k.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/schematics/PhaseSense.png' />
</p>
<p align='center'>
<b>Figure 3. Back-EMF conditioning circuit.</b>
</p>


## Optional ##

These modules are not required for successful operation, but can be included for debugging and systems monitoring.


### Serial Debugging ###

To debug the ESC via serial, a chip like a MAX232 is needed. This converts the 5V MCU logic to the appropriate levels (-12V -> 12V) for the RS232 protocol. An RS232 to USB cable can be bought online for a few dollars. The MAX232 requires four 1uF capacitors for level shifting. Refer to datasheet for circuit diagram.


### Systems Diagnostics ###

If the ESC is to be used in an expensive autonomous vehicle, it would be wise to install extra circuits to monitor things like temperature (a thermistor), current (current sense resistor), and voltage (simple voltage divider). These will need the extra ADC units which are only available on the smaller SMD Atmega8 chips.


## Example Circuit ##

An example fuctioning circuit will look something like [this](http://dl.dropbox.com/u/6783818/Brushless/schematics/complete.png). This circuit leaves out some important aspects to save clutter, these include:
  * 5V regulator
  * 330uF to 1000uF smoothing cap from V+ to gnd
  * AVR ISP header
  * Serial communications (MAX232)
It is assumed you will have to knowledge to correctly connect these extras. Also note, the power stage is one of many possible configurations. See [Driving The MOSFETs](mosfetdrive.md) for more details.