const int SERVO_PIN = 2; 
 
void setup() {
  pinMode(SERVO_PIN, OUTPUT);
}
 
const int PULSE_PERIOD_us = 30000;
void loop() {
  int high_time_us = 1400;
  digitalWrite(SERVO_PIN, 1);
  delayMicroseconds(high_time_us);

  int low_time_us = PULSE_PERIOD_us-high_time_us;
  digitalWrite(SERVO_PIN, 0);
  delayMicroseconds(low_time_us); 
}
