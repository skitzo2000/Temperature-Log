Temperature-Log
===============

Basic temp log setup using mysql, php, python, and Arduino


I created this for monitoring Fermentation Temperatures of Beer.  I use a laptop running centos with a LAMP stack installed.  An Arduino Deci, and three dallas temp sensors.  *Note that the arduino is connected to the laptop via USB.

Note that a few of these scripts I've modified for my specific use case, I've tried to document the files accordingly, but As this is a beta version there may be bugs

Two of the scripts I've used I found from somewhere online, but I don't recall where as I wrote this a long time ago and just wanted to get it docuemnted.  The Daemon Script and USB reset script I did not write.  But I wanted to provide if anyone wants to use this project.

Note that templog folder contains the arduino sketch.  The other three file would run on the server/computer.  I've written it to run from the root user directory, but this can be changed pretty easily.
