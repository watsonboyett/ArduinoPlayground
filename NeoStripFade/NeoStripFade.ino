#include <Adafruit_NeoPixel.h>
#include <math.h>

#define NEOPIXEL_PIN (6)    // data pin of neopixel strip
#define NUM_PIXELS (240)    // total number of LEDS
#define HEARTBEAT_PIN (13)  // output pin for heartbeat LED

#define SECTION_LEN (10)     // number of LEDs to be grouped as one
#define NUM_SECTIONS (24)   // number of LED groups

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(HEARTBEAT_PIN, OUTPUT);
  digitalWrite(HEARTBEAT_PIN, 0);

  pixels.begin();
}

int loop_count = 0;
bool heartbeat = false;
void loop()
{
  // show heartbeat to indicate that we're running
  heartbeat = !heartbeat;
  //digitalWrite(HEARTBEAT_PIN, heartbeat);
  loop_count++;

  switch (1)
  {
    case 0:
      {
        all_white(60);
        break;
      }
    case 1:
      {
        fade();
        break;
      }
  }
}


// turn off all LEDs
void all_off()
{
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

// set all LEDs to white (at given brightness level)
void all_white(int level)
{
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(level, level, level));
  }
  pixels.show();
}

// stratifiy the pixel changes so that fading looks smoother
void all_white_strat(int level)
{
  for (int k = 0; k < SECTION_LEN; k++)
  {
    for (int j = 0; j < NUM_SECTIONS; j++)
    {
      int pi = (j * SECTION_LEN) + k;
      pixels.setPixelColor(pi, pixels.Color(level, level, level));
    }
    pixels.show();
  }
}

// stratifiy the pixel changes so that fading looks smoother
// account for fractional changes in level based on section
void all_white_strat_frac(float level)
{
  for (int k = 0; k < SECTION_LEN; k++)
  {
    int rem = (level - (int)level) * 10;
    for (int j = 0; j < NUM_SECTIONS; j++)
    {
      int b = level;
      b = k < rem ? b + 1 : b;

      int pi = (j * SECTION_LEN) + k;
      pixels.setPixelColor(pi, pixels.Color(b, b, b));
    }
    pixels.show();
  }
}

const unsigned char cie[256] = {
  0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
  3, 4, 4, 4, 4, 4, 4, 5, 5, 5,
  5, 5, 6, 6, 6, 6, 6, 7, 7, 7,
  7, 8, 8, 8, 8, 9, 9, 9, 10, 10,
  10, 10, 11, 11, 11, 12, 12, 12, 13, 13,
  13, 14, 14, 15, 15, 15, 16, 16, 17, 17,
  17, 18, 18, 19, 19, 20, 20, 21, 21, 22,
  22, 23, 23, 24, 24, 25, 25, 26, 26, 27,
  28, 28, 29, 29, 30, 31, 31, 32, 32, 33,
  34, 34, 35, 36, 37, 37, 38, 39, 39, 40,
  41, 42, 43, 43, 44, 45, 46, 47, 47, 48,
  49, 50, 51, 52, 53, 54, 54, 55, 56, 57,
  58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
  68, 70, 71, 72, 73, 74, 75, 76, 77, 79,
  80, 81, 82, 83, 85, 86, 87, 88, 90, 91,
  92, 94, 95, 96, 98, 99, 100, 102, 103, 105,
  106, 108, 109, 110, 112, 113, 115, 116, 118, 120,
  121, 123, 124, 126, 128, 129, 131, 132, 134, 136,
  138, 139, 141, 143, 145, 146, 148, 150, 152, 154,
  155, 157, 159, 161, 163, 165, 167, 169, 171, 173,
  175, 177, 179, 181, 183, 185, 187, 189, 191, 193,
  196, 198, 200, 202, 204, 207, 209, 211, 214, 216,
  218, 220, 223, 225, 228, 230, 232, 235, 237, 240,
  242, 245, 247, 250, 252, 255,
};

