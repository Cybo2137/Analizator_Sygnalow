#include <Arduino.h>

void setup() {
  pinMode(9, OUTPUT); // Pin 9 w Uno obsługuje PWM
}

void loop() {
  // Płynne zwiększanie wypełnienia sygnału (0 do 255)
  for(int i = 0; i <= 255; i++) {
    analogWrite(9, i);
    delay(15);
  }
  // Płynne zmniejszanie wypełnienia
  for(int i = 255; i >= 0; i--) {
    analogWrite(9, i);
    delay(15);
  }
}