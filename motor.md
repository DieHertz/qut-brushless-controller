# Basic Motor Theory #

Brushed DC motors have seen extensive use since their invention in the early 19th century. They are cheap and easy to use, only needing a voltage source to operate. They work by changing the polarity of the rotor's electromagnets (commutating) at precisely the right time to achieve the most amount of torque and efficiency. Conductive "brushes" make constant contact with the rotor, which produce sparks, noise (both electrical and audible), and a considerable friction force, reducing efficiency.

A solution to this is moving the electromagnets to the stator, and removing the brushes completely. This makes motor design much simpler, but shifts the task of commutation to complicated digital circuits. Below is a table summarising the main differences between the two types of DC motors:

| **Brushed** | **Brushless** |
|:------------|:--------------|
| Cheap       | High efficiency |
| Easy to operate and control | High power to weight ratio |
| Full torque from zero RPM | More suited to constant operation |
|             | Extended service life (low maintenance) |

Brushless DC motors have gained enormous popularity in recent years in the remote control aircraft industry. Their high efficiency and power-to-weight ratio make them top candidates for limited battery life, small-scale aircraft. One disadvantage is that operation at sub-1000 RPM is almost impossible without the use all extra hall-effect sensors, especially when a load is present. It is also hard to provide 100% torque at motor startup, as the rotor position is unknown. For these reasons, they aren't as popular in stop-start applications like RC cars. This project focuses on the sensorless type of motor (i.e. no hall sensors).

## Brushless: How It Works ##
A basic understanding of electromagnets and how a simple brushed DC motor works is assumed knowledge. If you would like a refresher, there are plenty of online resources available (e.g. http://pcbheaven.com/wikipages/How_DC_Motors_Work/).

A brushless motor works on exactly the same basic theory, the only difference is how commutation is achieved. A brushless motor will have 3 leads, and 3 Y-connected coil circuits on the stator, as seen below, right. It is essentially a 3-phase, permanent magnet synchronous AC motor, but the alternating current is produced from a DC power source using an inverter.

<p align='center'>
<a href='http://dl.dropbox.com/u/6783818/Brushless/figures/simple_brushless.PNG'>http://dl.dropbox.com/u/6783818/Brushless/figures/simple_brushless.PNG</a>
</p>
<p align='center'>
<b>Figure 1. Graphical representation of a Y-connected brushless motor.</b><a href='https://code.google.com/p/qut-brushless-controller/wiki/references'> <sup>[1]</sup></a>**</p>**

Many motor variations exist, but the coils are always in multiples of 3, and the permanent magnets (poles) in multiples of 2. A common configuration is 12 coils and 14 poles, as can be seen in the picture on the [home page](home.md). A large number of poles and coils results in larger torque, and a smoother torque curve.

By energising 2 wires at a time, the polarity of the coils can be chosen. As can be seen in the figure (right) above, there are 6 possible energised states, and stepping through these in the correct order will cause the motor to turn. As with a typical brushed motor, if the commutation occurs at precisely the right time, torque is maximised and the motor will accelerate until an equilibrium speed is reached, which depends on applied voltage and load torque. Due to [Faraday's Law of Induction](http://en.wikipedia.org/wiki/Faraday's_law_of_induction), the spinning magnets inside the motor induce a current in the coils which opposes the applied voltage, called the back electromotive force (back-EMF). This voltage determines the natural equilibrium speed given a certain applied voltage and load.

The goal of a brushless ESC is to find this equilibrium speed, and commutate the motor in the most efficient way possible. It must also automatically adjust to changes in load and voltage as fast as possible to maintain maximum torque. If commutation is too slow, the rotor will reach the next commutation point earlier than expected, resulting in a jittery stop-start operation, and increased current draw (no movement = no back-EMF). If the commutation is too fast, the rotor will not be able to keep up with the electrical rotation of the stator, and will loose sync and stall completely.

Without sensors, the only available feedback from the motor is the voltage on each motor wire. Figure 2 below shows the waveform of each wire during operation.

<p align='center'>
<a href='http://dl.dropbox.com/u/6783818/Brushless/figures/phaseabc.PNG'>http://dl.dropbox.com/u/6783818/Brushless/figures/phaseabc.PNG</a>
</p>
<p align='center'>
<b>Figure 2. Phase A, B and C waveforms during operation</b>
</p>

These waveforms are fed through voltage divider circuits to make them safe for the microcontroller to read. Figure 3 shows only phase A, with accompanying highside and lowside mosfet logic signals. Notice only the lowside MOSFETs are switched using PWM.

<p align='center'>
<a href='http://dl.dropbox.com/u/6783818/Brushless/figures/phasea.PNG'>http://dl.dropbox.com/u/6783818/Brushless/figures/phasea.PNG</a>
</p>
<p align='center'>
<b>Figure 2. Phase A waveform, with accompanying MOSFET logic</b>
</p>

The phase is "floating" when neither of it's MOSFETs are switched on, and this is when the rotor position can be sensed. See [Knowing When To Commutate](zerocrossing.md).