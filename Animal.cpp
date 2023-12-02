#include "Animal.h"
#include "World.h"

Animal::Animal(Vector2f pos) {
    this->setPos(pos);
}

Animal::Animal(float x, float y) {
    this->setPos(x, y);
}

Animal::~Animal() {

}

bool Animal::move(int dt) {
    float delta_x = target.x - pos.x;
    float delta_y = target.y - pos.y;
    float vector_size = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    float speed = get_speed();

    if (vector_size < 10) {
        state = IDLE;
        return true;
    }
    else {
        pos.x += speed * dt * delta_x / vector_size / 1000;
        pos.y += speed * dt * delta_y / vector_size / 1000;
        return false;
    }
}

// 잠 자는 함수 정의
void Animal::sleep() {
    if (desire_for_sleep < 1) {
        state = MOVING;
    }
    // 잠을 자는 동작 구현
    // 여기에 잠 자는 모습 넣기
}

// moveTo 함수를 이용하여 동물을 특정 위치로 이동시키는 함수 추가
void Animal::moveTo(const Vector2f& targetPos) {
    /*// 이동 방향 설정
    float angle = std::atan2(targetPos.y - pos.y, targetPos.x - pos.x);
    vel.x = speed * std::cos(angle);
    vel.y = speed * std::sin(angle);

    // 동물의 위치 업데이트
    pos.x += vel.x;
    pos.y += vel.y;

    // 동물의 상태 업데이트
    hunger -= 1;

    // 이동한 위치가 풀의 위치인 경우, 풀을 먹음
    if (state == MOVING && hunger < 10) {
        eatGrass();
    }
    */
}

void Animal::draw_arr(char * arr, int width, int height) {
    int index;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) {
            index = i * width + j;
            if (arr[index] == '1')
            {
                sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                shape_r.setFillColor(sf::Color(0, 0, 0));
                shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                world.window->draw(shape_r);
            }
            else if (arr[index] == '2')
            {
                sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                shape_r.setFillColor(sf::Color(255, 255, 255));
                shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                world.window->draw(shape_r);
            }
            else if (arr[index] == '3')
            {
                sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                shape_r.setFillColor(sf::Color(255, 130, 255));
                shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                world.window->draw(shape_r);
            }
        }
    }
}

int Animal::get_state() {
    return state;
}
int Animal::get_hunger() {
    return hunger;
}


int Animal::get_dir() { return direction; }