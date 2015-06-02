# Safety Issues #

The safety issues listed below are not so much human safety, as the voltages involved are usually quite low, and direct current, but more to protect your components from an early death.

  * Batteries have a very low equivalent series resistance (ESR) which means they are capable of high current. This means if you accidentally make a short to ground, you will know about it, and something will go boom. Triple check all connections before powering up your system, and be careful of loose wires.
  * Microcontrollers require 3.3 to 5 volts for a reason. Be careful with high voltages around delicate logic level circuits, they will always come out second best.
  * Incorrectly driving a MOSFET, or switching it at a very high frequency, can result in it operating in the linear region for longer than it should, which will increase power dissipation, causing it to heat up. MOSFETs can handle a certain amount of heat, but doing this for too long or too hot will destroy the MOSFET. If your MOSFETs feel hot to the touch when they probably shouldn't, stop operation immediately and find the cause of the problem.
  * It is possible to turn on both high and low MOSFETs through software. This is very bad, and will blow something up. A solution to this is to check if the low-side is on before switching on the high-side, and visa versa.
  * Never push a motor higher than it is designed to go. It may get very hot and damage the internal coils, or even mechanically fail and become a hazard. Make sure all props and attachments are securely fixed before running a motor.