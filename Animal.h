#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "Environment.h"


class Animal : public Entity {
protected:
    int direction = 0;

    Vector2f target;

    static const int max_thirst = 100000;

    int hunger;
    int thirst;
    int state = IDLE;

    static const int speed;
    Pond* target_pond;
public:
    Animal(Vector2f pos);
    Animal(float x, float y);
    ~Animal();

    bool move(int dt);
    bool moveTo(int dt, const Vector2f& targetPos);

    bool drink(int dt);
    bool find_pond();
    bool find_rand_pond();

    int get_state();
    int get_hunger();
    int get_thirst();
    int get_dir();

    void setState(AnimalState state);

    void check_dir();
    void draw_arr(char * arr, int width, int height);
    void draw_arr(char* arr, int width, int height, int alpha);

    virtual void update(int dt) = 0;
    virtual void draw() = 0;
    virtual int get_type() = 0;
    virtual float get_speed() = 0;
};