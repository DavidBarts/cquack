Alarm Quack
===========

Description
-----------

This is very similar to the traditional ``leave`` command-line utility,
with a few enhancements:

* Custom reminder messages instead of simply “Time to leave.”
* Plays a distinctive quack sound on the computer’s speaker.
  (No other program quacks for attention, so if my computer quacks,
  I know it must be reminding me of something significant.)
* Time is specified using the unambiguous 24-hour clock, so no more
  am/pm confusion.
* Can schedule reminders relative to the current time (e.g. 20 minutes
  from now) as well as at a specific absolute time of day.
* Can list the process ID’s of all pending alarms.
* Tries as hard as possible to work around how processor sleep states
  caused by power management affect sleeping and alarms.

Installing
----------

Quack builds on both MacOS and Linux. With a few minor changes to ``list.c``
and ``quack.c``, it should build on most fully POSIX-compliant operating
systems. (Quack relies on certain particulars of how POSIX-compliant kernels
launch and manage processes, so *will not* run properly on Windows. Sorry.)

To build, just type::

    make -f Makefile.linux

or::

    make -f Makefile.macos

You will then have to install ``quack.mp3`` (MacOS) or ``quack.ogg`` (Linux)
in your home directory’s ``misc`` subdirectory. If you want this file to be
kept elsewhere, change the logic in ``quack.c`` before building.

Prerequisites
~~~~~~~~~~~~~

A C compiler, a sound card, and on Linux the ``paplay`` command must be
installed.

Running
-------

``quack help`` will print out a brief summary of allowed syntax. Some examples
follow:

A lunchtime reminder::

    quack at 12:00 LUNCH

To check the oven in 15 minutes::

    quack in 15 Check on cookies

By default quack reminds you five minutes before, one minute before, at the
requested time, and every minute thereafter for up to 10 times. To make it
shut up, run ``quack list`` to determine the ID of the quack process and then
``kill`` it.

If you only want a single alert, use the ``once`` modifier::

    quack once in 5 Check again

Specifying Times
~~~~~~~~~~~~~~~~

Times are specified in hh:mm format. For ``quack at`` times are on a 24-hour
clock, and both hours and minutes must be specified; the alarm will always be
set for a time in the next 24 hours. For ``quack in``, times are specified as
a number of hours and minutes in the future, with the hours portion
optional.

Listing Processes
~~~~~~~~~~~~~~~~~

``quack list`` will list all running ``quack`` processes, which is useful if
you want to silence a given alarm (i.e. kill its process).

Silencing an Alarm
~~~~~~~~~~~~~~~~~~

The way to silence an alarm is to kill its associated process. See “Listing
Processes” immediately above. If you log out or close the window associated
with one or more ``quack`` processes, it will also silence the associated
alarms.

Power Management and Alarms
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is something of a problem. If a computer goes to sleep, it cannot issue
alarms. The cure is to configure power management so that your computer never
goes into a deep sleep if receiving alarms is important to you. (This problem
is not particular to ``quack``; it affects any program whose job it is to
issue asynchronous reminders.)

A further wrinkle is that if a computer goes to sleep, time essentially ceases
to pass so far as the alarm(2) system call (which is what ``quack`` uses under
the hood) is concerned. This causes many alarm clock programs (and the
traditional ``leave`` command) to issue alerts which are late by the amount of
time the processor spent in a deep sleep state. ``quack`` works around this
glitch by doing its sleeping in short “naps,” awakening at regular intervals to
check the current time. So long as your computer is not in a deep sleep at the
scheduled time of the alarm, the alarm should get raised on time or close to it.
