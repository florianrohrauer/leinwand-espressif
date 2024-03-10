#include <bits/stdc++.h>
#include <FastLED.h>

class Effect {
    #define LED_PIN     4
    #define LED_TYPE    WS2812B
    #define COLOR_ORDER GRB
    #define BRIGHTNESS  255
    #define LED_COUNT   113
    #define FPS         60

    public:
    static void init();
    static void apply(std::string effect_name);

    private:
    static CRGB leds[LED_COUNT];
    static void static_color(u_int32_t hex);
    static void fire();
    static void pacifica();
    static void render();
};