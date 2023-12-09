#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "Environment.h"
#include "Animal.h"

class Rabbit : public Animal
{
private:
    static const int max_hunger = 50000;
    static const int speed = 100.0;

    float mate_detect_range = 500.0;
    float detect_range = 300.0;
    float walk_mult = 0.5;
    float run_mult = 2.3;

    bool jump = false;
    int jump_frame = 0;

    int temp = 0;
    int temp_mate = 0;
    int mate_progress = 0;

    int die_timer;
    bool pond_fail;

    Animal* target_wolf;
    grass* target_grass;
    Rabbit* target_mate;

    static const char rabbit_left[19][16];
    static const char rabbit_left_jump[19][16];
    static const char rabbit_right[19][16];
    static const char rabbit_right_jump[19][16];
    static const char rabbit_back[19][16];
    static const char rabbit_back_jump[19][16];
    static const char rabbit_front[19][16];
    static const char rabbit_front_jump[19][16];
    static const char rabbit_die[19][16];
    static const char rabbit_exclam[9][4];
    static const char rabbit_love[6][7];
public:
    Rabbit(float x, float y);

    bool find_grass();
    bool find_wolf();
    bool find_mate();
    

    bool eatting(int dt);
    bool mate(int dt);
    void draw();
    void update(int dt);

    int get_type();
    float get_speed();
    bool is_deleting();
};
