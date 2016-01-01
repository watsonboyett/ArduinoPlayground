#include <Adafruit_NeoPixel.h>

#define HEARTBEAT_PIN (13)
#define NEOPIXEL_PIN (6)
#define NUM_PIXELS (60)    // 240

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(HEARTBEAT_PIN, OUTPUT);
  pixels.begin();
}

int loop_count = 0;
bool heartbeat = false;
void loop()
{
  heartbeat = !heartbeat;
  digitalWrite(HEARTBEAT_PIN, heartbeat);
  snake();
}

int delayval = 50;
const float DIM = 0.6;
const float FADE_RATE = 0.6;
const int MIN_DC = 10;
const int MAX_DC = 250;


int clr_r = MIN_DC;
int step_r = 29;
int clr_g = MIN_DC;
int step_g = 19;
int clr_b = MIN_DC;
int step_b = 13;
void snake()
{
  int fence_count = 3;
  int fence_skip = NUM_PIXELS / fence_count;

  clr_r = (clr_r + step_r);
  if (clr_r >= MAX_DC || clr_r <= MIN_DC)
  {
    clr_r = constrain(clr_r, MIN_DC, MAX_DC);
    step_r = -step_r;
  }

  clr_g = (clr_g + step_g);
  if (clr_g >= MAX_DC || clr_g <= MIN_DC)
  {
    clr_g = constrain(clr_g, MIN_DC, MAX_DC);
    step_g = -step_g;
  }

  clr_b = (clr_b + step_b);
  if (clr_b >= MAX_DC || clr_b <= MIN_DC)
  {
    clr_b = constrain(clr_b, MIN_DC, MAX_DC);
    step_b = -step_b;
  }
  clr_b = (clr_b + step_b);

  for (int i = 0; i < fence_skip; i++)
  {

    for (int j = 0; j < fence_count + 1; j++)
    {
      float fade_cur = DIM;
      int px_key = j * fence_skip + i;

      for (int k = 0; k < fence_skip; k++)
      {
        int px_cur = px_key - k;
        if (px_cur < 0)
        {
          px_cur = NUM_PIXELS - k;
        }

        int r, g, b;
        r = clr_r * fade_cur;
        g = clr_g * fade_cur;
        b = clr_b * fade_cur;

        pixels.setPixelColor(px_cur, pixels.Color(r, g, b));

        fade_cur = fade_cur * FADE_RATE;
      }
    }

    pixels.show();
    delay(delayval);
  }
}

