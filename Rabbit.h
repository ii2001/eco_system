#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "Environment.h"
#include "Animal.h"

class Rabbit : public Animal
{
private:
    static const int max_hunger = 10000;
    static const int max_thirsty = 10000;
    static const int speed = 100.0;

    float detect_range = 300.0;
    float walk_mult = 0.5;
    float run_mult = 2.3;

    bool jump = false;
    int jump_frame = 0;

    int temp = 0;

    Animal* target_wolf;
    grass* target_grass;

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

    bool find_grass();
    //bool find_pond();
    bool find_wolf();

    bool eatting(int dt);
    void draw();
    void update(int dt);
    
    void check_dir();

    int get_type();
    float get_speed();
};
