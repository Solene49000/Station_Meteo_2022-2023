int LED_R = 33;
int LED_G = 25;
void setup() {
pinMode (LED_R, OUTPUT);
pinMode (LED_G, OUTPUT);
}
void loop() {
digitalWrite(LED_G, LOW);
digitalWrite(LED_R, HIGH);
delay(1000);
digitalWrite(LED_R, LOW);
digitalWrite(LED_G, HIGH);
delay(1000);
}
