/*
 * ESP8266 GPIO
D0   = 16;
D1   = 5;
D2   = 4;
D3   = 0;
D4   = 2;
D5   = 14;
D6   = 12;
D7   = 13;
D8   = 15;
D9   = 3;
D10  = 1;
 * */

#ifdef ESP8266
   #include <ESP8266WiFi.h>
#else
   #include <WiFi.h>
#endif

const char* WIFI_SSID = "SSID";
const char* WIFI_PASS = "PASSWD";

WiFiServer server(80);

void setup(){ 
    delay(2000);
    Serial.begin(115200);

    WiFi.mode(WIFI_STA); WiFi.disconnect();
    delay(100);
  
    Serial.println("Connecting..."); WiFi.begin(WIFI_SSID, WIFI_PASS);
  
    while (WiFi.status() != WL_CONNECTED) {
      if (WiFi.status() == WL_CONNECT_FAILED) {
        Serial.println("Failed to connect to WIFI. Please verify credentials. ");
        WiFi.begin(WIFI_SSID, WIFI_PASS);
      }
      delay(1000);
    }

    Serial.println( "\nWiFi connected\nIP address: " ); Serial.print(WiFi.localIP());

   server.begin();
   Serial.println("\n_____\n");
   pinMode(2, OUTPUT);
   digitalWrite(2, HIGH); delay(1000); digitalWrite(2, LOW);
}

void loop() {
  //if (WiFi.status() != WL_CONNECTED) { WiFi.begin(WIFI_SSID, WIFI_PASS); }
    WiFiClient client = server.available();
    
    if (client) {
      if (client.connected()) {
        Serial.println("Connected with client.");
        String request = " " + client.readStringUntil('\r');
        if ( request.indexOf("on") > 0 ) { Serial.println("on"); digitalWrite(2, HIGH); }
        else if ( request.indexOf("off") > 0 ) { Serial.println("off"); digitalWrite(2, LOW); }
        else { Serial.println(request); }
        }
      client.stop();
    }

}
