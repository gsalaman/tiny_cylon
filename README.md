# ATTINY85-based "cylon" lights
Simple code driving a 595 board with an ATTINY85.

## Using an UNO as a a ATTINY programmer
First, add the tiny board manager package under "preferences".  Paste the following text into the "Additional Boards Managers 
URLS" field...if you've got a bunch, you'll need to add a comma separator.
```
https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json
```

Next, install the board manager package by selecting:  "Tools->Board->Boards Manager" and type attiny.  It should find the 
tiny package by David Mellis.

We now need to setup the UNO as a programmer.  Download the built-in example #11 (ArduinoISP) and program it onto your UNO.

Next, we need to hook up the tiny to the Uno for programming.  Here are the connections:

| tiny pin # | tiny label | arduino pin |
|------------|------------|-------------|
| 1 | reset | 10 |
| 4 | GND   | GND |
| 5 | Pin 0 | 11 |
| 6 | Pin 1 | 12 |
| 7 | Pin 2 | 13 |
| 8 | VCC | +5v |

You'll also want a 10 uF cap running across the arduino's reset pin to gnd.

Now you need to burn in the bootloader to the tiny.  Change your board settings as follows:
Board -> ATtiny25/24/85
Processor -> ATtiny85
Clock -> Internal 8 MHz
Programmer -> Arduino as ISP

Then click "burn bootloader".  This should only need to be done once per chip.

...and now, you are ready to upload the custom sketch.  I've got the cylon code so that it attaches to 5, 6, and 7 on the Tiny...
and it works with either the 5v or a simple coin cell!!!

## Tiny Pins
From the arduino board file:
```
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2)  Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+
```
