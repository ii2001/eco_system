#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "Animal.h"
#include "Wolf.h"
#include "Environment.h"

using namespace sf;

class World {
private:
    int day;
    int time;
    int frame;

    int speed;

    vector<Animal*> rabbitVector;
    vector<Wolf*> wolfVector;
    vector<grass*> grassVector;
public:
    World();
    ~World();

    RenderWindow* window;

    void update(int dt);
    void draw();
    
    void setWindow(RenderWindow* window);


    int add_entity(Entity *e, Type t);      //t에 맞는 벡터에 e 추가
    int delete_entity(Entity* e, Type t);   //t에 맞는 벡터에 e 삭제
    
    Entity* get_entity(unsigned int index, Type t); //type에 맞는 vector에 index번째 객체 반환

    int get_entity_num(Type t);             //type에 맞는 vector 크기 반환

    int get_frame();
    int get_time();
    int get_day();
    int get_speed();

    void set_speed(int speed);
};

extern World world;