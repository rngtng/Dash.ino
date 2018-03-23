#include <Dash.h>

void setup()
{
  Dash.begin()
  Dash.all_led(YELLOW);
}

void loop()
{
   for (byte color = 0; color < 8; color++) {
    for (byte led = 0; led < 4; led++) {
      Dash.raw_led(led, color);
      delay(150);
    }
  }
}
