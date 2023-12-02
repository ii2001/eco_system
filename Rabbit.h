#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "World.h"
#include "Environment.h"
#include "Animal.h"

class Rabbit : public Animal {
private:
    static const int speed = 100.0;

    int temp = 0;

    bool jump = false;
    int jump_frame = 0;

    static const char rabbit_left[19][16];
    static const char rabbit_left_jump[19][16];
    static const char rabbit_right[19][16];
    static const char rabbit_right_jump[19][16];
    static const char rabbit_back[19][16];
    static const char rabbit_back_jump[19][16];
    static const char rabbit_front[19][16];
    static const char rabbit_front_jump[19][16];
public:
    Rabbit(float x, float y);

    void eatGrass();

    void draw();
    void update(int dt);
    
    void check_dir();
    int get_type();
    float get_speed();
};
