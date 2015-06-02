# Driving The MOSFETs #

#### **CAUTION: Presented below are an active-low circuit for both high- and low-side switches. These cannot be used in conjunction with each other, because when no MCU high output is present to turn them off, both MOSFETs will be on at the same time, causing a short circuit in the power supply, and destroying both MOSFETs.** ####

To get the best possible efficiency from an ESC, the MOSFETs must be properly driven to ensure a fast on/off transition, and reduce waste current. Several schemes exist to accomplish this, and are listed below in order of descending efficiency. All 3 phases require a high-side and low-side MOSFET, which means a minimum of 6. The circuits shown below only show the requirements for one phase, and must be copied for all 3 phases. MOSFETs can be placed in parallel to increase current capability, but this is only recommended when using a MOSFET driver.

## High and Low: Dedicated MOSFET Driver ##

_**Advantages**
  * Provides the fastest possible switching time.
  * Allows the use of high-side N-channel MOSFETs.
  * Internal low-voltage cut-off (Impossible to under-drive the mosfets, which can damage them).
  * Can handle huge MOSFET supply voltages.
  * Easy to use. Set and forget._

_**Disadvantages**
  * Expensive.
  * Take up more space, especially on small-scale SMD boards._

Using a dedicated MOSFET driver is the easiest, but also most expensive solution. For a beginner who is worried about the technicalities of driving a MOSFET, using a driver is the best solution. When using a supply voltage above 15V, it is highly recommended to use a MOSFET driver, as most MOSFETs have a V<sub>gs</sub> limit of about 20V. An example circuit using the IR2101 is shown.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/schematics/IR2101.png' />
</p>
<p align='center'>
<b>Figure 1. An example IR2101 circuit for one phase.</b>
</p>

V+ can be anything up to 600V, but the provided Vcc must be between 10-20V. This is not a problem if the power supply is in that range, but if not, it must be provided via a voltage regulator or voltage doubler.


## Low-Side MOSFET ##

The circuits following will show only low-side driving schemes, with place holder high-side circuits. Each circuit must be copied for all 3 phases. Only N-channel MOSFETs can be used on the low-side switch.


### Logic Level MOSFETs ###

_**Advantages**
  * Very simple circuit.
  * Easy to drive, direct connection to MCU._

_**Disadvantages**
  * Not as fast as a MOSFET driver._

If not using a MOSFET driver, it is highly recommended to use logic level FETs. These have a much lower gate drive requirement, and can be efficiently driven from MCU logic. If you are not sure if a MOSFET is logic level, check the datasheet for V<sub>gs (th)</sub>, it should be between 1 to 3 volts. An example logic level FET circuit is shown below.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/schematics/lowside-1.png' />
</p>
<p align='center'>
<b>Figure 2. An example low-side logic-level MOSFET circuit.</b>
</p>


### Regular MOSFETs ###

_**Advantages**
  * Sometimes cheaper and more available than logic-level MOSFETs._

_**Disadvantages**
  * High gate drive voltage required.
  * Active-low. MCU logic is reversed.
  * Drains current from power source to turn the FET off.
  * Slowest low-side driving scheme._

Regular MOSFETs require a higher V<sub>gs</sub> to fully saturate, usually about 10V. They can be recognised by their V<sub>gs (th)</sub> value, which is in the range of 2 to 4 volts, and also by looking at the V<sub>ds</sub> vs. I<sub>d</sub> graph. If it does not show a curve for a low V<sub>gs</sub>, e.g. 3.3V, then it is probably a regular FET and needs 10-20V V<sub>gs</sub> to fully saturate. You should only use these types of FETs if you can provide 10-20V to drive them, and even if you can, they will be less efficient than logic level FETs due to the nature of the switching circuit. An example circuit is provided.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/schematics/lowside-2.png' />
</p>
<p align='center'>
<b>Figure 3. An example low-side regular MOSFET circuit.</b>
</p>

The reason two 470Ω resistors are used is to balance the gate charge and discharge current, and also minimise short-to-ground current when the transistor is conducting. The can be exchanged for one resistor from E to gnd, but the MOSFET will turn off slower.


## High-Side MOSFET ##

The circuits following will show only high-side driving schemes, with place holder low-side circuits. Each circuit must be copied for all 3 phases. Using logic-level devices is not as important for high-side FETs, but the power supply must be sufficient to drive the V<sub>gs</sub> to a suitable level. e.g. if V+ is less than 10V, logic-level FETs should be used.


### P-Channel ###

_**Advantages**
  * Simple circuit, easy to drive_

_**Disadvantages**
  * P-MOS devices are much less popular than N-MOS, and hence more expensive.
  * It is very difficult to find P- and N-MOS devices with the same voltage and current ratings.
  * Drains current while in the on state._

P-MOS are just like N-MOS with reversed polarity. Be careful when connecting the device, do not mix up source and drain. This is a popular choice if not using a MOSFET driver. Below is a recommended circuit diagram. The two 470Ω resistors can be substituted for a single resistor (in the upper position) for simplicity. Lower resistor values will reduce turn-on time, but also increase current draw while the MOSFET is conducting. Since the MOSFET is only conducting for 2/6 of the commutation stages, average current draw will be 1/3 of calculated value. Times by 3 (one for each phase), means average current draw for all 3 phases will be V/R. Adjust depending on preference.

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/schematics/highside-1.png' />
</p>
<p align='center'>
<b>Figure 4. An example high-side P-channel circuit.</b>
</p>


### N-Channel ###

_**Advantages**
  * Less parts count.
  * Low and high -side switches can have matching ratings._

_**Disadvantages**
  * Requires a bootstrapping circuit to work.
  * Active-low. MCU logic is reversed.
  * Cannot be used with 100% PWM (redundant in ESC applications, the MOSFETs are always switching)._

Usually, N-MOS devices can not be used in a high-side switching application. To saturate the device, V<sub>gs</sub> must be above V<sub>s</sub>. In a high-side orientation, when the MOSFET begins to conduct, V<sub>s</sub> will rise to a voltage very close to V<sub>d</sub> (the supply voltage). If you are supplying the same voltage, or even worse; a 5V logic voltage to the gate; absolutely nothing will happen (voltage between source and gate is 0). To switch on the MOSFET, a voltage ABOVE the supply is required. It is quite impractical to have another voltage supply simply to drive the MOSFETs, so a bootstrapping circuit is utilised.

The main principle behind bootstrapping is that voltage is stored in a capacitor, and then used as a floating supply to essentially double the supply voltage. Once the gate capacitance is charged, the capacitor will slowly discharge through the resistors to ground, causing the MOSFET to turn off, but this should not be a problem in an ESC, where the MOSFET is on for a maximum of about 10 microseconds during low RPMs. If a more in-depth discussion of boot-strapping is desired, please leave a comment. Here is a sample circuit. Note it is active-low logic. The capacitor should be in the range 4.7uF to 10uF. As discussed above, the 470Ω resistors can be scaled down to reduce lag time, but will drain more average current than a P-MOS configuration (current is flowing during off-time rather than on-time).

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/schematics/highside-2.png' />
</p>
<p align='center'>
<b>Figure 5. An example high-side N-channel circuit.</b>
</p>