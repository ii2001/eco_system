#include "Rabbit.h"
#include "World.h"

Rabbit::Rabbit(float x, float y) :Animal(x, y) {
    this->hunger = max_hunger;
    this->target_wolf = NULL;
    this->target_grass = NULL;
};

void Rabbit::draw() {
    char* curr_arr = NULL;
    if (direction == RIGHT) // move right
    {
        if (!jump) // jump x
            curr_arr = (char*)(rabbit_right);
        else // jump 0
            curr_arr = (char*)(rabbit_right_jump);
    }
    else if (direction == LEFT) // move left
    {
        if (!jump) // jump x
            curr_arr = (char*)(rabbit_left);
        else // jump 0
            curr_arr = (char*)(rabbit_left_jump);
    }
    else if (direction == TOP) // move top
    {
        if (!jump) // jump x
            curr_arr = (char*)(rabbit_front);
        else // jump 0
            curr_arr = (char*)(rabbit_front_jump);
    }
    else if (direction == DOWN)// move down
    {
        if (!jump) // jump x
            curr_arr = (char*)(rabbit_back);
        else // jump 0
            curr_arr = (char*)(rabbit_back_jump);
    }
    if (curr_arr != NULL) {
        draw_arr(curr_arr, 16, 19);
    }
}

void Rabbit::update(int dt) {
    hunger -= dt;
    /*if (hunger < 0) {
        world.delete_entity(this, RABBIT);
        cout << "dead";
    }*/
    if (find_wolf()) {
        //set target
        Vector2f wolf_pos = target_wolf->getPos();
        Vector2f vector = Vector2f(wolf_pos.x - pos.x, wolf_pos.y - pos.y);
        target = pos - vector;
        check_dir();
        state = RUNNING_AWAY;
    }

    else if (hunger < 3000) {
        if (target_grass == NULL) {
            if (find_grass()) {
                state = HUNGRY;
            }
        }
    }
    
    switch (state) {
    case IDLE:
        temp += dt;
        if (temp >= 2000) {
            //set random target
            temp = 0;
            target = Vector2f(pos.x + rand() % 400 - 200, pos.y + rand() % 400 - 200);
            check_dir();
            state = MOVING;
            break;
        }
    case MOVING:
        jump_frame += dt;
        if (jump_frame > 500) {
            jump_frame = 0;
            jump = !jump;
        }
        if (move(dt)) { jump = false; }
        break;
    case RUNNING_AWAY:
        jump_frame += dt;
        if (jump_frame > 500) {
            jump_frame = 0;
            jump = !jump;
        }
        if (move(dt * run_mult)) {
            state = IDLE;
            jump = false;
        }
        break;
    case HUNGRY:
        jump_frame += dt;
        if (jump_frame > 500) {
            jump_frame = 0;
            jump = !jump;
        }
        if (eatting(dt*run_mult)) {
             state = IDLE;
             jump = false;
        }
        break;
    }
}

bool Rabbit::eatting(int dt) {
    float distance = this->distance(*target_grass);
    target = target_grass->getPos();
    if (distance > 600) { move(dt); }
    else { move(dt * walk_mult); }

    if (distance > 10) {
        target = target_grass->getPos();
        move(dt * run_mult);
        return false;
    }
    else {
        world.delete_entity(target_grass, GRASS);
        target_grass = NULL;
        hunger += 10000;
        return true;
    }
}

bool Rabbit::find_wolf() {
    Entity* entity;
    for (int i = 0; i < world.get_entity_num(WOLF); i++) {
        entity = world.get_entity(i, WOLF);
        if (this->distance(*entity) < detect_range) {
            target_wolf = (Animal*)(entity);
            return true;
        }
    }
    return false;
}

bool Rabbit::find_grass() {
    Entity* entity;
    for (int i = 0; i < world.get_entity_num(GRASS); i++) {
        entity = world.get_entity(i, GRASS);
        if (this->distance(*entity) < detect_range) {
            target_grass = (grass*)(entity);
            return true;
        }
    }
    return false;
}

void Rabbit::check_dir() {
    float theta = atan2(target.y - pos.y, target.x - pos.x) * 180 / PI;
    if ((theta <= 45) && (theta >= -45)) {
        direction = RIGHT;
    } else if ((theta >= 45) && (theta <= 135)) {
        direction = TOP;
    } else if ((theta >= 135) || (theta <= -135)) {
        direction = LEFT;
    } else if ((theta <= -45) && (theta >= -135)) {
        direction = DOWN;
    }
}

