#include <WiFi.h>

WiFiClient client;          // CLIENT is a variable can me client1, client2
WiFiServer server(80);      // server is a variable and 80 is the port no at which server listens to

#define led 2

void setup() 
{
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
  server.begin();
  pinMode(led, OUTPUT);
}

void loop() 
{
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.    
  if (client)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /ledon HTTP/1.1")
    {
      digitalWrite(led, HIGH);
    }
    if(request == "GET /ledoff HTTP/1.1")
    {
      digitalWrite(led, LOW);
    }
  }
}
