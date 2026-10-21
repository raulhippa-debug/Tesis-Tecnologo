// Tesis Tecnólogo - Anexo 6.11, páginas 70-71.
// Transcripción del programa del documento con normalización tipográfica.
// AVISO: el POST HTTP procede del PDF y no se ha validado. Revisar el
// formato de cuerpo/cabeceras con la API vigente de ThingSpeak.
// Sustituir placeholders solo en una copia local que NO se suba a GitHub.

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define PRESION_NIVEL_MAR_HPA (1013.25)

Adafruit_BME280 bme;

String apiKey = "TU_API_KEY";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

const char* ssid = "Nombre_Red";
const char* password = "Contrasena";
const char* server = "api.thingspeak.com";

WiFiClient cliente;

void setup() {
    Serial.begin(9600);
    if (!bme.begin(0x76)) {
        Serial.println("BME280 no detectado");
        while (1);
    }
    Serial.print("Conectando a: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi conectado");
    Serial.println(WiFi.localIP());
    timeClient.begin();
}

void loop() {
    float Temperatura = bme.readTemperature();
    float Presion = bme.readPressure() / 100.0F;
    float Humedad = bme.readHumidity();

    timeClient.update();
    String formattedDate = timeClient.getFormattedDate();

    if (cliente.connect(server, 80)) {
        String postStr = apiKey;
        postStr += "&field1=";
        postStr += String(Temperatura);
        postStr += "&field2=";
        postStr += String(Humedad);
        postStr += "&field3=";
        postStr += String(Presion);
        postStr += "\r\n\r\n";

        cliente.print("POST /update HTTP/1.1\n");
        cliente.print("Host: api.thingspeak.com\n");
        cliente.print("Connection: close\n");
        cliente.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        cliente.print("Content-Type: application/x-www-form-urlencoded\n");
        cliente.print("Content-Length: ");
        cliente.print(postStr.length());
        cliente.print("\n\n");
        cliente.print(postStr);

        Serial.print("Temperatura: ");
        Serial.print(Temperatura);
        Serial.print(" C, Humedad: ");
        Serial.print(Humedad);
        Serial.print(" %, Presion: ");
        Serial.print(Presion);
        Serial.println(" hPa ||| Datos enviados a ThingSpeak");
    }
    cliente.stop();
    delay(20000);
}
