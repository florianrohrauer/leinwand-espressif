#include "Effect.h"

void Effect::static_color(u_int32_t hex) {
    CRGB color = CRGB(hex);
    
    for(int led = 0; led < LED_COUNT; led++) {
        leds[led] = color;
    }

    Effect::render();
}