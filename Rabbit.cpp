#include "Rabbit.h"
#include "World.h"

Rabbit::Rabbit(float x, float y) :Animal(x, y) {
    this->hunger = max_hunger;
    this->thirst = max_thirst;
    this->target_wolf = NULL;
    this->target_grass = NULL;
    this->target_mate = NULL;
    
    this->type = RABBIT;
    this->die_timer = 0;
    this->state = IDLE;
};

void Rabbit::draw() {
    char* curr_arr = NULL;

    if (state == DIE) {
        draw_arr((char*)rabbit_die, 16, 19, 255 * (1 - die_timer / 5000.0));
        return;
    }

    check_dir();

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
    if (state == RUNNING_AWAY)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 4; j++) {
                if ((char)rabbit_exclam[i][j] == '4')
                {
                    sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                    shape_r.setFillColor(sf::Color(255, 0, 0));
                    shape_r.setPosition(pos.x + j * 3 - 6, pos.y + i * 3 - 40);
                    world.window->draw(shape_r);
                }
            }
        }
    }
    if (state == MATING) {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++) {
                if ((char)rabbit_love[i][j] == '1')
                {
                    sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                    shape_r.setFillColor(sf::Color(0, 0, 0));
                    shape_r.setPosition(pos.x + j * 3 - 6, pos.y + i * 3 - 40);
                    world.window->draw(shape_r);
                }
                else if ((char)rabbit_love[i][j] == '2')
                {
                    sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                    shape_r.setFillColor(sf::Color(255, 255, 255));
                    shape_r.setPosition(pos.x + j * 3 - 6, pos.y + i * 3 - 40);
                    world.window->draw(shape_r);
                }
                else if ((char)rabbit_love[i][j] == '4')
                {
                    sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                    shape_r.setFillColor(sf::Color(255, 0, 0));
                    shape_r.setPosition(pos.x + j * 3 - 6, pos.y + i * 3 - 40);
                    world.window->draw(shape_r);
                }
            }
        }
    }
}

void Rabbit::update(int dt) {
    if (state == DIE) {
        die_timer += dt;
        return;
    }
    if (state == IDLE) {
        if (world.get_time() > 70000) {
            state = SLEEP;
        }

        target_pond = NULL;
        target_grass = NULL;
        target_wolf = NULL;
        target_mate = NULL;
    }

    hunger -= dt;
    thirst -= dt;
    temp_mate += dt;

    if (find_wolf()) {
        //set target
        Vector2f wolf_pos = target_wolf->getPos();
        Vector2f vector = Vector2f(1.5*(wolf_pos.x - pos.x), 1.5*(wolf_pos.y - pos.y));
        target = pos - vector;
        state = RUNNING_AWAY;
    }
    else if (state == SLEEP) {
        if (world.get_time() <= 1000) {
            state = IDLE;
        }
    }
    else if (state == MATING) {
        //maintain state
        temp_mate -= dt;
    } 
    else if (state != RUNNING_AWAY) {
        if (thirst < 70000) {
            if (target_pond == NULL) {
                if (pond_fail) {
                    find_rand_pond();
                    pond_fail = true;
                    state = THIRSTY;
                }
                else {
                    find_pond();
                    pond_fail = true;
                    state = THIRSTY;
                }
                
            }
        }
        else if (hunger < 30000) {
            if (target_grass == NULL) {
                if (find_grass()) {
                    state = HUNGRY;
                }
            }
        }
        //first mate
        else if (temp_mate > 175000) {
            temp_mate = 0;
            if (find_mate()) {
                target_mate->mate_progress = 0;
                target_mate->temp_mate = 0;
                target_mate->state = MATING;
                target_mate->target_mate = this;
                target_mate->target = this->getPos();
                state = MATING;
                mate_progress = 0;
                target = target_mate->getPos();
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
            state = MOVING;
            break;
        }
    case MOVING:
        jump_frame += dt;
        if (jump_frame > 500) {
            jump_frame = 0;
            jump = !jump;
        }
        if (move(dt)) { 
            state = IDLE;
            jump = false; 
        }
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
    case THIRSTY:
        jump_frame += dt;
        if (jump_frame > 500) {
            jump_frame = 0;
            jump = !jump;
        }
        if (drink(dt)) {
            pond_fail = false;
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
        if (eatting(dt)) {
             state = IDLE;
             jump = false;
        }
        break;
    case MATING:
        if (mate(dt)) {
            // mate success
            if (world.get_entity_num(RABBIT)<20) {
                cout << "mate success" << endl;
                world.add_entity(new Rabbit(pos.x, pos.y), RABBIT);
            }
            else {
                if ((rand() % 100) < 50) {
                    cout << "mate success-" << endl;
                    world.add_entity(new Rabbit(pos.x, pos.y), RABBIT);
                }
                else {
                    cout << "mate fail" << endl;
                }
            }        
            target_mate->mate_progress = 0;
            target_mate->state = IDLE;
            target_mate->target_mate = NULL;
            target_mate = NULL;
            state = IDLE;
        }
    }
}

bool Rabbit::eatting(int dt) {
    if (target_grass == NULL) {
        return true;
    }
    if (move(dt)) {
        target_grass->minusCount();
        target_grass = NULL;
        hunger = max_hunger;
        return true;
    }
    else {
        target = target_grass->getPos();
        return false;
    }
}

bool Rabbit::mate(int dt) {
    if (move(dt)) {
        if (mate_progress > 3000) {
            mate_progress = 0;
            return true;
        }
        else if (mate_progress == 0) {
            direction = target_mate->get_dir();
            jump = false;
        }
        mate_progress += dt;
    }
    else {
        jump_frame += dt;
        if (jump_frame > 500) {
            jump_frame = 0;
            jump = !jump;
        }
        target = target_mate->getPos();
    }
    return false;
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

bool Rabbit::find_mate() {
    Rabbit* entity;
    float distance;
    for (int i = 0; i < world.get_entity_num(RABBIT); i++) {
        entity = (Rabbit *)world.get_entity(i, RABBIT);
        distance = this->distance(*entity);
        if ((distance < mate_detect_range) && (distance != 0) && entity->state != DIE) {
            if (entity->state != MATING) {
                target_mate = (Rabbit*)(entity);
                return true;
            }
        }
    }
    return false;
}

int Rabbit::get_type() {
    return RABBIT;
}

float Rabbit::get_speed() {
    return speed;
}

bool Rabbit::is_deleting() {
    return (die_timer >= 5000);
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


const char Rabbit::rabbit_die[19][16] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
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


const char Rabbit::rabbit_exclam[9][4] = { {'0', '4', '4', '0'},
{'0', '4', '4', '0'},
{'0', '4', '4', '0'},
{'0', '4', '4', '0'},
{'0', '4', '4', '0'},
{'0', '4', '4', '0'},
{'0', '0', '0', '0'},
{'0', '4', '4', '0'},
{'0', '4', '4', '0'} };

const char Rabbit::rabbit_love[6][7] = { 
    {'0', '1', '1', '0', '1', '1', '0'},
    {'1', '4', '4', '1', '4', '2', '1'},
    {'1', '4', '4', '4', '4', '4', '1'},
    {'0', '1', '4', '4', '4', '1', '0'},
    {'0', '0', '1', '4', '1', '0', '0'},
    {'0', '0', '0', '1', '0', '0', '0'},
 };