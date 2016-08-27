#include <dht11.h>
#include <ESP8266WiFi.h>
/*#include <DHT11.h> */

const char* ssid     = "GBroadband_ahamed"; // Your ssid
const char* password = "connect07022015"; // Your Password
float temp, humi;
String tempS;
String humiS;
char t_buffer[10];
char h_buffer[10];
int pin = D5;

//WiFiServer server(80);
WiFiClient client;
dht11 dht;

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "SOW0EIS0H3TK4BAS";
const int updateThingSpeakInterval = 10 * 1000; // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)
// Variable Setup
long lastConnectionTime = 0;
boolean lastConnected = false;
int failedCounter = 0;
double Fahrenheit(double celsius) {
  return ((double)(9 / 5) * celsius) + 32;
}

double Kelvin(double celsius) {
  return celsius + 273.15;
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();

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
}
void updateThingSpeak(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))
  {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    lastConnectionTime = millis();
    if (client.connected())
    {
      Serial.println("Connecting to ThingSpeak...");
      Serial.println();
      failedCounter = 0;
    }
    else
    {
      failedCounter++;
      Serial.println("Connection to ThingSpeak failed (" + String(failedCounter, DEC) + ")");
      Serial.println();
    }
  }
  else
  {
    failedCounter++;
    Serial.println("Connection to ThingSpeak Failed (" + String(failedCounter, DEC) + ")");
    Serial.println();
    lastConnectionTime = millis();
  }
}
void loop() {
  int err;

  if ((err = dht.read(pin)) == 0)
  {
    temp = dht.temperature;

    tempS = dtostrf(temp, 0, 5, t_buffer);

    humi = dht.humidity;
    humiS = dtostrf(humi, 0, 5, h_buffer);
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();
  }



  //if(!client.connected() && ((millis() - lastConnectionTime) > updateThingSpeakInterval))
  if (((millis() - lastConnectionTime) > updateThingSpeakInterval))
  {
    updateThingSpeak("field1=" + tempS + "&field2=" + humiS); /* &field3="+pres+"&field4="+temp2); */
  }
  delay(3000); //delay for reread
}


