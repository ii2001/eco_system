#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "Environment.h"
#include "Animal.h"

class Wolf : public Animal {
private:
    static const int max_hunger = 100000;
    static const int speed = 150.0;

    float detect_range = 1200.0;
    float walk_mult = 0.8;
    float run_mult = 2.0;

    bool is_walk = false;
    int walk_frame = 0;

    int temp = 0;

    Animal* target_rabbit;

    static const char wolf_left_stand[50][62];
    static const char wolf_left_move1[50][70];
    static const char wolf_left_move2[50][70];
    static const char wolf_right_stand[50][62];
    static const char wolf_right_move1[50][70];
    static const char wolf_right_move2[50][70];
    static const char wolf_left_sleep[50][62];
    static const char wolf_right_sleep[50][62];
    static const char wolf_front1[70][30];
    static const char wolf_front2[70][30];
    static const char wolf_back1[70][30];
    static const char wolf_back2[70][30];
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