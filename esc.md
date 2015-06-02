# What Is An ESC? #

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/KF40A.jpg' />
</p>
<p align='center'>
<b>Figure 1. Turnigy K-Force 40A Brushless ESC</b>
</p>

ESC stands for electronic speed controller. The term is most often used in the remote control industry. High-end RC vehicles utilise a modular design where parts can easily be replaced if they fail, and help with troubleshooting. An ESC is usually an enclosed unit (often just shrink-wrap, as above), with connections for power, output (motor), and input, usually in the form of standard logic-level RC servo pulses, as shown below, with 1->2ms pulses representing 0->100% speed control (or in some designs, full reverse -> stop -> full forward)

<p align='center'>
<img src='http://dl.dropbox.com/u/6783818/Brushless/figures/servo.jpg' />
</p>
<p align='center'>
<b>Figure 2. Standard Servo Pulse Waveforms</b>
</p>

There are variations of ESCs, and can be designed for either brushed or brushless motor. This wiki is dedicated to brushless ESCs only. An off-the-shelf ESC is a perfectly respectable solution to driving a brushless motor, but often times engineers or hobbyists will want to customise the firmware, develop additional functionality, receive system feedback and real-time diagnostics, or incorporate the ESC into the main design of a project (i.e. use the same PCB). It also allows customisation of the drive stage to accommodate for larger/smaller motors.

Using this wiki and the accompanying source code, the user should be able to develop a robust, customisable brushless ESC to meet their specific project demands.