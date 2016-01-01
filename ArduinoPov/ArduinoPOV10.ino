/*
##########################
# Arduino POV for 10 LEDs #
##########################

Circuit: 10 LEDs connected to pins 2 to 11 (with resistors, usually 560 ohm)

Each character is given a 10x10 grid to represent it's self
For example "H" is
O 0       0 0
O 0       0 0
O O       0 0
O 0       0 0
O 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0       0 0
0 0       0 0
0 0       0 0
0 0       0 0
each of these vertical lines is made from a single number
for the "H" example the numbers are 31,4,4,4,31

512  O 0       0 0
256  O 0       0 0
128  O O       0 0
64   O 0       0 0
32   O 0 0 0 0 0 0
16   0 0 0 0 0 0 0
8    0 0       0 0
4    0 0       0 0
2    0 0       0 0
1    0 0       0 0

t    1 1 0 0 0 1 1 0 0 0
o    0 0 0 0 0 0 0 0 0 0
t    2 2 4 4 4 2 2 0 0 0
     3 3 8 8 8 3 3 0 0 0

1023 is 512+256+128+64+32+16+8+4+2+1 (all LEDs are lit)
48   is 000+000+000+00+32+16+0+0+0+0  (only the middle 2 LEDs are lit)

thus the definition for h is...
int h[] = {1023,1023,48,48,48,1023,1023,0,0,0};

*/


int delayTime = 2; //sub-char delay time
int charBreak = 5; //char delay time


int LED0 = 3;
int LED1 = 4;
int LED2 = 5;
int LED3 = 6;
int LED4 = 7;
int LED5 = 8;
int LED6 = 9;
int LED7 = 10;
int LED8 = 11;
int LED9 = 12;

void setup()
{
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);  
}

//lets define a font, yay

int a[] = {7,31,248,216,792,792,216,248,31,7};
int b[] = {1023,1023,819,819,478,478,0,0,0,0};
int c2[] = {120,510,390,771,771,771,462,204,0,0};
int d[] = {1023,1023,771,771,390,510,120,0,0,0};
int e[] = {1023,1023,819,819,819,771,771,0,0,0};
int f[] = {1023,1023,816,816,816,768,768,0,0,0};
int g[] = {0,252,510,903,771,795,927,414,24,0};
int h[] = {1023,1023,48,48,48,1023,1023,0,0,0};
int i[] = {771,771,1023,1023,771,771,0,0,0,0};
int j[] = {771,771,1023,1023,768,768,0,0,0,0};
int k[] = {1023,1023,120,204,390,771,513,0,0,0};
int l[] = {1023,1023,3,3,3,3,0,0,0,0};
int m[] = {1023,1023,448,224,56,56,224,448,1023,1023};
int n[] = {1023,1023,448,224,56,28,1023,1023,0,0};
int o[] = {120,252,390,771,771,771,390,252,120,0};
int p[] = {1023,1023,816,816,480,480,0,0,0,0};
int q[] = {120,510,390,771,795,414,510,126,6,0};
int r[] = {1023,1023,816,824,510,199,3,0,0,0};
int s[] = {230,502,947,819,926,396,0,0,0,0};
int t[] = {768,768,768,1023,1023,768,768,768,0,0};
int u[] = {1016,1022,6,3,3,3,6,1022,1016,0};
int v[] = {768,960,240,60,15,15,60,240,960,768};
int w[] = {240,254,7,62,112,62,7,254,240,0};
int x[] = {771,903,462,252,120,120,252,462,903,771};
int y[] = {771,903,462,252,120,112,224,448,896,768};
int z[] = {775,783,799,827,883,995,963,899,0,0};

int eos[] = {3,3,0,0,0,0,0,0,0,0};
int excl[] = {448,1019,1019,448,0,0,0,0,0,0};
int ques[] = {192,448,768,795,795,816,480,192,0,0};

void displayLine(int line)
{
  int myline;
  myline = line;
  if (myline>=512)  {digitalWrite(LED0, HIGH); myline-=512;}  else {digitalWrite(LED0, LOW);}
  if (myline>=256)  {digitalWrite(LED1, HIGH); myline-=256;}  else {digitalWrite(LED1, LOW);}
  if (myline>=128)  {digitalWrite(LED2, HIGH); myline-=128;}  else {digitalWrite(LED2, LOW);}
  if (myline>=64)   {digitalWrite(LED3, HIGH); myline-=64;}   else {digitalWrite(LED3, LOW);}
  if (myline>=32)   {digitalWrite(LED4, HIGH); myline-=32;}   else {digitalWrite(LED4, LOW);}    
  if (myline>=16)   {digitalWrite(LED5, HIGH); myline-=16;}   else {digitalWrite(LED5, LOW);}
  if (myline>=8)    {digitalWrite(LED6, HIGH); myline-=8;}    else {digitalWrite(LED6, LOW);}
  if (myline>=4)    {digitalWrite(LED7, HIGH); myline-=4;}    else {digitalWrite(LED7, LOW);}
  if (myline>=2)    {digitalWrite(LED8, HIGH); myline-=2;}    else {digitalWrite(LED8, LOW);}
  if (myline>=1)    {digitalWrite(LED9, HIGH); myline-=1;}    else {digitalWrite(LED9, LOW);}  
}