int Rabbit::get_type() {
    return RABBIT;
}

float Rabbit::get_speed() {
    return speed;
}

const char Rabbit::rabbit_left[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '1', '2', '1', '2', '1', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '1', '3', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '1', '3', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '1', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '1', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0', '0', '0', '0', '0'},
    {'0', '1', '2', '2', '1', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0'},
    {'0', '1', '3', '2', '1', '2', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0'},
    {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '2', '1', '0'},
    {'0', '0', '1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1', '0'},
    {'0', '0', '0', '0', '1', '2', '2', '2', '2', '1', '1', '2', '2', '2', '1', '0'},
    {'0', '0', '0', '1', '2', '2', '1', '1', '1', '2', '2', '2', '2', '2', '1', '0'},
    {'0', '0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };


const char Rabbit::rabbit_left_jump[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '2', '1', '2', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '8', '1', '8', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '8', '3', '8', '3', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '1', '2', '2', '2', '2', '3', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'1', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0', '0', '0', '0', '0', '0'},
{'1', '2', '2', '1', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0'},
{'1', '8', '2', '1', '2', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0', '0'},
{'1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '2', '1', '0', '0'},
{'0', '1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1', '0', '0'},
{'0', '0', '0', '1', '2', '2', '2', '2', '1', '1', '2', '2', '2', '1', '0', '0'},
{'0', '0', '0', '1', '2', '2', '1', '1', '0', '0', '1', '2', '2', '2', '1', '0'},
{'0', '0', '0', '1', '2', '1', '0', '0', '0', '0', '0', '1', '1', '2', '2', '1'},
{'0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };


const char Rabbit::rabbit_right[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '1', '2', '1', '2', '1', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '1', '3', '1', '3', '1', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '1', '3', '1', '3', '1', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '1', '2', '2', '2', '2', '1', '0', '0'},
{'0', '0', '0', '0', '0', '1', '1', '1', '2', '2', '2', '2', '2', '2', '1', '0'},
{'0', '0', '0', '0', '1', '2', '2', '2', '2', '2', '2', '1', '2', '2', '1', '0'},
{'0', '1', '1', '1', '2', '2', '2', '2', '2', '2', '2', '1', '2', '3', '1', '0'},
{'0', '1', '2', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
{'0', '1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1', '0', '0'},
{'0', '1', '2', '2', '2', '1', '1', '2', '2', '2', '2', '1', '0', '0', '0', '0'},
{'0', '1', '2', '2', '2', '2', '2', '1', '1', '1', '2', '2', '1', '0', '0', '0'},
{'0', '1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };


const char Rabbit::rabbit_right_jump[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '2', '1', '2', '1', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '3', '1', '3', '1', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '3', '1', '3', '1', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '2', '2', '2', '2', '1', '0'},
{'0', '0', '0', '0', '0', '0', '1', '1', '1', '2', '2', '2', '2', '2', '2', '1'},
{'0', '0', '0', '0', '0', '1', '2', '2', '2', '2', '2', '2', '1', '2', '2', '1'},
{'0', '0', '1', '1', '1', '2', '2', '2', '2', '2', '2', '2', '1', '2', '3', '1'},
{'0', '0', '1', '2', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1'},
{'0', '0', '1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1', '0'},
{'0', '0', '1', '2', '2', '2', '1', '1', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '1', '2', '2', '2', '1', '0', '0', '1', '1', '2', '2', '1', '0', '0', '0'},
{'1', '2', '2', '1', '1', '0', '0', '0', '0', '0', '1', '2', '1', '0', '0', '0'},
{'1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };


const char Rabbit::rabbit_back[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0'},
{'0', '0', '1', '2', '1', '0', '0', '0', '0', '0', '1', '2', '1', '0', '0', '0'},
{'0', '0', '1', '3', '2', '1', '0', '0', '0', '1', '2', '3', '1', '0', '0', '0'},
{'0', '0', '0', '1', '3', '2', '1', '1', '1', '2', '3', '1', '0', '0', '0', '0'},
{'0', '0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0'},
{'0', '0', '1', '2', '2', '1', '2', '2', '2', '1', '2', '2', '1', '0', '0', '0'},
{'0', '0', '0', '1', '1', '1', '2', '2', '2', '1', '1', '1', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };


const char Rabbit::rabbit_back_jump[19][16] = { {'0', '0', '1', '1', '0', '0', '1', '0', '1', '0', '0', '1', '1', '0', '0', '0'},
{'0', '0', '1', '2', '1', '1', '2', '1', '2', '1', '1', '2', '1', '0', '0', '0'},
{'0', '0', '1', '3', '2', '1', '2', '1', '2', '1', '2', '3', '1', '0', '0', '0'},
{'0', '0', '0', '1', '3', '2', '1', '1', '1', '2', '3', '1', '0', '0', '0', '0'},
{'0', '0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '1', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0', '0', '0'},
{'0', '0', '1', '2', '1', '2', '2', '2', '2', '2', '1', '2', '1', '0', '0', '0'},
{'0', '0', '1', '1', '2', '1', '2', '2', '2', '1', '2', '1', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
{'0', '0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '1', '1', '1', '1', '1', '2', '1', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '1', '0', '0', '0', '1', '2', '1', '0', '0', '0', '0'},
{'0', '0', '1', '2', '2', '1', '0', '0', '0', '1', '2', '2', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '1', '0', '0', '0', '1', '2', '2', '1', '0', '0', '0'},
{'0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0'} };


const char Rabbit::rabbit_front[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0'},
{'0', '1', '2', '1', '0', '0', '0', '1', '2', '1', '0', '0', '0', '0', '0', '0'},
{'0', '1', '3', '2', '1', '0', '1', '2', '3', '1', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '3', '1', '0', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '2', '2', '1', '2', '2', '1', '0', '0', '0', '0', '0', '0', '0'},
{'0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0', '0'},
{'0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0', '0', '0'},
{'0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0', '0', '0'},
{'0', '1', '2', '2', '2', '3', '2', '2', '2', '1', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0'},
{'0', '0', '1', '1', '2', '2', '2', '2', '1', '1', '1', '2', '2', '1', '0', '0'},
{'0', '1', '2', '1', '2', '2', '2', '2', '1', '2', '1', '2', '2', '1', '0', '0'},
{'0', '1', '2', '1', '2', '2', '2', '2', '1', '2', '2', '1', '1', '0', '0', '0'},
{'0', '1', '2', '1', '2', '1', '2', '2', '1', '2', '2', '1', '0', '0', '0', '0'},
{'0', '1', '1', '2', '2', '1', '2', '2', '1', '2', '2', '1', '0', '0', '0', '0'},
{'0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };


const char Rabbit::rabbit_front_jump[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '1', '2', '1', '1', '1', '2', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0'},
{'0', '0', '0', '1', '3', '2', '1', '2', '1', '2', '3', '1', '0', '0', '0', '0'},
{'0', '0', '0', '0', '1', '3', '1', '1', '1', '3', '1', '0', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0'},
{'0', '0', '0', '1', '2', '2', '2', '3', '2', '2', '2', '1', '0', '0', '0', '0'},
{'0', '0', '0', '1', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0', '0', '0'},
{'0', '0', '1', '2', '1', '1', '1', '1', '1', '1', '1', '2', '1', '0', '0', '0'},
{'0', '0', '1', '2', '2', '1', '0', '0', '0', '1', '2', '2', '1', '0', '0', '0'},
{'0', '0', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };


const static char rabbit_die[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '1', '2', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '0'},
{'0', '0', '1', '3', '2', '1', '0', '0', '0', '0', '1', '1', '3', '2', '1', '0'},
{'0', '0', '0', '1', '3', '1', '0', '0', '4', '4', '2', '3', '2', '1', '0', '0'},
{'0', '0', '0', '1', '4', '4', '4', '4', '4', '4', '1', '1', '1', '0', '0', '0'},
{'0', '0', '0', '4', '4', '4', '4', '4', '4', '4', '4', '0', '0', '0', '0', '0'},
{'0', '0', '0', '4', '4', '4', '4', '4', '4', '4', '4', '4', '0', '0', '0', '0'},
{'0', '0', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '0', '0', '0'},
{'0', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '0', '0', '4', '0'},
{'4', '0', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '0', '0', '0', '0'},
{'0', '0', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '0', '0', '0'},
{'0', '0', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '0', '0', '0', '0'},
{'0', '0', '0', '4', '4', '4', '4', '4', '4', '4', '4', '4', '4', '0', '0', '0'},
{'0', '0', '0', '0', '4', '0', '4', '4', '0', '0', '4', '0', '0', '0', '0', '0'},
{'0', '0', '0', '4', '0', '4', '0', '0', '4', '0', '0', '4', '0', '0', '4', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0'},
{'0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };
