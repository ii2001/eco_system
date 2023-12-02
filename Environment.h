#pragma once

#include "EcoSystem.h"
#include "Entity.h"

#include <chrono>
#include <thread>

class environment : public Entity {
private:

public:
    environment(Vector2f pos);
    environment(float x, float y);
    ~environment();

    virtual void draw() = 0;

};

// Ǯ
class grass : public environment {
private:
    int age = 1000 + rand() % 1000;
    bool hasEaten = false;

public:
    grass(float x, float y);

    void setHasEaten();
    void draw() override;
    void minus_age();
    int getAge();
    void isDead();
    void update(int dt);
    int get_type();
};
