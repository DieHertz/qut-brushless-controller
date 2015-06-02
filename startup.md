# Motor Startup Tuning #

Motors will behave differently depending on their size. Larger motors will have more inertia and require a different starting sequence. Follow the instructions below to tune the ESC for your motor:

  1. In the config folder, copy one of the "`motor.h`" files, and give it an easy to remember name, e.g. the model number of the motor.
  1. Change `STARTUP_LOCK_PWM` to 0.1\*PWM\_TOP, `STARTUP_RLOCK_LOOPS` to 30, and `STARTUP_RLOCK` to 100. If you attempt to run the motor, it will run like a stepper motor for a short while. If the motor struggles or is slow, keep raising the PWM until the transition between steps is smooth (but not bouncing or too forceful).
  1. If the motor takes a while to settle between steps, even with a low PWM, increase the lock wait time with `STARTUP_RLOCK`.
  1. Put `STARTUP_RLOCK_LOOPS` back to about 3.
  1. The "TICKS" settings are unsigned 16-bit values (0 to 65535). To begin with, set `STARTUP_TICKS_BEGIN` and `STARTUP_DURATION` to a large value, like 65000.
  1. Set `STARTUP_TICKS_END` between 10000 and 20000, find a value which gives a reliable start every time.
  1. First, reduce `STARTUP_TICKS_BEGIN`, then `STARTUP_DURATION` to the lowest values possible while still maintaining a reliable startup.
  1. You should not need to change `STARTUP_STABILISE`, but experimenting with it cannot hurt.

Once familiar, this process should not take more than a few minutes for each motor. A new startup sequence is under development which should eliminate the need to tune for each motor.