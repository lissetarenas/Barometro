#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_SSD1306.h>

#define SDA_PIN 21
#define SCL_PIN 22

#define LORA_SS_PIN 18
#define LORA_RST_PIN 14
#define LORA_DIO0_PIN 26

#define OLED_ADDR 0x3C
#define OLED_SDA SDA_PIN
#define OLED_SCL SCL_PIN

#define SCREEN_WIDTH 128   // Ancho del display OLED
#define SCREEN_HEIGHT 64 

Adafruit_BMP085 bmp;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error inicializando el display OLED.");
    while (true);
  }

  if (!bmp.begin()) {
    Serial.println("No se pudo encontrar el sensor BMP180. Verifique la conexión.");
    while (1);
  }

  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar el módulo LoRa. Verifique la conexión.");
    while (1);
  }

  display.clearDisplay();

  // Configura el tamaño y color de la fuente de texto
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println("Iniciando...");

  display.display();
  delay(5000);
  
}

void loop() {
  //float pressure = bmp.readPressure() / 100.0; // Convertir a hPa
  float altitude = bmp.readAltitude();

  Serial.println(altitude-2000);

  LoRa.beginPacket();
  LoRa.print(altitude-2000);
  LoRa.endPacket();
  
  display.clearDisplay();

  display.setCursor(10,10);
  display.println(altitude-2000);
  display.display();
  
  delay(1000);
}



//100 MILISEGUNDOS 