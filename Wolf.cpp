#include "Wolf.h"
#include "World.h"

Wolf::Wolf(float x, float y) : Animal(x, y) {
    this->hunger = max_hunger;
    this->target_rabbit = NULL;
}

bool Wolf::find_rabbit() {
    Entity* entity;
    for (int i = 0; i < world.get_entity_num(RABBIT); i++) {
        entity = world.get_entity(i,RABBIT);
        // check rabbit 
        if (this->distance(*entity) < detect_range) {
            target_rabbit = (Animal*)(entity);
            return true;
        }
    }
    return false;
}

void Wolf::hunt(int dt) {
    float distance = this->distance(*target_rabbit);
    if (distance > 400) {
        target = target_rabbit->getPos();
        move(dt * walk_mult);
    } else if (this->distance(*target_rabbit) > 10) {
        target = target_rabbit->getPos();
        move(dt * run_mult);
    }
    else {
        world.delete_entity(target_rabbit, RABBIT);
        state = IDLE;
        hunger += 5000;
    }
}

void Wolf::draw() {
    sf::RectangleShape shape_r(sf::Vector2f(60, 60));
    shape_r.setFillColor(sf::Color(0, 0, 0));
    shape_r.setPosition(pos.x, pos.y);
    world.window->draw(shape_r);

    sf::CircleShape shape_red_c(10);
    shape_red_c.setRadius(detect_range);
    shape_red_c.setFillColor(sf::Color(0, 0, 0, 0));
    shape_red_c.setOutlineColor(sf::Color::Red);
    shape_red_c.setOutlineThickness(4);
    shape_red_c.setPosition(pos.x - detect_range, pos.y - detect_range);
    world.window->draw(shape_red_c);

    sf::CircleShape shape_blue_c(10);
    shape_blue_c.setRadius(300.0);
    shape_blue_c.setFillColor(sf::Color(0, 0, 0, 0));
    shape_blue_c.setOutlineColor(sf::Color::Blue);
    shape_blue_c.setOutlineThickness(4);
    shape_blue_c.setPosition(pos.x - 300, pos.y - 300);
    world.window->draw(shape_blue_c);
}

void  Wolf::update(int dt) {
    hunger -= dt;
    if (hunger < 3000) {
        if (find_rabbit()) {
            state = HUNTING;
        }
    }

    switch (state) {
    case IDLE:
        temp += dt;
        if (temp >= 2000) {
            //set random target
            temp = 0;
            target = Vector2f(pos.x + rand() % 500 - 250, pos.y + rand() % 500 - 250);
            state = MOVING;
        }
        break;
    case MOVING:
        move(dt);
        break;
    case HUNTING:
        hunt(dt);
        break;
    }
}

int Wolf::get_type() {
    return WOLF;
}

float Wolf::get_speed() {
    return speed;
}