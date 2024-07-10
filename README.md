Alarm Quack
===========

Description
-----------

This is very similar to the traditional `leave` command-line utility,
with a few enhancements:

-   Custom reminder messages instead of simply “Time to leave.”
-   Plays a distinctive quack sound on the computer’s speaker. (No other
    program quacks for attention, so if my computer quacks, I know it
    must be reminding me of something significant.)
-   Time is specified using the unambiguous 24-hour clock, so no more
    am/pm confusion.
-   Can schedule reminders relative to the current time (e.g. 20 minutes
    from now) as well as at a specific absolute time of day.
-   Can list the process ID’s of all pending alarms.

Installing
----------

Quack builds on both MacOS and Linux. With a few minor changes to list.c
and quack.c, it should build on most fully POSIX-compliant operating
systems. (Quack relies on certain particulars of how POSIX-compliant
kernels launch and manage processes, so *will not* run properly on
Windows. Sorry.)

To build, just type:

    make -f Makefile.linux

or:

    make -f Makefile.macos

You will then have to install `quack.mp3` (MacOS) or `quack.ogg` (Linux)
in your home directory’s `misc` subdirectory. If you want this file to
be kept elsewhere, change the logic in `quack.c` before building.

### Prerequisites

A C compiler, a sound card, and on Linux the `paplay` command must be
installed.

Running
-------

`quack help` will print out a brief summary of allowed syntax. Some
examples follow:

A lunchtime reminder:

    quack at 12:00 LUNCH

To check the oven in 15 minutes:

    quack in 15 Check on cookies

By default quack reminds you five minutes before, one minute before, at
the requested time, and every minute thereafter for up to 10 times. To
make it shut up, run `quack list` to determine the ID of the quack
process and then `kill` it.

If you only want a single alert, use the `once` modifier:

    quack once in 5 Check again
