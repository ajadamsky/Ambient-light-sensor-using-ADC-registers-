 
  /*  Code written by Adrian Adamski
      10th May 2020 */

#include <Arduino.h>
#include <stdint.h>

#define GCLK_BASE ((uint8_t*)(0x40000C00))
#define GCLK_CLKCTRL *((uint16_t*)(GCLK_BASE + 0x2))

#define ADC_BASE ((uint8_t*)(0x42004000)) 
#define ADC_CTRLA *((uint8_t*)(ADC_BASE + 0x0))
#define ADC_CTRLB *((uint16_t*)(ADC_BASE + 0x04))
#define ADC_REFCTRL *((uint8_t*)(ADC_BASE + 0x01))
#define ADC_INPUTCTRL *((uint32_t*)(ADC_BASE + 0x10))
#define ADC_SWTRIG *((uint8_t*)(ADC_BASE + 0x0C))
#define ADC_INTFLAG *((uint8_t*)(ADC_BASE + 0x18))
#define ADC_RESULT *((uint16_t*)(ADC_BASE + 0x1A))

#define INPUT_PIN 9 // Button
int ledPin = A0; // LED

void setup()
{
    Serial.begin(9600);
    pinMode(INPUT_PIN, INPUT_PULLUP); // Button
    pinMode (ledPin, OUTPUT); // LED
    while (!Serial);

    GCLK_CLKCTRL = (0x0 << 8) | (0x1E << 0) | (1 << 14);  // Enable clock 0 for the ADC
    ADC_CTRLA = (1 << 1);                                 // Enable the ADC
    ADC_CTRLB = (0x3 << 4) | (0x6 << 8);                  // Set the resolution to 8 bit and set the prescaler to /256
    ADC_REFCTRL = (0x2 << 0);                             // Set the ADC reference voltage to INTVCC1 
    ADC_INPUTCTRL = (0xF << 24);                          // Set the ADC input gain to DIV2
    ADC_INPUTCTRL |= (0x18 << 8) | (0x0B << 0);           // Set ADC input to GND and pin 11 (used by light sensor on the MKR ENV board)
}

void loop()
{
    ADC_SWTRIG = (1 << 1);                                // Start a conversion
    while (ADC_INTFLAG & (1 << 0) == 0);                  // Wait for the conversion to finish
    
    if (digitalRead(INPUT_PIN) == LOW) {                  // Pressed button

    uint32_t value = ADC_RESULT;                          // Read the result and print it
    Serial.print("Light value = ");
    Serial.println(value);

    int result = digitalRead(INPUT_PIN);
    result = map(value, 0, 1023, 0, 255);                 // LED fully off in the dark and fully on in bright 
    digitalWrite(ledPin, result);
    
    Serial.println();
    delay(100);
  }
}     

