#include <bits/stdc++.h>

class Effect {
    public:
    static void init();
    static void apply(std::string effect_name);

    private:
    static void static_color(u_int32_t hex);
    static void fire();
    static void render();
};