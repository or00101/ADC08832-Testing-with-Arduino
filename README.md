# ADC08832-Testing-with-Arduino

This code was meant to be used in order to test the ADC08832 (Analog to Digital Converter IC [Texas Instruments]).
The purpose of this experiment is to get a working knolegde on how to debug the mentioned ADC IC with Arduino.

The schematics for this experiment:

<img src="https://github.com/or00101/ADC08832-Testing-with-Arduino/blob/main/testing-schematics.png" width="500"/>

> The appropriate pull-down resistors should be of 1kOhms. But this hasn't been tested yet.


The code will let you focus on the timing graph (Fig 21) seen on page 10 of the IC's datasheet:
<img src="https://github.com/or00101/ADC08832-Testing-with-Arduino/blob/main/ADC08832%20Timing%20Graph.png" width="900"/>

Once assembled and plugged to the scope, after triggering the scope to the falling of the CS (CHIP SELECT) pin on the IC, we can see:

<img src="https://github.com/or00101/ADC08832-Testing-with-Arduino/blob/main/SCOPE_MEASUREMENT.png" width="900"/>

> SCOPE MEASUREMENT: (CLK - YELLOW, CS - BLUE, DI - PINK, DO - GREEN)

We can see we measured: 
> MSB DATA: 00101110
and:
> LSB DATA: 01110100

which is exactly what we wanted!




# Future development:

ELECTRONICS:

> 1. Testing with appropriate pull-down resistors
> 2. Measuring correspondance of DO values to CH0 and CH1 actual values.

CODE:

> 1. Taking into account the t_pd as an added time delay between CLK-FALL and the digitalRead(DO); should give a more stable measure.
> 2. getting rid of code reppetition and better organizing functions.


PICS:

> 1. get SCREENSHOT of off the scope instead of taking a photo with my phone.
