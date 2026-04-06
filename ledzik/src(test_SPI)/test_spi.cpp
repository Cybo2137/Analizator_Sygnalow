#include <Arduino.h>
#include <driver/spi_slave.h>

#define PIN_MOSI 25
#define PIN_MISO -1 
#define PIN_SCK  26
#define PIN_CS   27

WORD_ALIGNED_ATTR char buforOdbiorczy[10];

void setupSPI() {
  spi_bus_config_t buscfg = {};
  buscfg.mosi_io_num = PIN_MOSI;
  buscfg.miso_io_num = PIN_MISO;
  buscfg.sclk_io_num = PIN_SCK;
  buscfg.quadwp_io_num = -1;
  buscfg.quadhd_io_num = -1;

  spi_slave_interface_config_t slvcfg = {};
  slvcfg.mode = 0; // Wracamy do standardowego trybu 0
  slvcfg.spics_io_num = PIN_CS;
  slvcfg.queue_size = 3;
  slvcfg.flags = 0;

  spi_slave_initialize(VSPI_HOST, &buscfg, &slvcfg, SPI_DMA_DISABLED);
}

void setup() {
  Serial.begin(115200);
  setupSPI();
  Serial.println("Analizator SPI gotowy. Czekam na dane...");
}

void loop() {
  spi_slave_transaction_t t = {};
  memset(&t, 0, sizeof(t));
  memset(buforOdbiorczy, 0, sizeof(buforOdbiorczy));
  
  t.length = 3 * 8; 
  t.rx_buffer = buforOdbiorczy;

  esp_err_t ret = spi_slave_transmit(VSPI_HOST, &t, portMAX_DELAY);

  if (ret == ESP_OK) {
    Serial.print("--- PRZECHWYCONO SPI (SUROWE DANE): ");
    for(int i=0; i<3; i++) {
      Serial.print(buforOdbiorczy[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println(">Aktywnosc_SPI:100");
  } else {
    Serial.println(">Aktywnosc_SPI:0");
  }
  delay(50);
}