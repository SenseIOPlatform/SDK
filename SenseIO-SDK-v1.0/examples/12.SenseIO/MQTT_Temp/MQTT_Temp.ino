#include <ESP8266WiFi.h>
#include <dht11.h>
#include <PubSubClient.h>
#define wifi_ssid "GBroadband_ahamed"
#define wifi_password "connect07022015"
#define mqtt_server "test.mosquitto.org"
#define mqtt_user "your_username"
#define mqtt_password "your_password"
#define topic1 "temp"
#define topic2 "humidity"

WiFiClient espClient;
PubSubClient client(espClient);

dht11 dht;
#define DHT11_PIN D5

void setup_wifi();
void reconnect();
void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
}
void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("TestMQTT")) { //* See //NOTE below
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
//NOTE: if a user/password is used for MQTT connection use:
//if(client.connect("TestMQTT", mqtt_user, mqtt_password)) {
void pubMQTT(String topic,float topic_val){
    Serial.print("Newest topic " + topic + " value:");
    Serial.println(String(topic_val).c_str());
    client.publish(topic.c_str(), String(topic_val).c_str(), true);
}
//Variables used in loop()
long lastMsg = 0;
float t1 = 75.5;
float t2 = 50.5;
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //2 seconds minimum between Read Sensors and Publish
  long now = millis();
  if (now - lastMsg > 2000) {
      lastMsg = now;
      //Read Sensors (simulate by increasing the values, range:0-90)
      dht.read(DHT11_PIN);
      t1 = dht.temperature;
      t2 = dht.humidity;
//      t1 = t1>90 ? 0 : ++t1;
 //     t2 = t2>90 ? 0 : ++t2;
      //Publish Values to MQTT broker
      pubMQTT(topic1,t1);
      pubMQTT(topic2,t2);
  }
}
