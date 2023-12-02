#include "World.h"

World::World()
    :day(0), time(0), frame(0), speed(1) {

}

World::~World() {
    int size = rabbitVector.size();

    for (int i = size - 1; i >= 0; i--) {
        delete rabbitVector[i];
        rabbitVector.pop_back();
    }

    size = wolfVector.size();

    for (int i = size - 1; i >= 0; i--) {
        delete wolfVector[i];
        wolfVector.pop_back();
    }

    size = grassVector.size();

    for (int i = size - 1; i >= 0; i--) {
        delete grassVector[i];
        grassVector.pop_back();
    }
}

void World::update(int dt) {
    if (speed == 0)
        return;

    frame += speed;

    if (frame >= 25) {
        time += 1;
        frame = 0;
    }

    if (time >= 24) {
        day += 1;
        time = 0;
    }

    int size = rabbitVector.size();
    for (int i = 0; i < size; i++) {
        rabbitVector[i]->update(dt);
    }

    size = wolfVector.size();
    for (int i = 0; i < size; i++) {
        wolfVector[i]->update(dt);
    }

    size = grassVector.size();
    for (int i = 0; i < size; i++) {
        grassVector[i]->update(dt);
    }
}

void World::draw() {
    int size = rabbitVector.size();
    for (int i = 0; i < size; i++) {
        rabbitVector[i]->draw();
    }

    size = wolfVector.size();
    for (int i = 0; i < size; i++) {
        wolfVector[i]->draw();
    }

    size = grassVector.size();
    for (int i = 0; i < size; i++) {
        grassVector[i]->draw();
    }
}

void World::setWindow(RenderWindow* window) {
    this->window = window;
}

int World::add_entity(Entity* e, Type t) {
    switch (t) {
    case RABBIT:
        rabbitVector.push_back((Animal*)e);
        return rabbitVector.size() - 1;
    case WOLF:
        wolfVector.push_back((Wolf*)e);
        return wolfVector.size() - 1;
    case GRASS:
        grassVector.push_back((grass*)e);
        return grassVector.size() - 1;
    }
    return -1;
}

int World::delete_entity(Entity* e, Type t) {
    int i = 0;

    switch (t) {
    case RABBIT:
        for (auto iter = rabbitVector.begin(); iter != rabbitVector.end(); iter++, i++) {
            if (*iter == e) {
                rabbitVector.erase(iter);
                return i;
            }
        }
        break;
    case WOLF:
        for (auto iter = wolfVector.begin(); iter != wolfVector.end(); iter++, i++) {
            if (*iter == e) {
                wolfVector.erase(iter);
                return i;
            }
        }
        break;
    case GRASS:
        for (auto iter = grassVector.begin(); iter != grassVector.end(); iter++, i++) {
            if (*iter == e) {
                grassVector.erase(iter);
                return i;
            }
        }
        break;
    }
    return -1;
}

Entity* World::get_entity(unsigned int index, Type t) {
    switch (t) {
    case RABBIT: return rabbitVector[index];
    case WOLF: return wolfVector[index];
    case GRASS: return grassVector[index];
    }
    return NULL;
}

int World::get_entity_num(Type t) {
    switch (t) {
    case ENTITY:
        return rabbitVector.size() \
            + wolfVector.size() + grassVector.size();
    case RABBIT:
        return rabbitVector.size();
    case WOLF:
        return wolfVector.size();
    case GRASS:
        return grassVector.size();
    }
    return -1;
}

int World::get_frame() {
    return frame;
}

int World::get_time() {
    return time;
}

int World::get_day() {
    return day;
}

int World::get_speed() {
    return speed;
}

void World::set_speed(int speed) {
    this->speed = speed;
}

World world;