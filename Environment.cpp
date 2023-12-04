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
void grass::draw() {
    sf::RectangleShape shape_g(sf::Vector2f(2, 2));
    char grass_fresh[13][14] = {
{'0', '3', '3', '0', '0', '0', '3', '3', '0', '0', '3', '0', '0', '0'},
{'0', '3', '1', '3', '0', '3', '1', '3', '0', '3', '1', '3', '0', '0'},
{'3', '1', '1', '3', '0', '3', '1', '3', '0', '3', '1', '3', '0', '0'},
{'3', '1', '1', '3', '3', '1', '1', '3', '0', '3', '1', '3', '0', '0'},
{'3', '1', '1', '3', '3', '1', '1', '3', '0', '3', '1', '1', '3', '0'},
{'3', '1', '1', '3', '3', '1', '2', '1', '3', '1', '1', '1', '3', '0'},
{'3', '1', '1', '3', '3', '1', '2', '2', '3', '2', '3', '1', '3', '0'},
{'3', '1', '1', '3', '3', '1', '3', '2', '3', '2', '3', '1', '1', '3'},
{'3', '1', '1', '3', '3', '1', '3', '2', '3', '0', '3', '1', '2', '3'},
{'3', '1', '3', '1', '1', '1', '3', '2', '1', '1', '3', '2', '1', '3'},
{'3', '1', '3', '1', '1', '1', '3', '2', '1', '1', '3', '2', '2', '3'},
{'3', '1', '3', '1', '3', '1', '3', '1', '2', '2', '3', '2', '2', '3'},
{'0', '3', '1', '1', '1', '1', '1', '1', '1', '1', '3', '1', '1', '3'} };
    char grass_normal[13][14] = {
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '3', '0', '0', '3', '1', '3', '0', '0'},
{'0', '0', '3', '0', '0', '3', '2', '3', '0', '3', '1', '3', '0', '0'},
{'0', '3', '1', '3', '3', '1', '2', '3', '0', '2', '2', '1', '3', '0'},
{'0', '3', '1', '3', '3', '1', '2', '2', '3', '3', '2', '1', '3', '0'},
{'0', '3', '1', '1', '1', '3', '2', '2', '1', '1', '3', '2', '3', '0'},
{'0', '3', '1', '1', '1', '3', '2', '2', '1', '1', '3', '2', '3', '0'},
{'0', '3', '1', '3', '1', '3', '1', '1', '2', '2', '3', '2', '3', '0'},
{'0', '3', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '3', '0'} };
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

    if (count == 3) {
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 14; j++) {
                if (grass_fresh[i][j] == '3') {
                    shape_g.setFillColor(sf::Color(0, 0, 0));
                    shape_g.setPosition(pos.x + j * 2, pos.y + i * 2);
                    world.window->draw(shape_g);
                }
                else if (grass_fresh[i][j] == '1' || grass_fresh[i][j] == '2') {
                    shape_g.setFillColor(sf::Color(0, 144, 0));
                    shape_g.setPosition(pos.x + j * 2, pos.y + i * 2);
                    world.window->draw(shape_g);
                }
            }
        }
    }

    else if (count == 2) {
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 14; j++) {
                if (grass_normal[i][j] == '3') {
                    shape_g.setFillColor(sf::Color(0, 0, 0));
                    shape_g.setPosition(pos.x + j * 2, pos.y + i * 2);
                    world.window->draw(shape_g);
                }
                else if (grass_normal[i][j] != '0') {
                    shape_g.setFillColor(sf::Color(90, 144, 0));
                    shape_g.setPosition(pos.x + j * 2, pos.y + i * 2);
                    world.window->draw(shape_g);
                }
            }
        }
    }
    else if(count == 1) {
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

void grass::minusCount() {
    count--;
}

int signDecide() {
    int signDecider = rand() % 2;
    if (signDecider == 0) return 1;
    else return -1;
}

void grass::respawn() {
    count = 3;
    //여기서 연못 주변에 나오게 
    Entity* entity;
    int pondCount = world.get_entity_num(POND);
    entity = world.get_entity(rand() % pondCount, POND);
    Vector2f randPondPos = entity->getPos();
    setPos(randPondPos.x + signDecide() * rand() % 150, randPondPos.y + signDecide() * rand() % 150);
}

void grass::isDead() {
    if (count <= 0) {
        respawn();
    }
}

int grass::get_type() {
    return GRASS;
}

void grass::update(int dt) {
    isDead();
}

grass::grass(float x, float y) :environment(x, y) {};







void Pond::draw() {
    sf::RectangleShape shape_p(sf::Vector2f(5, 5));
    char pond[13][16] = {
{'0','0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0','0'},
{'0','0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0','0'},
{'0','0', '0', '0', '3', '3', '3', '3', '3', '3', '3', '0', '0', '0', '0','0'},
{'0','0', '0', '3', '1', '3', '1', '3', '1', '1', '1', '3', '3', '0', '0','0'},
{'0','0', '3', '1', '3', '1', '3', '3', '1', '1', '3', '1', '1', '3', '0','0'},
{'0','3', '3', '1', '3', '2', '2', '2', '3', '3', '2', '3', '3', '1', '3','0'},
{'3','1', '1', '3', '2', '2', '2', '2', '2', '2', '2', '2', '2', '3', '1','3'},
{'3','1', '1', '3', '2', '2', '2', '2', '2', '2', '2', '2', '2', '3', '1','3'},
{'3','1', '3', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '3', '1','3'},
{'3','1', '3', '2', '3', '3', '2', '2', '2', '2', '2', '2', '3', '1', '3','3'},
{'0','3', '1', '3', '1', '1', '3', '3', '2', '3', '3', '2', '3', '1', '1','3'},
{'0','3', '1', '3', '1', '1', '3', '1', '3', '1', '1', '3', '1', '1', '3','0'},
{'0','0', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '0','0'} };
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 16; j++) {
            if (pond[i][j] == '1') {
                shape_p.setFillColor(sf::Color(96, 96, 96));
                shape_p.setPosition(pos.x + j * 5, pos.y + i * 5);
                world.window->draw(shape_p);
            }
            else if (pond[i][j] == '2') {
                set_transparency(shape_p);
                shape_p.setPosition(pos.x + j * 5, pos.y + i * 5);
                world.window->draw(shape_p);
            }
            else if (pond[i][j] == '3') {
                shape_p.setFillColor(sf::Color(0, 0, 0));
                shape_p.setPosition(pos.x + j * 5, pos.y + i * 5);
                world.window->draw(shape_p);
            }
        }
    }
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
void Pond::update(int dt) {
    refillPond();
}


Pond::Pond(float x, float y) :environment(x, y) {};
