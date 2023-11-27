#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <math.h>
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;

//ANIMAL STATES
#define IDLE 0
#define SLEEP 1
#define EATING 2
#define MOVING 3

// GLOBAL VARIABLES
// create the window
sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");
const double PI = 3.1415926;

// DEBUG
class Function {
public:
    Function() {};
    Function(int value()) {
        ptr = value;
    };
    int(*ptr) ();
};

class Debug {
private:
    vector<bool> is_func;
    vector<Function> funcs;
    vector<string> names;
    vector<int*>  values;
    vector<sf::Text *> texts;

    sf::Font font;
    
public:
    Debug() {
        if (!font.loadFromFile("arial.ttf")) {
            cout << "failed to loat font file" << endl;
        }
    };
    void null_func(){}
    void add(string name, int* value) {
        sf::Text * text = new sf::Text;

        text->setFont(font);
        text->setPosition(0, texts.size() * 24);
        text->setCharacterSize(24);
        text->setFillColor(sf::Color::White);
        text->setOutlineColor(sf::Color::Black);
        text->setOutlineThickness(2);
        text->setStyle(sf::Text::Bold);
        text->setString(name + ':' + to_string(*value));
        
        is_func.push_back(false);
        funcs.push_back(Function());
        texts.push_back(text);
        names.push_back(name);
        values.push_back(value);
    }

    void add(string name, int func()) {
        sf::Text* text = new sf::Text;

        text->setFont(font);
        text->setPosition(0, texts.size() * 24);
        text->setCharacterSize(24);
        text->setFillColor(sf::Color::White);
        text->setOutlineColor(sf::Color::Black);
        text->setOutlineThickness(2);
        text->setStyle(sf::Text::Bold);

        is_func.push_back(true);
        funcs.push_back(Function(func));
        texts.push_back(text);
        names.push_back(name);
        values.push_back(0);
    }
    void draw() {
        for (int i = 0; i < texts.size(); i++) {
            if (is_func[i]) {
                texts[i]->setString(names[i] + ':' + to_string(funcs[i].ptr()));
                window.draw(*texts[i]);
            }
            else {
                texts[i]->setString(names[i] + ':' + to_string(*values[i]));
                window.draw(*texts[i]);
            }   
        }
    }
};


// 환경
class World {
private:
    int day = 0;
    int time = 0;
    int frame = 0;
public:
    World() {};

    void update() {
        frame++;
        if (frame >= 25) {
            time += 1;
            frame = 0;
        }

        if (time >= 24) {
            day += 1;
            time = 0;
        }
    }

    int get_frame() { return frame; };
    int get_time() { return time; };
    int get_day() { return day; };
};

// 동물
class Animal {
private:
    float x;
    float y;
    int direction;

    int hunger;
    int thirst;

    int state = IDLE;

    float speed = 3.0;
    float vel_x = 3.0;
    float vel_y = 0.0;

    int temp = 0;

