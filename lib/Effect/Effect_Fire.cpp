#include "Effect.h"

void Effect::fire() {
    #define COOLING  55
    #define SPARKING 120

    static uint8_t heat[LED_COUNT];

    for (int i = 0; i < LED_COUNT; i++) {
        heat[i] = qsub8(heat[i],  random8(0, ((COOLING * 10) / LED_COUNT) + 2));
    }
  
    for (int k = LED_COUNT - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    if (random8() < SPARKING) {
        int y = random8(7);
        heat[y] = qadd8(heat[y], random8(160,255) );
    }

    for (int j = 0; j < LED_COUNT; j++) {
        CRGB color = HeatColor(heat[j]);
        int pixelnumber;
        pixelnumber = j;
        leds[pixelnumber] = color;
    }

    Effect::render();
}