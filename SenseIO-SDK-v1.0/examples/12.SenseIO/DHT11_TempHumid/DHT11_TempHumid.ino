#include <dht11.h>
#include <ESP8266WiFi.h>
float temp, humi;
String tempS;
String humiS;
char t_buffer[10];
char h_buffer[10];

int pin = D5;
dht11 dht;

double Kelvin(double celsius) {
  return celsius + 273.15;
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
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
  delay(3000);

}