    bool jump = false;
    int jump_frame = 0;

public:
    Animal(float x, float y) :x(x), y(y) {};

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
            }
            else {
                state = IDLE;
            }
        }
        else {
            temp++;
            switch (state)
            {
            case IDLE:
                jump = false;
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
        if (jump == false && jump_frame > 5)
        {
            jump = true;
            jump_frame = 0;
        }
        else if (jump == true && jump_frame > 10)
        {
            jump = false;
            jump_frame = 0;
        }
        jump_frame++;
    }

    void change_dir() {
        direction = rand() % 360;
        temp = 0;   
        vel_y = speed * sin(direction * PI / 180);
        vel_x = speed * cos(direction * PI / 180);
        jump = false;
        jump_frame = 0;
    }

    /*
    void draw() {
        sf::CircleShape shape(20);
        sf::CircleShape s1(7);
        sf::CircleShape s2(7);
        
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
        
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(255, 255, 0));
        s1.setPosition(x, y - 10);
        s2.setPosition(x + 26, y - 10);

        window.draw(shape);
        window.draw(s1);
        window.draw(s2);
        sf::RectangleShape rab[13][14];

    }
    */
    void draw()
    {
        char rabbit_move[13][14] = { 
            {'0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '3', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '3', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '1', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'1', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0', '0', '0', '0'},
            {'1', '2', '2', '1', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'1', '3', '2', '1', '2', '2', '2', '2', '2', '2', '2', '1', '1', '1'},
            {'1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '2', '1'},
            {'0', '1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '1', '1', '2', '2', '2', '1'},
            {'0', '0', '1', '2', '2', '1', '1', '1', '2', '2', '2', '2', '2', '1'},
            {'0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1'} };


        char rabbit_jump[14][16] = { 
            {'0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '3', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '3', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '1', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'1', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0', '0', '0', '0', '0', '0'},
            {'1', '2', '2', '1', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0'},
            {'1', '3', '2', '1', '2', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0', '0'},
            {'1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '1', '1', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '1', '1', '0', '0', '1', '2', '2', '2', '1', '0'},
            {'0', '0', '0', '1', '2', '1', '0', '0', '0', '0', '0', '1', '1', '2', '2', '1'},
            {'0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1'} };


        char rabbit_back[16][13] = { 
            {'0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0'},
            {'0', '1', '2', '1', '0', '0', '0', '0', '0', '1', '2', '1', '0'},
            {'0', '1', '3', '2', '1', '0', '0', '0', '1', '2', '3', '1', '0'},
            {'0', '0', '1', '3', '2', '1', '1', '1', '2', '3', '1', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0'},
            {'0', '1', '2', '2', '1', '2', '2', '2', '1', '2', '2', '1', '0'},
            {'0', '0', '1', '1', '1', '2', '2', '2', '1', '1', '1', '0', '0'},
            {'0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '0', '0', '0'} };

        
        char rabbit_back_jump[19][13] = { 
            {'0', '1', '1', '0', '0', '1', '0', '1', '0', '0', '1', '1', '0'},
            {'0', '1', '2', '1', '1', '2', '1', '2', '1', '1', '2', '1', '0'},
            {'0', '1', '3', '2', '1', '2', '1', '2', '1', '2', '3', '1', '0'},
            {'0', '0', '1', '3', '2', '1', '1', '1', '2', '3', '1', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '1', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0'},
            {'0', '1', '2', '1', '2', '2', '2', '2', '2', '1', '2', '1', '0'},
            {'0', '1', '1', '2', '1', '2', '2', '2', '1', '2', '1', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '1', '1', '1', '1', '1', '2', '1', '0', '0'},
            {'0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0'},
            {'0', '1', '0', '0', '1', '0', '0', '0', '1', '0', '0', '1', '0'},
            {'0', '1', '0', '0', '1', '0', '0', '0', '1', '0', '0', '1', '0'},
            {'0', '0', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0'} };


        char rabbit_front[17][13] = { 
            {'1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0'},
            {'1', '2', '1', '0', '0', '0', '1', '2', '1', '0', '0', '0', '0'},
            {'1', '3', '2', '1', '0', '1', '2', '3', '1', '0', '0', '0', '0'},
            {'0', '1', '3', '1', '0', '1', '3', '1', '0', '0', '0', '0', '0'},
            {'0', '1', '2', '2', '1', '2', '2', '1', '0', '0', '0', '0', '0'},
            {'1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0'},
            {'1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0'},
            {'1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0'},
            {'1', '2', '2', '2', '3', '2', '2', '2', '1', '0', '0', '0', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0', '0', '0'},
            {'0', '0', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '0'},
            {'0', '1', '1', '2', '2', '2', '2', '1', '1', '1', '2', '2', '1'},
            {'1', '2', '1', '2', '2', '2', '2', '1', '2', '1', '2', '2', '1'},
            {'1', '2', '1', '2', '2', '2', '2', '1', '2', '2', '1', '1', '0'},
            {'1', '2', '1', '2', '1', '2', '2', '1', '2', '2', '1', '0', '0'},
            {'1', '1', '2', '2', '1', '2', '2', '1', '2', '2', '1', '0', '0'},
            {'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0'} };

        
        char rabbit_front_jump[14][13] = { 
            {'0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '2', '1', '1', '1', '2', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '0', '1', '3', '2', '1', '2', '1', '2', '3', '1', '0', '0'},
            {'0', '0', '0', '1', '3', '1', '1', '1', '3', '1', '0', '0', '0'},
            {'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '2', '2', '3', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '1', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0'},
            {'0', '1', '2', '1', '1', '1', '1', '1', '1', '1', '2', '1', '0'},
            {'0', '1', '2', '2', '1', '0', '0', '0', '1', '2', '2', '1', '0'},
            {'0', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0'} };


        if ((direction<45)||(direction>315)) // 오른쪽
        {
            if (!jump) // 점프 x
            {
                for (int i = 0; i < 13; i++)
                {
                    for (int j = 0; j < 14; j++) {
                        if (rabbit_move[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(x + 39 - j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_move[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(x + 39 - j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_move[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(x + 39 - j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                    }
                }
            }
            else // 점프 0
            {
                for (int i = 0; i < 14; i++)
                {
                    for (int j = 0; j < 16; j++) {
                        if (rabbit_jump[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(x + 45 - j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_jump[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(x + 45 - j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_jump[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(x + 45 - j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                    }
                }
            }
        }
        else if ((direction >= 135) && (direction <= 225)) // 왼쪽
        {
            if (!jump) // 점프 x
            {
                for (int i = 0; i < 13; i++)
                {
                    for (int j = 0; j < 14; j++) {
                        if (rabbit_move[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_move[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_move[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                    }
                }
            }
            else // 점프 0
            {
                for (int i = 0; i < 14; i++)
                {
                    for (int j = 0; j < 16; j++) {
                        if (rabbit_jump[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_jump[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_jump[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                    }
                }
            }
        }
        else if ((direction >= 225) && (direction <= 315)) // 위쪽
        {
            if (!jump) // 점프 x
            {
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j < 13; j++) {
                        if (rabbit_back[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_back[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_back[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                    }
                }
            }
            else // 점프 0
            {
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j < 13; j++) {
                        if (rabbit_back_jump[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_back_jump[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_back_jump[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                    }
                }
            }
        }
        else if ((direction >= 45) && (direction <= 135)) // 아래쪽
        {
            if (!jump) // 점프 x
            {
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 13; j++) {
                        if (rabbit_front[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_front[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_front[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                    }
                }
            }
            else // 점프 0
            {
                for (int i = 0; i < 14; i++)
                {
                    for (int j = 0; j < 13; j++) {
                        if (rabbit_front_jump[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_front_jump[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                        else if (rabbit_front_jump[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(x + j * 3, y + i * 3);
                            window.draw(shape_r);
                        }
                    }
                }
            }
        }
    }
    
    void print_status() {
        printf("vel_x : %f\n", vel_x);
        printf("vel_y : %f\n", vel_y);
    }

};

// 초식동물
class Herbivore : public Animal {
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

class Rabbit : public Herbivore {
private:

public:
    Rabbit(float x, float y) :Herbivore(x, y) {};

};

//자연 환경
class environment {
private:
protected:
    float x;
    float y;
public:
    environment(float x, float y) :x(x), y(y) {};

    virtual void draw() {
        sf::RectangleShape grass;
        grass.setSize(sf::Vector2f(10, 10));

        grass.setPosition(x, y);

        window.draw(grass);
    }

};

// 풀
class grass : public environment {
private:
    bool hasEaten = false;

public:
    grass(float x, float y) : environment(x, y), hasEaten(false) {};

    void setHasEaten() {
        hasEaten = true;
    }

    void draw() override {
        if (!hasEaten) {
            sf::RectangleShape grassShape;
            grassShape.setSize(sf::Vector2f(10, 10));
            grassShape.setPosition(x, y);
            window.draw(grassShape);
        }
    }
};

int main()
{
    // RANDOM SEED
    srand((unsigned int)time(NULL));

    // FRAME
    int UPDATE_TIME = 30;
    int DRAW_TIME = 30;
    int speed = 1;

    clock_t update_prev_clock = clock();
    clock_t draw_prev_clock = clock();
    clock_t curr_clock;
    int update_clock_delta;
    int draw_clock_delta;
    int fps;
    int tps;

    // COLORS
    sf::Color color_grass = sf::Color(94, 161, 82);

    // INIT
    World world = World();

    vector<grass> grasses = {};
    vector<grass>::iterator g_iter;
    for (int i = 0; i < 10; i++) {
        grasses.push_back(grass(rand() % 1200, rand() % 800));
    }
    
    vector<Rabbit> rabbits = {};
    vector<Rabbit>::iterator r_iter;
    for (int i = 0; i < 10; i++) {
        rabbits.push_back(Rabbit(rand() % 1200, rand() % 800));
    }

    // SELECT
    Animal* selected;
    selected = &rabbits[0];

    sf::RectangleShape select_rect(sf::Vector2f(0.0,0.0));
    select_rect.setSize(sf::Vector2f(40.0, 40.0));
    select_rect.setOutlineColor(sf::Color::Red);
    select_rect.setOutlineThickness(2.0);
    select_rect.setFillColor(sf::Color::Transparent);

    // MOUSE
    sf::Vector2i mouse_position;
    bool is_clicked = false;

    // DEBUG
    Debug debug = Debug();
    //debug("day", world.get_day());
    //debug("time", world.get_time());
    //debug("frame", world.get_frame());
    //debug("selected_x",selected->get_x());
    //debug.add("selected_y", selected->get_y);
    debug.add("tps", &tps);
    debug.add("fps", &fps);
    //debug("speed", speed);
    // MAIN LOOP
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mouse_position = sf::Mouse::getPosition(window);
                is_clicked = true;
            }

            //speed
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                UPDATE_TIME = 0;
                speed = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                UPDATE_TIME = 30;
                speed = 1;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                UPDATE_TIME = 15;
                speed = 2;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                UPDATE_TIME = 10;
                speed = 3;
            }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                UPDATE_TIME = 7;
                speed = 4;
            }
        }

        curr_clock = clock();
        update_clock_delta = curr_clock - update_prev_clock;
        if ((update_clock_delta >= UPDATE_TIME) && (UPDATE_TIME != 0)) {
            tps = 1000.0 / update_clock_delta;
            update_prev_clock = curr_clock;

            // update all
            world.update();
            for (int i = 0; i < rabbits.size(); i++) {
                rabbits[i].update();

                // change slected
                if (is_clicked) {
                    float distance = sqrt(pow(rabbits[i].get_x() - mouse_position.x, 2) + pow(rabbits[i].get_y() - mouse_position.y, 2));
                    if (distance <= 50) {
                        selected = (Animal*)&rabbits[i];
                        is_clicked = false;
                    }
                }
                
            }
            is_clicked = false;

            select_rect.setPosition(selected->get_x(), selected->get_y());
        }

        draw_clock_delta = curr_clock - draw_prev_clock;
        if (draw_clock_delta >= DRAW_TIME) {
            draw_prev_clock = curr_clock;
            fps = 1000.0 / draw_clock_delta;

            window.clear(color_grass);
            // draw everything here...
            for (r_iter = rabbits.begin(); r_iter != rabbits.end(); r_iter++) {
                r_iter->draw();
            }
            for (g_iter = grasses.begin(); g_iter != grasses.end(); g_iter++) {
                g_iter->draw();
            }
            window.draw(select_rect);
            debug.draw();
            //console output
            //cout << "day: " << world.get_day() << std::endl;
            //cout << "time: " << world.get_time() << std::endl;
            //cout << "frame: " << world.get_frame() << std::endl;
            // end the current frame
            window.display();
        }

    }

    return 0;
}
