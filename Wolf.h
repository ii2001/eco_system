#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "World.h"
#include "Environment.h"
#include "Animal.h"

class Wolf : public Animal {
private:
    static const int max_hunger = 10000;
    static const int speed = 150.0;

    float detect_range = 600.0;
    float walk_mult = 0.5;
    float run_mult = 2.0;

    int temp = 0;

    Animal* target_rabbit;
public:
    Wolf(float x, float y);

    bool find_rabbit();
    void hunt(int dt);

    void draw();
    void update(int dt);

    int get_type();
    float get_speed();
};