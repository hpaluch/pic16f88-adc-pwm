# ADC and PWD on PIC16F88

Project goal: read potentiometer value using ADC and output PWM to LED.

WORK IN PROGRESS! Status:
- toggling LED on RA1/PIN18 (PDIP package) every 250ms

Used HW:
- [PICDEM Lab Development Kit][DM163045] 
- [PIC16F88][PIC16F88] - included with latest series of DM163045

# C Version

Project under [pic16f88_adc_pwm_c.X/](pic16f88_adc_pwm_c.X/). Requires latest software:
- MPLAB X IDE v6.05
- XC8 v2.40
- DFP 1.3.42


# Resources

- used my PIC16F88 project as template:
  - https://github.com/hpaluch/pic16f88-comp-ccp-ex.X

[DM163045]: http://www.microchip.com/Developmenttools/ProductDetails/DM163045 "PICDEM Lab Development Kit"
[PIC16F88]: https://www.microchip.com/wwwproducts/en/PIC16F88 "PIC16F88 Overview"