void displayChar(char c)
{
  if (c == 'a'){for (int i = 0; i <10; i++){displayLine(a[i]);delay(delayTime);}displayLine(0);}
  if (c == 'b'){for (int i = 0; i <10; i++){displayLine(b[i]);delay(delayTime);}displayLine(0);}
  if (c == 'c'){for (int i = 0; i <10; i++){displayLine(c2[i]);delay(delayTime);}displayLine(0);}
  if (c == 'd'){for (int i = 0; i <10; i++){displayLine(d[i]);delay(delayTime);}displayLine(0);}
  if (c == 'e'){for (int i = 0; i <10; i++){displayLine(e[i]);delay(delayTime);}displayLine(0);}
  if (c == 'f'){for (int i = 0; i <10; i++){displayLine(f[i]);delay(delayTime);}displayLine(0);}
  if (c == 'g'){for (int i = 0; i <10; i++){displayLine(g[i]);delay(delayTime);}displayLine(0);}
  if (c == 'h'){for (int i = 0; i <10; i++){displayLine(h[i]);delay(delayTime);}displayLine(0);}  
  if (c == 'i'){for (int it = 0; it <10; it++){displayLine(i[it]);delay(delayTime);}displayLine(0);}
  if (c == 'j'){for (int i = 0; i <10; i++){displayLine(j[i]);delay(delayTime);}displayLine(0);}
  if (c == 'k'){for (int i = 0; i <10; i++){displayLine(k[i]);delay(delayTime);}displayLine(0);}
  if (c == 'l'){for (int i = 0; i <10; i++){displayLine(l[i]);delay(delayTime);}displayLine(0);}
  if (c == 'm'){for (int i = 0; i <10; i++){displayLine(m[i]);delay(delayTime);}displayLine(0);}
  if (c == 'n'){for (int i = 0; i <10; i++){displayLine(n[i]);delay(delayTime);}displayLine(0);}
  if (c == 'o'){for (int i = 0; i <10; i++){displayLine(o[i]);delay(delayTime);}displayLine(0);}
  if (c == 'p'){for (int i = 0; i <10; i++){displayLine(p[i]);delay(delayTime);}displayLine(0);}
  if (c == 'q'){for (int i = 0; i <10; i++){displayLine(q[i]);delay(delayTime);}displayLine(0);}
  if (c == 'r'){for (int i = 0; i <10; i++){displayLine(r[i]);delay(delayTime);}displayLine(0);}
  if (c == 's'){for (int i = 0; i <10; i++){displayLine(s[i]);delay(delayTime);}displayLine(0);}
  if (c == 't'){for (int i = 0; i <10; i++){displayLine(t[i]);delay(delayTime);}displayLine(0);}
  if (c == 'u'){for (int i = 0; i <10; i++){displayLine(u[i]);delay(delayTime);}displayLine(0);}
  if (c == 'v'){for (int i = 0; i <10; i++){displayLine(v[i]);delay(delayTime);}displayLine(0);}
  if (c == 'w'){for (int i = 0; i <10; i++){displayLine(w[i]);delay(delayTime);}displayLine(0);}
  if (c == 'x'){for (int i = 0; i <10; i++){displayLine(x[i]);delay(delayTime);}displayLine(0);}
  if (c == 'y'){for (int i = 0; i <10; i++){displayLine(y[i]);delay(delayTime);}displayLine(0);}
  if (c == 'z'){for (int i = 0; i <10; i++){displayLine(z[i]);delay(delayTime);}displayLine(0);}
  if (c == '!'){for (int i = 0; i <10; i++){displayLine(excl[i]);delay(delayTime);}displayLine(0);}
  if (c == '?'){for (int i = 0; i <10; i++){displayLine(ques[i]);delay(delayTime);}displayLine(0);}
  if (c == '.'){for (int i = 0; i <10; i++){displayLine(eos[i]);delay(delayTime);}displayLine(0);}
  delay(charBreak);
}

void displayString(char* s)
{
  for (int i = 0; i<=strlen(s); i++)
  {
    displayChar(s[i]);
  }
  delay(300);
}

void loop()
{    
  displayString("roving");
}
