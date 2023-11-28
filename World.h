#pragma once

#include "EcoSystem.h"
#include "Entity.h"

using namespace sf;

class World {
private:
    int day = 0;
    int time = 0;
    int frame = 0;

    vector<Entity*> entityVector;

public:
    World();
    ~World();

    RenderWindow* window;

    // update���� ���ڷ� delta �޾ƿͼ� �װŷ� �ؾ����� ������..?
    void update(int dt);
    void draw();

    void setWindow(RenderWindow* window);

    int add_entity(Entity *e);
    int delete_entity(Entity* e);

    int get_frame();
    int get_time();
    int get_day();
};

extern World world;