# JPEGcamera_MSP430
Using serial JPEG camera on TI MSP430 microprocessor

This code shows how to connect to the Adafruit VC0706 JPEG video camera.
It uses a port of their Arduino library, customized to the TI MSP430F5529, with the Energia libraries.

This initial version does work successfully, but with some limitations. It uses the PetitFS filesystem library for the SD card, so it requires a pre-created file such as 'log.txt' file on an SD card, filled up with (more bytes than expected of) some generic character like spaces.

This code takes a snapshot when you press the S2 pushbutton, then transfers the data to SD card "log.txt" file (in jpg format).  Next, open this file in a hex editor like HexEdit, remove all the extraneous spaces at the end, and resave it as *.jpg file .
