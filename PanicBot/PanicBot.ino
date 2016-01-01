

#define DEPTH_TRIG_PIN 12
#define DEPTH_ECHO_PIN 13
#define LED_RED_PIN 11
#define LED_GREEN_PIN 10
#define LED_BLUE_PIN 9

void setup() {
  Serial.begin (9600);
  pinMode(DEPTH_TRIG_PIN, OUTPUT);
  pinMode(DEPTH_ECHO_PIN, INPUT);

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
}

#define MAX_DEPTH_CM 400
#define SAFE_DIST_CM 200
#define MAX_BRIGHTNESS 250
#define MIN_BRIGHTNESS 20
int r_val = 0;
int r_dir = 1;
int b_val = MAX_BRIGHTNESS;
int b_dir = 0;
int g_val = MIN_BRIGHTNESS;
int g_dir = 1;
int val_inc = 10;
void loop() {

  // ping depth sensor and measure response
  long duration_us, distance_cm;
  digitalWrite(DEPTH_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(DEPTH_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(DEPTH_TRIG_PIN, LOW);
  duration_us = pulseIn(DEPTH_ECHO_PIN, HIGH, 10000);
  distance_cm = (duration_us/2) / 29.1;


  // set led brightness ("mood") based on object distance
  if (distance_cm >= MAX_DEPTH_CM || distance_cm <= 0){
    Serial.println("Out of range");

    r_val -= val_inc;
    if (r_val <= MIN_BRIGHTNESS)
      r_val = MIN_BRIGHTNESS;
  } 
  else {
    Serial.print(distance_cm);
    Serial.println(" cm");

    r_val += val_inc;

    if (distance_cm < SAFE_DIST_CM) {

      if (r_val >= MAX_BRIGHTNESS)
        r_val = MAX_BRIGHTNESS;

      float dist_ratio = (distance_cm/(float)SAFE_DIST_CM);
      r_val = (1 - dist_ratio) * r_val;
      g_val = dist_ratio * g_val;
      b_val = dist_ratio * b_val;
    } 
    else {
      if (r_val >= MIN_BRIGHTNESS)
        r_val = MIN_BRIGHTNESS; 
    }
  }

  analogWrite(LED_RED_PIN, r_val);

  // fade green leds
  if (g_val >= MAX_BRIGHTNESS)
    g_dir = 0;
  if (g_val <= MIN_BRIGHTNESS)
    g_dir = 1;
  g_dir == 1 ? g_val += val_inc : g_val -= val_inc;
  analogWrite(LED_GREEN_PIN, g_val);

  // fade blue leds
  if (b_val >= MAX_BRIGHTNESS)
    b_dir = 0;
  if (b_val <= MIN_BRIGHTNESS)
    b_dir = 1;
  b_dir == 1 ? b_val += val_inc : b_val -= val_inc;
  analogWrite(LED_BLUE_PIN, b_val);

  delay(50);
}









