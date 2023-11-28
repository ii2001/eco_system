#include "World.h"

World::World() {

}

World::~World() {
    int size = entityVector.size();
    for (int i = size - 1; i >= 0; i--) {
        delete entityVector[i];
        entityVector.pop_back();
    }
}

void World::update(int dt) {
    frame++;
    if (frame >= 25) {
        time += 1;
        frame = 0;
    }

    if (time >= 24) {
        day += 1;
        time = 0;
    }

    int size = entityVector.size();
    for (int i = 0; i < size; i++) {
        entityVector[i]->update(dt);
    }
}

void World::draw() {
    int size = entityVector.size();
    for (int i = 0; i < size; i++) {
        entityVector[i]->draw();
    }
}

void World::setWindow(RenderWindow* window) {
    this->window = window;
}

int World::add_entity(Entity* e) {
    entityVector.push_back(e);
    return entityVector.size() - 1;
}

int World::delete_entity(Entity* e) {
    int i = 0;
    for (auto iter = entityVector.begin(); iter != entityVector.end(); iter++, i++) {
        if (*iter == e) {
            entityVector.erase(iter);
            return i;
        }
    }
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

World world;