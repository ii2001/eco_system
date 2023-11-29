#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "Camera.h"

using namespace sf;

class World {
private:
    int day;
    int time;
    int frame;

    int speed;

    vector<Entity*> entityVector;

public:
    World();
    ~World();

    RenderWindow* window;
    Camera* camera;

    void update(int dt);
    void draw();
    
    void setWindow(RenderWindow* window);
    void setCamera(Camera* camera);

    int add_entity(Entity *e);
    int delete_entity(Entity* e);

    Entity* get_entity(unsigned int index);

    int get_frame();
    int get_time();
    int get_day();
    int get_speed();

    void set_speed(int speed);
};

extern World world;