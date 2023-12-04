///change
#include "Environment.h"
#include "World.h"


environment::environment(Vector2f pos) {
    this->setPos(pos);
}

environment::environment(float x, float y) {
    this->setPos(x, y);
}

environment::~environment() {

}

void grass::setHasEaten() {
    hasEaten = true;
}

void grass::draw() {
    sf::RectangleShape shape_g(sf::Vector2f(2, 2));
    char grass_fresh[13][14] = {
{'0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0'},
{'0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0'},
{'0', '1', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0'},
{'0', '1', '1', '0', '0', '1', '1', '0', '0', '1', '1', '0', '0', '0'},
{'0', '1', '1', '0', '0', '1', '1', '0', '0', '1', '1', '1', '0', '0'},
{'1', '2', '1', '0', '0', '1', '2', '1', '0', '1', '1', '1', '0', '0'},
{'1', '2', '1', '0', '0', '1', '2', '2', '0', '2', '1', '1', '0', '0'},
{'1', '3', '1', '0', '0', '1', '2', '2', '0', '2', '2', '1', '1', '0'},
{'1', '2', '1', '0', '0', '1', '2', '2', '0', '0', '2', '1', '2', '0'},
{'0', '1', '1', '1', '1', '1', '2', '2', '1', '1', '2', '2', '1', '0'},
{'0', '1', '1', '1', '1', '1', '2', '2', '1', '1', '2', '2', '2', '0'},
{'0', '1', '1', '2', '1', '1', '1', '1', '2', '2', '2', '2', '2', '0'},
{'0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0'} };
    char grass_normal[13][14] = {
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '2', '0', '0', '0', '1', '0', '0', '0'},
{'0', '0', '1', '0', '0', '1', '2', '0', '0', '2', '2', '1', '0', '0'},
{'0', '0', '1', '0', '0', '1', '2', '2', '0', '0', '2', '1', '0', '0'},
{'0', '0', '1', '1', '1', '1', '2', '2', '1', '1', '2', '2', '0', '0'},
{'0', '0', '1', '1', '1', '1', '2', '2', '1', '1', '2', '2', '0', '0'},
{'0', '0', '1', '2', '1', '1', '1', '1', '2', '2', '2', '2', '0', '0'},
{'0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0'} };
    char grass_dying[13][14] = {
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '2', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '1', '2', '0', '1', '0', '2', '0', '0', '0'},
    {'0', '0', '0', '0', '1', '1', '2', '0', '1', '1', '2', '0', '0', '0'},
    {'0', '0', '0', '2', '1', '1', '1', '0', '2', '2', '2', '2', '0', '0'},
    {'0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0'} };

    sf::RectangleShape grass;

    if (age > 800) {
        shape_g.setFillColor(sf::Color(0, 144, 0));
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 14; j++) {
                if (grass_fresh[i][j] != '0') {
                    shape_g.setPosition(pos.x + j * 2, pos.y + i * 2);
                    world.window->draw(shape_g);
                }
            }
        }
    }

    else if (400 < age && age <= 800) {
        shape_g.setFillColor(sf::Color(90, 144, 0));
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 14; j++) {
                if (grass_normal[i][j] != '0') {
                    shape_g.setPosition(pos.x + j * 2, pos.y + i * 2);
                    world.window->draw(shape_g);
                }
            }
        }
    }
    else {
        shape_g.setFillColor(sf::Color(102, 51, 0));
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 14; j++) {
                if (grass_dying[i][j] != '0') {
                    shape_g.setPosition(pos.x + j * 2, pos.y + i * 2);
                    world.window->draw(shape_g);
                }
            }
        }
    }
}

void grass::minusAge() {
    age--;
}

//void grass::respawn() {
//    age = 1000 + rand() % 1000;
//    findFullRabbit();
//    //Vector2f full_rabbit_pos = full_rabbit->getPos();
//    //setPos(full_rabbit_pos.x, full_rabbit_pos.y);
//
//}

void grass::isDead() {
    if (age < 0) {
        // hunger수치가 가장 높은 토끼 주변에 생성
        //respawn();
    }
}

int grass::get_type() {
    return GRASS;
}

//void grass::findFullRabbit()
//{
//    int maxHunger = -1000;
//    for (int i = 0; i < world.get_entity_num(RABBIT); i++) {
//        Entity* entity;
//        entity = world.get_entity(i, RABBIT);
//        //rabbit = (Rabbit*)(entity);
//        // get hunger도 안됨
//        //int rabitHunger = rabbit->get_hunger();
//        if (rabitHunger > maxHunger) {
//            maxHunger = rabitHunger;
//            //full_rabbit = rabbit;
//        }
//    }
//}

void grass::update(int dt) {
    isDead();
    minusAge();
}

grass::grass(float x, float y) :environment(x, y) {};







void Pond::draw() {
    sf::RectangleShape shape_p(sf::Vector2f(5, 5));
    char pond[13][14] = {
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0'},
{'0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0'},
{'0', '1', '1', '2', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0'},
{'1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1'},
{'1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1'},
{'1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1'},
{'1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1'},
{'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1', '1'},
{'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0'},
{'0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0'} };
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 14; j++) {
            if (pond[i][j] == '1') {
                shape_p.setFillColor(sf::Color(96, 96, 96));
                shape_p.setPosition(pos.x + j * 5, pos.y + i * 5);
                world.window->draw(shape_p);
            }
            else if (pond[i][j] == '2') {
                set_transparency(shape_p);
                //set_transparency(shape_p);
                shape_p.setPosition(pos.x + j * 5, pos.y + i * 5);
                world.window->draw(shape_p);
            }
        }
    }
}

void Pond::update(int dt) {
    refillPond();
}

void Pond::set_transparency(sf::RectangleShape& pix) {
    if (pond_quantity == 2) pix.setFillColor(sf::Color(0, 102, 204, 255));
    if (pond_quantity == 1) pix.setFillColor(sf::Color(0, 102, 204, 100));
    if (pond_quantity == 0) pix.setFillColor(sf::Color(0, 102, 204, 0));
}

int Pond::get_type() {
    return POND;
}
void Pond::resetCooltime() {
    refillCooltime = COOLTIME;
}
// pond_quantity가 2일 때만 먹을 수 있게
void Pond::refillPond() {
    if (pond_quantity == 0 || pond_quantity ==1) {
        refillCooltime--;
        if (refillCooltime < 0) {
            pond_quantity++;
            resetCooltime();
        }
    }
}

Pond::Pond(float x, float y) :environment(x, y) {};
