

#include <ESP8266WiFi.h>
#define PIN D0
#define PIN_LED D4
int state = LOW;             // by default, no motion detected
String motionS;
char m_buffer[10];

//WIFI Setup
const char* ssid     = "GBroadband_ahamed"; // Your ssid
const char* password = "connect07022015"; // Your Password
WiFiClient client;

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "04JWGEASOL672R63";
const int updateThingSpeakInterval = 10 * 1000; // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)
void updateThingSpeak(String tsData);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(PIN, INPUT_PULLUP);
pinMode(PIN_LED, OUTPUT);
// Connect to WiFi network
WiFi.mode(WIFI_STA);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
///server.begin();
Serial.println("Server started");

// Print the IP address
Serial.println(WiFi.localIP());
 pinMode(D4, OUTPUT); 


}

void loop() {
  // put your main code here, to run repeatedly:
//readPin = digitalRead(PIN);
//Serial.print("Reading Sensor Input\r\n");
int val = digitalRead(PIN);
  if (val == HIGH) 
  {
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
      digitalWrite(D4, HIGH);
      //motionS=dtostrf(state,0,5,m_buffer);
      //updateThingSpeak("field1=1");/* &field3="+pres+"&field4="+temp2); */
    }
  }
  else
  {
     if (state == HIGH)
     {
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
        digitalWrite(D4, LOW);
        //motionS=dtostrf(state,0,5,m_buffer);
        //updateThingSpeak("field1=0");/* &field3="+pres+"&field4="+temp2); */
    }
  }
 
 //delay(1000);

}
void updateThingSpeak(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))
  {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);

    if (client.connected())
    {
      Serial.println("Connecting to ThingSpeak...");
      Serial.println();
    }
    else
    {
     
      Serial.println("Connection to ThingSpeak failed...\r\n");
      Serial.println();
    }
    
  }

}

