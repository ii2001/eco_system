#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "Environment.h"
#include "Animal.h"

class Wolf : public Animal {
private:
    static const int max_hunger = 10000;
    static const int speed = 150.0;

    float detect_range = 1200.0;
    float walk_mult = 0.8;
    float run_mult = 2.0;

    int temp = 0;

    Animal* target_rabbit;

    static const char wolf_left[19][16];
    static const char wolf_left_jump[19][16];
    static const char wolf_right[19][16];
    static const char wolf_right_jump[19][16];
    static const char wolf_back[19][16];
    static const char wolf_back_jump[19][16];
    static const char wolf_front[19][16];
    static const char wolf_front_jump[19][16];
public:
    Wolf(float x, float y);

    bool find_rabbit();
    bool follow(int dt);
    bool hunt(int dt);

    void draw();
    void update(int dt);

    int get_type();
    float get_speed();
};