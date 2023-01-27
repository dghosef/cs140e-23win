-------------------------------------------------------------------------
### Lab extensions

There's a lot more you can do.  We will be doing a bunch of this later
in the class:

  - Save state onto the stack itself.

  - Make versions of the `libpi` `delay` routines that use your function rather than
  busy wait.  Make sure to check if threads are enabled in `rpi_yield()`!

  - Have a `sleep_until_us(us)` to put the current thread to sleep with a
  somewhat hard-deadline that it is woken up in `usec` micro-seconds.  Keep
  track of your cumulative error to see how well you're scheduling is doing.

  - Tune your threads package to be fast.  In particular, you can avoid
  context switching when a thread is run for the first time (there is
  no context to load) and you don't thave to save state when it exits
  (it's done).  You can also try tuning the interrupt handling code,
  since it is at least 2x slower than optimal.  (I'm embarrassed, but
  time = short.  Next year!)

   - See how many PWM threads you can run in `4-yield-test`.

   - Make fake pre-emptive threads. You can emulate pre-emptive threads using our threads by yielding every time you enter or exit a function. If you implement `__cyg_profile_func_enter` and `__cyg_profile_func_exit`, those functions will run on the entry/exit of each function call every single time. 
