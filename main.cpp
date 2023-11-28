#include "EcoSystem.h"
#include "Camera.h"
#include "Entity.h"
#include "Animal.h"
#include "World.h"

int debug_count = 0;

// DEBUG
void debug(string name, int value) {
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text;
    text.setFont(font);
    text.setPosition(0, debug_count * 24);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setStyle(sf::Text::Bold);

    text.setString(name + ":" + to_string(value));

    debug_count++;
    world.window->draw(text);
}


// ����


// �ʽĵ���
class Herbivore : public Animal {
private:

public:
    Herbivore(float x, float y) :Animal(x, y) {};
};

// ���ĵ���
class Carnivore : public Animal {

};

// ��ĵ���
class Omnivore : public Animal {

};

class Rabbit : public Herbivore {
private:

public:
    Rabbit(float x, float y) :Herbivore(x, y) {};

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

    // COLORS
    sf::Color color_grass = sf::Color(94, 161, 82);

    // INIT
    RenderWindow window(sf::VideoMode(1200, 800), "My window");
    world.setWindow(&window);
    Camera camera;

    vector<Rabbit> rabbits = {};
    vector<Rabbit>::iterator r_iter;
    for (int i = 0; i < 10; i++) {
        rabbits.push_back(Rabbit(rand() % 1200, rand() % 800));
    }

    // SELECT
    Animal* selected;
    selected = &rabbits[0];

    sf::RectangleShape select_rect(sf::Vector2f(0.0, 0.0));
    select_rect.setSize(sf::Vector2f(40.0, 40.0));
    select_rect.setOutlineColor(sf::Color::Red);
    select_rect.setOutlineThickness(2.0);
    select_rect.setFillColor(sf::Color::Transparent);

    // MOUSE
    sf::Vector2i mouse_position;
    bool is_clicked = false;

    // MAIN LOOP
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            camera.update(event);
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
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                UPDATE_TIME = 15;
                speed = 2;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                UPDATE_TIME = 10;
                speed = 3;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                UPDATE_TIME = 7;
                speed = 4;
            }
        }

        curr_clock = clock();
        update_clock_delta = curr_clock - update_prev_clock;
        if ((update_clock_delta >= UPDATE_TIME) && (UPDATE_TIME != 0)) {
            update_prev_clock = curr_clock;

            // update all
            world.update(update_clock_delta);
            for (int i = 0; i < rabbits.size(); i++) {
                rabbits[i].update(update_clock_delta);

                // change slected
                if (is_clicked) {
                    float distance = sqrt(pow(rabbits[i].getPos().x - mouse_position.x, 2) + pow(rabbits[i].getPos().y - mouse_position.y, 2));
                    if (distance <= 50) {
                        selected = (Animal*)&rabbits[i];
                        is_clicked = false;
                    }
                }

            }
            is_clicked = false;

            select_rect.setPosition(selected->getPos().x, selected->getPos().y);
            camera.setCenter(select_rect.getPosition());
        }

        draw_clock_delta = curr_clock - draw_prev_clock;
        if (draw_clock_delta >= DRAW_TIME) {
            draw_prev_clock = curr_clock;
            fps = 1000.0 / draw_clock_delta;

            // clear the window with black color
            window.clear(color_grass);

            // draw everything here...
            for (r_iter = rabbits.begin(); r_iter != rabbits.end(); r_iter++) {
                r_iter->draw();
            }
            window.draw(select_rect);

            // debug
            debug_count = 0;
            //debug("day", world.get_day());
            //debug("time", world.get_time());
            //debug("frame", world.get_frame());
            debug("selected_x", selected->getPos().x);
            debug("selected_y", selected->getPos().y);
            debug("fps", fps);
            debug("speed", speed);

            //console output
            //cout << "day: " << world.get_day() << std::endl;
            //cout << "time: " << world.get_time() << std::endl;
            //cout << "frame: " << world.get_frame() << std::endl;
            // end the current frame

            camera.setView();

            window.display();
        }

    }
    return 0;
}
