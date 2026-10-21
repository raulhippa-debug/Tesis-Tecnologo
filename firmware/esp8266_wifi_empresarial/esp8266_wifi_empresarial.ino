
#include <ESP8266WiFi.h>
#include <user_interface.h>
#include <wpa2_enterprise.h>
#include <c_types.h>

char ssid[] = "SSID";
char username[] = "usuario";
char identity[] = "identidad";
char password[] = "contrasena";
uint8_t target_esp_mac[6] = {0x24, 0x0a, 0xc4, 0x9a, 0x58, 0x28};

void setup() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200); delay(1000);
    Serial.setDebugOutput(true);

    wifi_set_opmode(STATION_MODE);
    struct station_config wifi_config;
    memset(&wifi_config, 0, sizeof(wifi_config));
    strcpy((char*)wifi_config.ssid, ssid);
    strcpy((char*)wifi_config.password, password);
    wifi_station_set_config(&wifi_config);
    wifi_set_macaddr(STATION_IF, target_esp_mac);

    wifi_station_set_wpa2_enterprise_auth(1);
    wifi_station_clear_cert_key();
    wifi_station_clear_enterprise_ca_cert();
    wifi_station_clear_enterprise_identity();
    wifi_station_clear_enterprise_username();
    wifi_station_clear_enterprise_password();

    wifi_station_set_enterprise_identity((uint8*)identity, strlen(identity));
    wifi_station_set_enterprise_username((uint8*)username, strlen(username));
    wifi_station_set_enterprise_password((uint8*)password, strlen((char*)password));

    wifi_station_connect();
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000); Serial.print(".");
    }
    Serial.println("WiFi conectado");
    Serial.println(WiFi.localIP());
}

void loop() { }
