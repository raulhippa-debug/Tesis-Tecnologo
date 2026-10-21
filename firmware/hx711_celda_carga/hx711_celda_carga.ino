// Tesis Tecnólogo - Anexo 6.9.3, páginas 67-68.
// Transcripción del programa del documento con normalización tipográfica.
// No validado en hardware en esta entrega.

#include <HX711_ADC.h>
#include <EEPROM.h>

const int HX711_dout = 5;
const int HX711_sck = 6;

HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;

void setup() {
    Serial.begin(57600);
    LoadCell.begin();
    float calibrationValue = 696.0;
    EEPROM.get(calVal_eepromAdress, calibrationValue);
    unsigned long stabilizingtime = 2000;
    boolean _tare = true;
    LoadCell.start(stabilizingtime, _tare);
    if (LoadCell.getTareTimeoutFlag()) {
        Serial.println("TIMEOUT: revisar conexiones");
        while (1);
    } else {
        LoadCell.setCalFactor(calibrationValue);
        Serial.println("Inicializacion completa");
    }
}

void loop() {
    static boolean newDataReady = 0;
    if (LoadCell.update()) newDataReady = true;
    if (newDataReady) {
        float i = LoadCell.getData();
        Serial.print("Peso detectado: ");
        Serial.println(i);
        newDataReady = 0;
    }
    if (Serial.available() > 0) {
        char inByte = Serial.read();
        if (inByte == 't') LoadCell.tareNoDelay();
    }
    if (LoadCell.getTareStatus() == true) {
        Serial.println("Tara completada");
    }
}
