#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;

#define UPDATE_TIME 30

//ANIMAL STATES
#define IDLE 0
#define SLEEP 1
#define EATING 2
#define MOVING 3

// GLOBAL VARIABLES
// create the window
sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");
const double PI = 3.1415926;

// 동물
class Animal {
private:
    float x;
    float y;

    int hunger;
    int thirst;

    int state = IDLE;

    float speed = 3.0;
    float vel_x = 3.0;
    float vel_y = 0.0;
    double theta;

    int temp = 0;

public:
    Animal(float x, float y):x(x),y(y) {};

    float get_x() { return x; }
    float get_y() { return y; }
    void set_x(float a) { x = a; };
    void set_y(float a) { y = a; };

    void update() {
        if (rand() % 100 <= temp) {
            //change state
            if (state == IDLE) {
                change_dir();
                state = MOVING;
            } else{
                state = IDLE;
            }
        }
        else {
            temp++;
            switch (state)
            {
            case IDLE:
                break;
            case MOVING:
                move();
                break;
            default:
                break;
            }
        }
    }

    void move() {
        x += vel_x;
        y += vel_y;
    }

    void change_dir() {
        temp = 0;
        theta = rand() % 360;
        vel_y = speed * sin(theta * PI / 180);
        vel_x = speed * cos(theta * PI / 180);
    }

    void draw() {
        sf::CircleShape shape(20);
        sf::CircleShape s1(7);
        sf::CircleShape s2(7);

        shape.setPosition(x, y);
        s1.setPosition(x, y - 10);
        s2.setPosition(x + 26, y - 10);

        window.draw(shape);
        window.draw(s1);
        window.draw(s2);
    }

    void print_status() {
        printf("vel_x : %f\n", vel_x);
        printf("vel_y : %f\n", vel_y);
        printf("direction : %f\n", theta);
    }

};

// 초식동물
class Herbivore  : public Animal{
private:

public:
    Herbivore(float x, float y) :Animal(x, y) {};
};

// 육식동물
class Carnivore : public Animal {

};

// 잡식동물
class Omnivore : public Animal {

};

class Rabbit : public Herbivore{
private:

public:
    Rabbit(float x, float y) :Herbivore(x,y){};

    
};

int main()
{   
    //random
    srand((unsigned int)time(NULL));

    //time
    clock_t prev_time = clock();
    clock_t curr_time;

    //init
    vector<Rabbit> rabbits = {};
    vector<Rabbit>::iterator r_iter;
    for (int i = 0; i < 10; i++) {
        rabbits.push_back(Rabbit(rand() % 1200, rand() % 800));
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        curr_time = clock();
        if (curr_time - prev_time >= UPDATE_TIME) {
            prev_time = curr_time;

            // clear the window with black color
            window.clear(sf::Color::Black);

            // update all
            for (r_iter = rabbits.begin(); r_iter != rabbits.end(); r_iter++) {
                r_iter->update();
            }

            // draw everything here...
            for (r_iter = rabbits.begin(); r_iter != rabbits.end(); r_iter++) {
                r_iter->draw();
            }
            //console output
            system("cls");
            rabbits[0].print_status();

            // end the current frame
            window.display();
        }
        
    }

    return 0;
}