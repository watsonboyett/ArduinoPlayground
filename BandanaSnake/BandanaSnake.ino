#include <Adafruit_NeoPixel.h>

#define HEARTBEAT_PIN (13)
#define NEOPIXEL_PIN (6)
#define NUM_PIXELS (60)

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


const int NUM_SNAKES = 3;
const int SNAKE_LENGTH = NUM_PIXELS / (NUM_SNAKES);

const float FADE_RATE = 0.6;
const float FADE_CUTOFF = 0.05;
const int FADE_COUNT = ceil(log(FADE_CUTOFF) / log(FADE_RATE));
const int MIN_DC = 50;
const int MAX_DC = 250;
int LOOP_DELAY_ms = 70;

// use circular buffers to display pixel RGB values
int pixels_r[NUM_PIXELS] = {0};
int pixels_g[NUM_PIXELS] = {0};
int pixels_b[NUM_PIXELS] = {0};

int get_buffer_index(int desired_pixel)
{
  int index;
  if (desired_pixel < 0)
  {
    index = NUM_PIXELS + desired_pixel;
  }
  else if (desired_pixel >= NUM_PIXELS)
  {
    index = desired_pixel % NUM_PIXELS;
  }
  else
  {
    index = desired_pixel;
  }
  return index;
}

int buffer_start = 0;
int r, g, b = 0;
float fade_cur = 1;
void snake()
{
  // determine if buffer start has passed the head of a snake
  int buffer_start_prev = (buffer_start - 1);
  bool new_color = (buffer_start > 0) && (buffer_start_prev % SNAKE_LENGTH) == 0;
  bool fade_tail = (buffer_start > 0) && (buffer_start_prev % SNAKE_LENGTH) < FADE_COUNT;
  if (new_color || fade_tail)
  {
    // if we've passed the head, then generate a new color
    if (new_color)
    {
      r = random(10, 100);
      g = random(MIN_DC, MAX_DC);
      b = random(MIN_DC, MAX_DC);
      fade_cur = 1;
    }

    // fade the new color as we continue to pass through the snake
    if (fade_tail)
    {
      pixels_r[buffer_start_prev] = r * fade_cur;
      pixels_g[buffer_start_prev] = g * fade_cur;
      pixels_b[buffer_start_prev] = b * fade_cur;
      fade_cur = fade_cur * FADE_RATE;
    }
  }

  // "render" all pixels to "screen"
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    // use buffer offset (rather than shifting arrays)
    int index = get_buffer_index(buffer_start + i);
    int r = pixels_r[index];
    int g = pixels_g[index];
    int b = pixels_b[index];
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }

  pixels.show();
  delay(LOOP_DELAY_ms);
  buffer_start = (buffer_start + 1) % NUM_PIXELS;
}

