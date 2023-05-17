#include <WiFi.h>
#include <ThingSpeak.h>

#define ldr 34

WiFiClient client;

long myChannelNumber = Your Channel ID;
const char myWriteAPIKey[] = "Your API Key";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("ssid", "password");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("ESP32 is connected!");
  Serial.println(WiFi.localIP());
  pinMode(ldr, INPUT);
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  int li = analogRead(ldr);
  Serial.println("Light Intensity: " + (String) li);
  ThingSpeak.writeField(myChannelNumber, 1, li, myWriteAPIKey);
  delay(2000);
}
