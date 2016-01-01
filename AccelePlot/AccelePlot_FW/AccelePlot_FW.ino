void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

int x, y, z = 0;
void loop() {
  // send the value of analog input 0:
  x = analogRead(A0);
  y = analogRead(A1);
  z = analogRead(A2);
  
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.print(z);
  Serial.println(' ');
  
  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(5);
}

