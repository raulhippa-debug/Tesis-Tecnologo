
#include "max6675.h"

int S0 = 5;
int CS = 6;
int sck = 7;
int ch1Pin = 2;
int triggerType = HIGH;
int ssrON, ssrOFF;
float temp_eval = 85.0;

MAX6675 module(sck, CS, S0);

void setup() {
    Serial.begin(115200);
    pinMode(ch1Pin, OUTPUT);
    if (triggerType == HIGH) {
        ssrON = HIGH;
        ssrOFF = LOW;
    } else {
        ssrON = LOW;
        ssrOFF = HIGH;
    }
    digitalWrite(ch1Pin, ssrOFF);
}

void loop() {
    float Temperatura = module.readCelsius();
    Serial.print("Temperatura: ");
    Serial.print(Temperatura);
    Serial.println(F("C"));
    delay(1000);
    while (Temperatura >= temp_eval) {
        digitalWrite(ch1Pin, ssrOFF);
    }
    if (Temperatura < temp_eval) {
        digitalWrite(ch1Pin, ssrON);
    }
    delay(5000);
}
