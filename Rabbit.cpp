#include "Rabbit.h"
#include "World.h"

Rabbit::Rabbit(float x, float y) :Animal(x, y) {
    this->hunger = max_hunger;
    this->target_wolf = NULL;
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
    if (find_wolf()) {
        //set target
        Vector2f wolf_pos = target_wolf->getPos();
        Vector2f vector = Vector2f(wolf_pos.x - pos.x, wolf_pos.y - pos.y);
        target = pos - vector;
        check_dir();
        state = RUNNING_AWAY;
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

void Rabbit::eatGrass() {
    {
        // 현재 동물의 위치
        Vector2f animalPos = getPos();
        //풀들 중에서 가장 가까운거 찾기
        // 가장 가까운 풀의 위치
        Vector2f closestGrassPos;
        float closestDistance = std::numeric_limits<float>::max();  // 최대값으로 초기화
        // 풀을 찾아서 가장 가까운 풀의 위치를 찾음



        // 풀 포지션 배열값만 받아내면 오나성
        /*
        for (const Vector2f& grassPos : environment.getPositions()) {
            float distance = std::sqrt(std::pow(animalPos.x - grassPos.x, 2) + std::pow(animalPos.y - grassPos.y, 2));

            if (distance < closestDistance) {
                closestDistance = distance;
                closestGrassPos = grassPos;
            }
        }
        */

        // 찾은 풀로 이동
        // target을 찾은 풀로 설정

        // 풀에 도착하면 EATING 상태로 전환
        if (closestDistance < 1.0f) {
            state = EATING;
        }
        // 풀까지 이동 중인 경우, 상태를 MOVING으로 유지
        else {
            state = MOVING;
        }
        // 풀까지 좌표이동하면
        state == EATING;
        // 여기에 풀을 먹는 동작을 추가


        //world.window->display();
    }
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