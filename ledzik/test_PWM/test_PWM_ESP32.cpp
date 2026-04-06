#include <Arduino.h>

const int PWM_IN_PIN = 15; // Pin, do którego podłączyliśmy sygnał przez konwerter

void setup() {
  Serial.begin(115200);
  pinMode(PWM_IN_PIN, INPUT);
}

void loop() {
  // pulseIn() zwraca czas trwania stanu w mikrosekundach
  unsigned long timeHigh = pulseIn(PWM_IN_PIN, HIGH);
  unsigned long timeLow = pulseIn(PWM_IN_PIN, LOW);

  // Zabezpieczenie przed dzieleniem przez zero w przypadku braku sygnału
  if (timeHigh > 0 || timeLow > 0) {
    unsigned long period = timeHigh + timeLow; // Całkowity czas jednego cyklu
    
    // Obliczamy wypełnienie PWM w procentach (0% - 100%)
    float dutyCycle = ((float)timeHigh / period) * 100.0;

    // Specjalny format tekstu, który rysuje wykresy (dodajemy znak '>')
    Serial.print(">Wypelnienie_PWM:");
    Serial.println(dutyCycle);
  } else {
    // Jeśli nie ma sygnału, rysuj zero
    Serial.println(">Wypelnienie_PWM:0.0");
  }

  // Odczekaj chwilę, żeby nie zapchać portu szeregowego
  delay(50); 
}