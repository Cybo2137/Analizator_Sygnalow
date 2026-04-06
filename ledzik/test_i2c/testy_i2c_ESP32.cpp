#include <Arduino.h>
#include <Wire.h>

// Flagi i bufory do bezpiecznego odbioru danych z przerwan
volatile bool noweDaneI2C = false;
String odebranaWiadomoscI2C = "";

// Funkcja, ktora wywoluje sie SAMA, gdy nadejda dane po I2C
void funkcjaOdbioruI2C(int iloscBajtow) {
  odebranaWiadomoscI2C = "";
  while (Wire.available()) {
    char znak = Wire.read();
    odebranaWiadomoscI2C += znak;
  }
  noweDaneI2C = true;
}

void setup() {
  Serial.begin(115200);
  
  // Uruchamiamy I2C jako urzadzenie Slave (Podwladny) z adresem nr 8
  Wire.begin(8);
  
  // Rejestrujemy funkcje "podsluchujaca"
  Wire.onReceive(funkcjaOdbioruI2C);
  
  Serial.println("Analizator I2C uruchomiony na adresie 0x08...");
}

void loop() {
  // Sprawdzamy, czy w miedzyczasie przyszly jakies dane
  if (noweDaneI2C) {
    noweDaneI2C = false; // Zerujemy flage
    
    // Wypisujemy bezposrednio do Terminala tekstowego (nie na wykres Teleplota)
    Serial.print("--- PRZECHWYCONO I2C: ");
    Serial.println(odebranaWiadomoscI2C);
    
    // Rysujemy "igle" w Teleplocie, zeby widziec to tez na wykresach
    Serial.println(">Aktywnosc_I2C:100");
  } else {
    // Opada do zera, gdy nic sie nie dzieje
    Serial.println(">Aktywnosc_I2C:0");
  }

  delay(50);
}