# MOSFETs: An Introduction #

Whether you have never used a MOSFET before, or simply need a quick summary to refresh your memory, this section should get you up to speed with using MOSFETs in your ESC design.


## MOSFET As A Switch ##
A MOSFET is very similar in operation to a bipolar-junction transistor, but is voltage controlled rather than current controlled. In can also operate in it's linear region, similar to a BJT in an amplifier, but is rarely used in this way. It finds it's main use as a very fast, electronically activated switch, with very large voltage and current handling capabilities. Due to their speed and efficiency, they are ideal for applications like motor speed control using pulse width modulation (PWM). The circuit symbol for an N-channel MOSFET is shown below.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/N-MOS.png' />
</p>
<p align='center'>
<b>Figure 1. Simple MOSFET circuit symbol (N-channel pictured).</b>
</p>

A MOSFET has 3 connections: gate, source, and drain, with substrate connected internally. Voltage between gate and source (V<sub>gs</sub>) controls the current flow from drain to source. A MOSFET will not conduct in the reverse direction, but due to their construction, most have an inherent reverse diode which prevents them from surge currents such as from an inductor discharging. MOSFETs can be made in different ways which determine how they operate. Only enhancement mode MOSFETs will be discussed in this wiki, both N-channel and P-channel. An N-channel device is most similar in operation to an NPN transistor, and vis with P-channel and PNP. Due to the electrical characteristics, the easiest way to switch an N-MOS is on the low side of a load, and a P-MOS on the high side, as below.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/schematics/n-channel.png' /> <img src='http://dl.dropbox.com/u/6783818/Brushless/schematics/p-channel.png' />
</p>
<p align='center'>
<b>Figure 2. Common arrangements for MOSFET switching.</b>
</p>

Notice that the P-MOS circuit is essentially just an N-MOS flipped vertically (even the Source and Drain connections).

If using the N-MOS circuit, connecting the gate to the same voltage level as source (in this case, ground) will turn the MOSFET off, and connecting it to a voltage above V<sub>gs (threshold)</sub> will turn it on. Note that V<sub>gs (th)</sub> is the threshold at which the MOSFET will switch OFF. To achieve a fully saturated on-state, a higher voltage is needed, usually 10V, but if using a logic-level MOSFET, can be as low as 3.3V. Logic level FETs are highly recommended when interfacing with microcontrollers.

Now consider the P-MOS circuit. All polarities are reversed, which means to turn it off, the gate must be connected to source (V+). To turn it on, a negative V<sub>gs</sub> (relative to V<sub>s</sub>) must be supplied, usually ground. As you can see, if gate is directly connected to an MCU pin, it will have a direct connection to V+, possibly damaging the delicate circuitry inside the chip. Therefore an extra transistor is needed to supply a ground potential. Also, the maximum limit for V<sub>gs</sub> is usually about 20V, so switching a load higher than this can damage the MOSFET.

## Driving A Motor ##

If these two sub-circuits are combined, the load can be connected to either V+ or Ground, and this configuration is called a half-bridge. Brushed DC motors can be connected to two half-bridges, and the direction of current through the motor can be reversed. This circuit is called a H-bridge, due to it's shape resembling the letter 'H'.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/H-bridge4.gif' />
</p>
<p align='center'>
<b>Figure 3. H-Bridge circuit representation.</b>
</p>

If either the high or low MOSFETs (or even both) are supplied with a PWM signal, the average voltage supplied to the motor can be varied, resulting in varying motor speed. This is the basic principle of an ESC power stage.

#### WARNING: If both high and low MOSFETs are activated at the same time, the power source will be shorted to ground causing massive shoot-through current. Depending on how long this lasts, the MOSFETs can get extremely hot and possibly explode. ####

A brushless ESC uses the same principles, and applyies is to a 3-phase system. The direction of the motor is determined by commutation order rather than a simple on/off scenario. The basic 3-phase half-bridge structure is shown below:

<p align='center'>
<a href='http://dl.dropbox.com/u/6783818/Brushless/figures/powerstage.PNG'>http://dl.dropbox.com/u/6783818/Brushless/figures/powerstage.PNG</a>
</p>
<p align='center'>
<b>Figure 4. Three parallel half-bridges, used to drive a brushless motor.</b><a href='https://code.google.com/p/qut-brushless-controller/wiki/references'> <sup>[1]</sup></a>