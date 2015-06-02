# Knowing When To Commutate #

So...how are we supposed to know when to commutate if we don't know where the rotor is, and we don't have any sensors? This is the most crucial (and complicated) aspect of a brushless ESC. As stated in [Motor Theory](motor.md), the motor produces back-EMF during operation, caused by the magnets moving past the coils inside the motor. The magnitude (and polarity) of the back-EMF on each of the 3 wires is directly related to the position of the magnets relative to the coils. Because only 2 wires are energised at any one time, the back-EMF voltage can be seen on the 3rd undriven (floating) phase. The back-EMF is a sinusoidal voltage, with reference to the center point of the Y-connected motor. Half-way through the optimal commutation period, the back-EMF on the undriven phase is equal to zero, or half the supply voltage of the motor (the two driven coils act as a voltage divider, assuming equal resistance in the motor windings). This is called the "Zero-Crossing Point", as it is the point where the back-EMF on the undriven phase is zero.


## Rotor Position Detection ##

The center point of the motor is often not provided, but it can be contructed using resistors in parallel connected to each phase, often referred to as the "virtual neutral point" (VNP). This virtual neutral point is simply an average of all 3 voltages present on each motor wire. Below is an oscilloscope waveform showing the voltage on phase A (top), and the voltage of the VNP (bottom).

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/bemf.png' />
</p>
<p align='center'>
<b>Figure 2. Phase A (top) and the virtual neutral point (bottom).</b>
</p>

As you can see, there is a lot of switching noise from PWM. This noise makes the task of detecting the correct zero crossing point even harder. These two waveforms are directed to a comparator, which gives a digital output (0 or 1) depending on which voltage is higher. Combining the two waveforms using an oscilloscope maths function reveals the input to this comparator, as shown below.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/maths.png' />
</p>
<p align='center'>
<b>Figure 3. Using a maths function to combine the two waveforms in figure 2.</b>
</p>

This may still look a bit messy, but this waveform will only be sensed during the floating phase, and the slope is mostly straight. By importing the captured values into MATLAB, the output can be changed to 1 when above zero or 0 when below zero, which simulates the comparator output as seen by the microcontroller. The following image is the resulting waveform, zoomed in to show one commutation period.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/matlabgraph.png' />
</p>
<p align='center'>
<b>Figure 4. Virtual neutral voltagecompared with floating phase voltage.</b>
</p>

The spikes from PWM are very unpredictable, and can sometimes happen before the actual zero crossing event, so the comparator output must be digitally filtered to reconstruct the real zero crossing point as accurately as possible. The implementation of this comparator method is shown below, using an abstract circuit diagram.

<p align='center'>
<a href='http://dl.dropbox.com/u/6783818/Brushless/figures/virtualneutral.PNG'>http://dl.dropbox.com/u/6783818/Brushless/figures/virtualneutral.PNG</a>
</p>
<p align='center'>
<b>Figure 5. Virtual neutral voltagecompared with floating phase voltage.</b>
</p>

The total commutation cycle encompasses 360 electrical degrees and is broken up into 6 steps, so one commutation period is 60 electrical degrees. At the time of commutation, one of the driven wires is swapped with the floating phase, so each wire is energised for 120 electrical degrees, or 2 commutation periods, as is seen in the figure below.

<p align='center'>
<a href='http://dl.dropbox.com/u/6783818/Brushless/figures/bemf%26driving.PNG'>http://dl.dropbox.com/u/6783818/Brushless/figures/bemf%26driving.PNG</a>
</p>
<p align='center'>
<b>Figure 3. Six step commutation process and back-EMF waveforms.</b>
</p>

Successful and accurate detection of the zero crossing point results in smooth, efficient operation of the motor.