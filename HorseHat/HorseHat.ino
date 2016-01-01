const int SERVO_PIN = 2; 
 
void setup() {
  pinMode(s, OUTPUT);
}
 
const int PULSE_PERIOD_us = 20000;
void loop() {
  int high_time_us = 1550;
  digitalWrite(SERVO_PIN, 1);
  delayMicroseconds(high_time_us);

  int low_time_us = PULSE_PERIOD_us-high_time_us;
  digitalWrite(SERVO_PIN, 0);
  delayMicroseconds(low_time_us); 
}
