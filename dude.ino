#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define LOOP_DELAY 100

const char* ssid = "Barkan";
const char* password = "037440240";

void setup() {
  led_setup();
  ota_setup();
  measure_setup();
  sync_setup();
}

void loop() {
  led_loop();
  ota_loop();
  measure_loop();
  sync_loop();
  delay(LOOP_DELAY);
}