const float cie_f[256] = {
  0.0, 0.1, 0.2, 0.3, 0.4, 0.6, 0.7, 0.8, 0.9, 1.0,
  1.1, 1.2, 1.3, 1.4, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1,
  2.2, 2.3, 2.4, 2.6, 2.7, 2.8, 2.9, 3.1, 3.2, 3.4,
  3.5, 3.6, 3.8, 4.0, 4.1, 4.3, 4.5, 4.6, 4.8, 5.0,
  5.2, 5.4, 5.6, 5.8, 6.0, 6.2, 6.4, 6.7, 6.9, 7.1,
  7.4, 7.6, 7.9, 8.1, 8.4, 8.7, 8.9, 9.2, 9.5, 9.8,
  10.1, 10.4, 10.7, 11.0, 11.3, 11.7, 12.0, 12.3, 12.7, 13.0,
  13.4, 13.8, 14.1, 14.5, 14.9, 15.3, 15.7, 16.1, 16.5, 16.9,
  17.4, 17.8, 18.2, 18.7, 19.2, 19.6, 20.1, 20.6, 21.1, 21.5,
  22.0, 22.6, 23.1, 23.6, 24.1, 24.7, 25.2, 25.8, 26.3, 26.9,
  27.5, 28.1, 28.7, 29.3, 29.9, 30.5, 31.2, 31.8, 32.5, 33.1,
  33.8, 34.5, 35.1, 35.8, 36.5, 37.3, 38.0, 38.7, 39.5, 40.2,
  41.0, 41.7, 42.5, 43.3, 44.1, 44.9, 45.7, 46.6, 47.4, 48.2,
  49.1, 50.0, 50.8, 51.7, 52.6, 53.5, 54.4, 55.4, 56.3, 57.3,
  58.2, 59.2, 60.2, 61.2, 62.2, 63.2, 64.2, 65.3, 66.3, 67.4,
  68.4, 69.5, 70.6, 71.7, 72.8, 74.0, 75.1, 76.2, 77.4, 78.6,
  79.8, 81.0, 82.2, 83.4, 84.6, 85.9, 87.1, 88.4, 89.7, 91.0,
  92.3, 93.6, 94.9, 96.3, 97.6, 99.0, 100.4, 101.8, 103.2, 104.6,
  106.1, 107.5, 109.0, 110.4, 111.9, 113.4, 114.9, 116.5, 118.0, 119.6,
  121.1, 122.7, 124.3, 125.9, 127.5, 129.2, 130.8, 132.5, 134.2, 135.9,
  137.6, 139.3, 141.0, 142.8, 144.5, 146.3, 148.1, 149.9, 151.7, 153.6,
  155.4, 157.3, 159.2, 161.1, 163.0, 164.9, 166.9, 168.8, 170.8, 172.8,
  174.8, 176.8, 178.8, 180.9, 182.9, 185.0, 187.1, 189.2, 191.4, 193.5,
  195.7, 197.8, 200.0, 202.2, 204.5, 206.7, 209.0, 211.2, 213.5, 215.8,
  218.1, 220.5, 222.8, 225.2, 227.6, 230.0, 232.4, 234.9, 237.3, 239.8,
  242.3, 244.8, 247.3, 249.9, 252.4, 255.0,
};

void fade()
{
  static int fade_limit_low = 40;
  static int fade_limit_high = 180;
  static int fade_level = fade_limit_low;
  static int fade_step = 1;
  static bool fade_dir = 0;

  if (fade_dir == 0)
  {
    fade_level += fade_step;

    if (fade_level >= fade_limit_high)
    {
      fade_level = fade_limit_high;
      fade_dir = 1;
    }
  }
  else
  {
    fade_level -= fade_step;

    if (fade_level <= fade_limit_low)
    {
      fade_level = fade_limit_low;
      fade_dir = 0;
      delay(600);
    }
  }

  switch (2)
  {
    case 0:
      {
        // linearly scaled intensity (does not work very well, since we perceive light on a log scale)
        all_white(fade_level);
        delay(100);
        break;
      }
    case 1:
      {
        // log-compensated intensity scaling (suffers from discrete jumps in intensity)
        int level = (cie[fade_level]);
        all_white_strat(level);
        delay(20);
        break;
      }
    case 2:
      {
        // log-compensated intensity scaling (reduces effect of discrete jumps in intensity)
        float level = (cie_f[fade_level]);
        all_white_strat_frac(level);
        //delay(3);
        break;
      }
  }
}

