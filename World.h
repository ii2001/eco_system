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


    int add_entity(Entity *e, Type t);      //t�� �´� ���Ϳ� e �߰�
    int delete_entity(Entity* e, Type t);   //t�� �´� ���Ϳ� e ����
    
    Entity* get_entity(unsigned int index, Type t); //type�� �´� vector�� index��° ��ü ��ȯ

    int get_entity_num(Type t);             //type�� �´� vector ũ�� ��ȯ

    int get_frame();
    int get_time();
    int get_day();
    int get_speed();

    void set_speed(int speed);
};

extern World world;