#include "Effect.h"
#include <FastLED.h>
#include <string>
#include "Command.h"

#define LED_PIN     4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  255
#define LED_COUNT   113
#define FPS         60

CRGB leds[LED_COUNT];

void Effect::init() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);
}

void Effect::apply(std::string effect_name) {
    std::vector<std::string> token = split(effect_name, ':');
    std::string command = token.at(0);
    
    if(command == "color") {
        uint32_t color = std::stoi(token.at(1));
        Effect::static_color(color);
    }

    if(command == "fire") {
        Effect::fire();
    }
}

// effect string: color:#FF52CB
void Effect::static_color(u_int32_t hex) {
    CRGB color = CRGB(hex);
    
    for(int led = 0; led < LED_COUNT; led++) {
        leds[led] = color;
    }

    Effect::render();
}

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

void Effect::render() {
    FastLED.show();
    FastLED.delay(1000 / FPS);
}