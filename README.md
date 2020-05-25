# Ambient light sensor using ADC registers

Ambient light sensor controller Arduino MKR WiFi 1010 with MKR ENV Shield. More advanced programming based on manually written ADC registers in SAM D21 microchip. University project.

Details:

- Manually configured registers with defines for each specific address 
- LED connected to analog output
- Button connected to analog input
- Configured ADC clock to use Generic Clock 0
- Configured ADC with a resolution of 8 bit / 256 prescaler
- ADC reference voltage set to INTVCC1
- ADC input gain set to DIV2
- Reads the value from MKR ENV Shield light sensor by pressing the button
- LED fully on in bright room and fully off in dark room




