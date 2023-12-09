#include "World.h"
#include "Camera.h"
#include "Rabbit.h"

World::World()
    :day(0), time(0), frame(0), speed(1), isNight(0)
{
    filter = RectangleShape(sf::Vector2f(0.0, 0.0));
    filter.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    color = Color(0, 0, 0, 0);
    filter.setFillColor(color);
}

World::~World() {
    int size = rabbitVector.size();

    for (int i = size - 1; i >= 0; i--) {
        delete rabbitVector[i];
    }

    size = wolfVector.size();

    for (int i = size - 1; i >= 0; i--) {
        delete wolfVector[i];
    }

    size = grassVector.size();

    for (int i = size - 1; i >= 0; i--) {
        delete grassVector[i];
    }
    size = pondVector.size();

    for (int i = size - 1; i >= 0; i--) {
        delete pondVector[i];
    }
}

void World::update(int dt) {
    if (speed == 0)
        return;

    dt *= speed;
    time += dt;

    if (time >= 60000) {
        isNight = true;
    }
    if (time >= 100000) {
        isNight = false;
        day += 1;
        time = 0;
    }

    int size = grassVector.size();
    for (int i = 0; i < size; i++) {
        grassVector[i]->update(dt);
    }

    size = pondVector.size();
    for (int i = 0; i < size; i++) {
        pondVector[i]->update(dt);
    }

    size = rabbitVector.size();
    for (int i = 0; i < size; i++) {
        rabbitVector[i]->update(dt);
    }

    size = wolfVector.size();
    for (int i = 0; i < size; i++) {
        wolfVector[i]->update(dt);
    }

    size = rabbitVector.size();
    for (int i = 0; i < size;) {
        Rabbit* r = (Rabbit*)rabbitVector[i];
        if (r->is_deleting()) {
            delete r;
            size--;
        }
        else
            i++;
    }
}

void World::draw() {
    // draw Game Screen here
    camera.setView(GAME);

    int size = grassVector.size();
    for (int i = 0; i < size; i++) {
        drawEntity(grassVector[i]);
    }

    size = pondVector.size();
    for (int i = 0; i < size; i++) {
        drawEntity(pondVector[i]);
    }

    size = rabbitVector.size();
    for (int i = 0; i < size; i++) {
        drawEntity(rabbitVector[i]);
    }

    size = wolfVector.size();
    for (int i = 0; i < size; i++) {
        drawEntity(wolfVector[i]);
    }

    // draw Interface here (independent from game view)
    camera.setView(INTERFACE);

    if (isNight && color.a < 125) {
        color.a += speed;
        filter.setFillColor(color);
    }
    else if (!isNight && color.a > 0) {
        color.a -= speed;
        filter.setFillColor(color);
    }

    window->draw(filter);
}

void World::drawEntity(Entity* e) {
    if (camera.isVisiable(*e))
        e->draw();
}

void World::setWindow(RenderWindow* window) {
    this->window = window;
}

int World::add_entity(Entity* e, Type t) {
    switch (t) {
    case RABBIT: 
        rabbitVector.push_back((Rabbit*)e);
        return rabbitVector.size() - 1;
    case WOLF:
        wolfVector.push_back((Wolf*)e);
        return wolfVector.size() - 1;
    case GRASS:
        grassVector.push_back((grass*)e);
        return grassVector.size() - 1;
    case POND:
        pondVector.push_back((Pond*)e);
        return pondVector.size() - 1;
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
    case POND: return pondVector[index];
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
    case POND:
        return pondVector.size();
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