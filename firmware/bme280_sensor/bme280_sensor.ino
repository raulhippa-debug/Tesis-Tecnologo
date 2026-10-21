

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define PRESION_NIVEL_MAR_HPA (1013.25)

Adafruit_BME280 bme;

void setup() {
    Serial.begin(9600);
    if (!bme.begin(0x76)) {
        Serial.println("No se encontro un sensor BME280 valido");
        while (1);
    }
}

void loop() {
    Serial.print("Temperatura = ");
    Serial.print(bme.readTemperature());
    Serial.println("*C");
    Serial.print("Presion = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println("hPa");
    Serial.print("Altitud Aprox. = ");
    Serial.print(bme.readAltitude(PRESION_NIVEL_MAR_HPA));
    Serial.println("m");
    Serial.print("Humedad = ");
    Serial.print(bme.readHumidity());
    Serial.println("%");
    Serial.println();
    delay(1000);
}
