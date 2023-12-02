#pragma once

#include "EcoSystem.h"
#include "Entity.h"
#include "Environment.h"


class Animal : public Entity {
protected:
    int direction = 0;

    Vector2f target;

    int hunger = 10;
    int thirst = 10;
    int desire_for_sleep = 0;
    int state = IDLE;

    float speed = 3.0;

    Vector2f vel = Vector2f(3.0, 0.0);

    int temp = 0;

    bool jump = false;
    int jump_frame = 0;

public:
    Animal(Vector2f pos);
    Animal(float x, float y);
    ~Animal();

    void update(int dt);


    //moving_animal
    void move();
    void sleep();
    // 동물이 풀을 먹는 함수
    void eatGrass();

    void moveTo(const Vector2f& targetPos);

    void change_dir();

    //void draw() {
        //sf::CircleShape shape(20);
        //sf::CircleShape s1(7);
        //sf::CircleShape s2(7);
        /*
        unsigned char a[728] = { 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 94, 161, 82, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 130, 255, 255, 0, 0, 0, 255, 255, 130, 255, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 130, 255, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 255, 130, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 255, 130, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 94, 161, 82, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 130, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 130, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 130, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 130, 255, 255, 255, 130, 255, 255, 255, 130, 255, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 94, 161, 82, 255, 94, 161, 82, 255, 94, 161, 82, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255 };
        sf::Texture texture;
        texture.create(13, 14);
        sf::Uint8* pixels = new sf::Uint8[14 * 13 * 4]; // * 4 because pixels have 4 components (RGBA)
        for (int i = 0; i < 728; i += 4)
        {
            pixels[i] = a[i];
        }
        texture.update(pixels);
        sf::RectangleShape rabbit_shape(sf::Vector2f(13, 14));
        rabbit_shape.setTexture(&texture);
        rabbit_shape.setPosition(x, y);
        window.draw(rabbit_shape);
        */
        //shape.setPosition(x, y);
        //shape.setFillColor(sf::Color(255, 255, 0));
        //s1.setPosition(x, y - 10);
        //s2.setPosition(x + 26, y - 10);

        //window.draw(shape);
        //window.draw(s1);
        //window.draw(s2);
        //sf::RectangleShape rab[13][14];

    //}
    void draw(const char a[19][16]);
    void draw();

    void print_status();

    int get_state();

    int get_hunger();

    virtual int get_type() = 0;
};

class Rabbit : public Animal {
private:

public:
    Rabbit(float x, float y);

    int get_type();
};
