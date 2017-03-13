#define SYNC_EVERY 15000
#define NUM_FIELDS 8
#define NUM_REF_FIELDS 2

const char* host = "api.thingspeak.com"; // Your domain  
String dude_api_key = "UJOTAVLHVLL4ZMH9";
String dude_ref_api_key = "I2FMGP46WNZAAHXK";
String path = "/update?";  
long sync_counter = 1;

unsigned int last_sync_millis;
int hight_thermometers[NUM_FIELDS] = {4, 14, 9, 7, 15, 5, 2, 1};
int ref_thermometers[NUM_REF_FIELDS] = {8, 3};  // change 3 to actual num


void sync_setup() {
  last_sync_millis = 0;
}

void sync_loop() {
  unsigned int now = millis();
  if (now > last_sync_millis && now < last_sync_millis + SYNC_EVERY)
    return;
  red_off();
  green_off();
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    red_on();
    return;
  }

  // Free accounts on ThingSpeak accept a single message per 15 seconds.
  // Also, in each message it accepts up to 8 fields.
  // Thus, we sync every 15 seconds but we alternate between syncing the 8 main thermometers
  // and the two ref thermometers. Ref thermomemters are synched only once per four syncs,
  // specifically when sync_counter%4 = 0
  if (sync_counter % 4 == 0) {
    reportData(client, dude_ref_api_key, ref_thermometers, NUM_REF_FIELDS);    
  } else {
    reportData(client, dude_api_key, hight_thermometers, NUM_FIELDS);
  }
  sync_counter++;
  
  last_sync_millis = now;
  green_on();
  //blue_on();
  //green_on();
}

void reportData(WiFiClient & client, String api_key, const int* fields, int field_count) {
  String fields_str;
  for (int i=0; i<field_count; i++) {
    char temp_str[6];
    dtostrf(temperature[fields[i] - 1], 2, 2, temp_str);
    fields_str += String("&field") + (i+1) + "=" + temp_str;
  }

  String request = String("GET ") + path + "key=" + api_key + fields_str + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n";
  Serial.println(request);
  client.print(request);

}

