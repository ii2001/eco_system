#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "World.h"
#include "Environment.h"
#include "Animal.h"
#include <cmath>

class Wolf : public Animal {
private:
    Rabbit* target_rabbit;
public:
    static const int max_hunger = 10000;

    Wolf(float x, float y);
    void move(int dt);
    bool find_rabbit();
    void hunt(int dt);
    void draw();
    void update(int dt);
    int get_type();
};