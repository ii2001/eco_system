#pragma once

#include "EcoSystem.h"
#include "Entity.h"

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
    int count = 3;


public:
    grass(float x, float y);

    void draw() override;
    void minusCount();
    void isDead();
    void update(int dt);
    int get_type();
    void respawn();
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



