#include <Arduino.h>

#include <SoftwareSerial.h>

int pwmValue = 0;
int pwmDirection = 5;

// Tworzymy "sztuczny" port szeregowy na pinach 10 (RX) i 11 (TX)
SoftwareSerial mojUART(10, 11); 

void setup() {
  pinMode(9, OUTPUT); 
  pinMode(8, OUTPUT); 
  
  // Uruchamiamy nasz nowy port z popularną prędkością 9600
  mojUART.begin(9600);
}

void loop() {
  // 1. PWM i Cyfra (Zostawiamy jak było)
  analogWrite(9, pwmValue);
  pwmValue += pwmDirection;
  if (pwmValue <= 0 || pwmValue >= 255) pwmDirection = -pwmDirection;

  if (millis() % 2000 < 1000) digitalWrite(8, HIGH);
  else digitalWrite(8, LOW);

  // 2. NOWOŚĆ: Wysyłanie tekstu przez UART (co ok. 1 sekundę)
  if (millis() % 1000 < 20) {
    mojUART.println("Tajne Haslo: ESP32 Rzadzi!");
  }

  delay(20); 
}