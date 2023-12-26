#ifndef WIFI_HANDLER
#define WIFI_HANDLER
#include <WiFi.h>

class WiFiHandler{
private:
    const char* ssid = "AndroidAP_2200";
    const char* password = "p6nret75nk8czfw";
    // const char* username = "Embedded-Lab Games";

public:
    WiFiHandler();
    String get_mac_address();
    void connect(wifi_mode_t mode);
};

#endif // WIFI_HANDLER