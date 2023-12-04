#pragma once

#include "EcoSystem.h"
#include "Entity.h"

#include <chrono>
#include <thread>

class environment : public Entity{
private:
protected:
    int age; // randome age for different lifecycle
    bool markedForDeletion = false;
public:
    environment(float x, float y, int age) :Entity(x, y), age(age) {};
    
    virtual void draw() = 0;

};

// Ǯ
class grass : public environment {
private:
    bool hasEaten = false;

public:
    grass(float x, float y, int age);

    void setHasEaten();
    void draw() override;
    void minus_age();
    int getAge();
    void isDead(vector<grass>& grasses, std::vector<grass>::iterator& iter);
    void update(int dt);
    int get_type();
};

void createGrass(vector<grass>& grasses);