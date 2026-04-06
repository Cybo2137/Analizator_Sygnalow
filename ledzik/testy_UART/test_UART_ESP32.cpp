#include <Arduino.h>

const int PIN_PWM = 18;      
const int PIN_DIGITAL = 19;  
// Pin RX dla drugiego UARTu w ESP32 to zazwyczaj 16. 
// TX to 17, ale my tylko słuchamy, więc go nie używamy.

void setup() {
  Serial.begin(115200); // Komunikacja z Teleplotem
  
  // Uruchamiamy nasłuch UART z prędkością 9600 (tak samo jak w Arduino!)
  Serial2.begin(9600, SERIAL_8N1, 16, 17); 

  pinMode(PIN_PWM, INPUT);
  pinMode(PIN_DIGITAL, INPUT);
}

void loop() {
  // --- ODCZYT CYFRY ---
  int stanCyfrowy = digitalRead(PIN_DIGITAL);
  Serial.print(">Cyfra_Stan:");
  Serial.println(stanCyfrowy);

  // --- ODCZYT PWM ---
  unsigned long timeHigh = pulseIn(PIN_PWM, HIGH, 20000);
  unsigned long timeLow = pulseIn(PIN_PWM, LOW, 20000);
  if (timeHigh > 0 && timeLow > 0) {
    float dutyCycle = ((float)timeHigh / (timeHigh + timeLow)) * 100.0;
    Serial.print(">PWM_Wypelnienie:");
    Serial.println(dutyCycle);
  } else {
    Serial.print(">PWM_Wypelnienie:");
    Serial.println(0.0);
  }

  // --- NOWOŚĆ: ODCZYT UART ---
  // Jeśli na sprzętowym porcie Serial2 pojawiły się jakieś znaki...
  if (Serial2.available() > 0) {
    // Odczytujemy całą linijkę tekstu aż do znaku końca
    String odebranyTekst = Serial2.readStringUntil('\n');
    
    // Teleplot służy do wykresów, ale potrafi też drukować zwykły tekst w konsoli!
    // Wysyłamy go normalnie, bez znaczka '>'
    Serial.print("--- PRZECHWYCONO UART: ");
    Serial.println(odebranyTekst);
    
    // Opcjonalnie: Zróbmy mały skok na wykresie, żeby wizualnie wiedzieć, że przyszła paczka danych
    Serial.print(">Aktywnosc_UART:");
    Serial.println(100); 
  } else {
    // Opada do zera, gdy jest cisza na łączu
    Serial.print(">Aktywnosc_UART:");
    Serial.println(0);
  }

  delay(50);
}