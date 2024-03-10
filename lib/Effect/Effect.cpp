#include "Effect.h"
#include <FastLED.h>
#include <string>
#include "Command.h"

CRGB Effect::leds[LED_COUNT];

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

    if(command == "pacifica") {
        Effect::pacifica();
    }
}

void Effect::render() {
    FastLED.show();
    FastLED.delay(1000 / FPS);
}