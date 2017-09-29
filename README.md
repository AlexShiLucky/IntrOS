IntrOS
=======

Free, simple and tiny cooperative operating system (OS) designed for deeply embedded applications.
Target: ARM Cortex-M, STM8, AVR8 families.
It was inspired by the concept of a state machine.
Procedure executed by the task (task state) doesn't have to be noreturn-type.
It will be executed into an infinite loop.
There's a dedicated function for immediate change the task state.

Features
--------

- kernel works in cooperative (non-preemptive) mode only
- kernel can operate in tick-less mode (32-bit timer required)
- signals (auto clearing, protected)
- events
- flags (any, all)
- barriers
- semaphores
- mutexes
- condition variables
- memory pools
- message queues
- mailbox queues
- job queues
- timers (one-shot, periodic)
- c++ wrapper
- all documentation is contained within the source files
- examples and templates are in separate repositories on [GitHub](https://github.com/stateos)
- archival releases on [sourceforge](https://sourceforge.net/projects/intros.stateos.p)

Targets
-------

ARM CM0(+), CM3, CM4(F), CM7

License
-------

This project is licensed under the terms of [GNU GENERAL PUBLIC LICENSE Version 3](http://www.gnu.org/philosophy/why-not-lgpl.html).
