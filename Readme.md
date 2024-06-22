# Meine_sery

A basic serial layer for user interaction, facilite the first steps using serial ;) .

### Meine_sery overview:

  - init_sery ==> will handle all stuf related to initializing the serial port communication.

  - cleanup_sery ==> will clean the stuff before leaving , close the port and free all buffers..

  - open_sery ==> will open the serial port.

  - read_from_sery ==> read data from serial port.

  - write_to_sery ==> will handle frame write to the serial port.


### Meine_sery why?

First time getting into using basic syscalls and dealing with serial over linux will be so overwhelming, i created Meine_sery cause of that, it helps and make the first steps more easier for newbies.

* Meine_sery uses "open()" , "close()", "read()", and "write()" also it uses "poll()" as system calls for handling serial manipulation.
