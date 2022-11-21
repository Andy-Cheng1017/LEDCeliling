#include "src/Adafruit_INA219/Adafruit_INA219.h"
Adafruit_INA219 ina219;

void setup()
{
    pinMode(10, OUTPUT);
}
void loop()
{
    digitalWrite(10, HIGH);
}