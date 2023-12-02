#include "Wolf.h"
#include "World.h"

Wolf::Wolf(float x, float y) : Animal(x, y) {
    this->hunger = max_hunger;
    this->speed = 300.0;
}

void Wolf::move(int dt) {
    float delta_x = target.x - pos.x;
    float delta_y = target.y - pos.y;
    float vector_size = sqrt(pow(delta_x, 2) + pow(delta_y, 2));

    if (vector_size < 10) {
        state = IDLE;
    }
    else {
        pos.x += speed * dt * delta_x / vector_size / 1000;
        pos.y += speed * dt * delta_y / vector_size / 1000;
    }
}

bool Wolf::find_rabbit() {
    Entity* entity;
    for (int i = 0; i < world.get_entity_num(RABBIT); i++) {
        entity = world.get_entity(i, RABBIT);
        // check rabbit
        if (entity->get_type() == RABBIT) {
            if (this->distance(*entity) < 1000) {
                target_rabbit = (Rabbit*)(entity);
                return true;
            }
        }
    }
    return false;
}

void Wolf::hunt(int dt) {
    if (this->distance(*target_rabbit) > 10) {
        target = target_rabbit->getPos();
        move(dt);
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
}

void  Wolf::update(int dt) {
    hunger -= 10;
    if (hunger < 3000) {
        if (find_rabbit()) {
            state = HUNTING;
        }
    }

    switch (state) {
    case IDLE:
        temp += dt;
        if (temp >= 1000) {
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