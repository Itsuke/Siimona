#include "wi_fi_handler.hpp"

WiFiHandler::WiFiHandler(){
    WiFi.disconnect();
};

String WiFiHandler::get_mac_address(){
    return WiFi.macAddress();
}

void WiFiHandler::connect(wifi_mode_t mode){
    WiFi.mode(mode);
    WiFi.begin(ssid, password);

    Serial.print("\nConnecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1500);
        Serial.print(".");
    }
    Serial.println("");
}
