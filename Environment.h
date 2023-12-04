#pragma once

#include "EcoSystem.h"
#include "Entity.h"

// Animal.h가 포함되어서 그런 거 같다. Entity는 되는데 animal이랑 rabbit 이 안된다.

#define COOLTIME 150

class environment : public Entity {
private:

public:
    environment(Vector2f pos);
    environment(float x, float y);
    ~environment();

    virtual void draw() = 0;

};

// age modify
class grass : public environment {
private:    
    int age = 1000 + rand() % 1000;
    bool hasEaten = false;


public:
    grass(float x, float y);

    void setHasEaten();
    void draw() override;
    void minusAge();
    void isDead();
    void update(int dt);
    int get_type();
    //void respawn();
    //void findFullRabbit();
};

class Pond : public environment {
private:
    int pond_quantity = 0;
    int refillCooltime = COOLTIME;
public:
    Pond(float x, float y);

    void draw();
    void refillPond();
    void resetCooltime();
    int get_type();
    void update(int dt);
    void set_transparency(sf::RectangleShape& pix);
};



