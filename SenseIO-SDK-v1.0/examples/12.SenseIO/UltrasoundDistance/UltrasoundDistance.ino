#define trigPin D6
#define echoPin D7
#define led 11
#define led2 10
void setup()
{
 Serial.begin (115200);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
// pinMode(led, OUTPUT);
 //pinMode(led2, OUTPUT);
}
void loop() 
{
 long duration, distance;
 digitalWrite(trigPin, LOW);  
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration/2) / 29.1;
 if (distance < 4) 
{  // This is where the LED On/Off happens
   //digitalWrite(led,HIGH); 
 //digitalWrite(led2,LOW);
}
 else {
   //digitalWrite(led,LOW);
   //digitalWrite(led2,HIGH);
 }
 if (distance >= 200 || distance <= 0){
   Serial.println("Out of range");
 }
 else {
   Serial.print(distance);
   Serial.println(" cm");
 }
 delay(500);
}
