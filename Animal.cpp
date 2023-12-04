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

// �� �ڴ� �Լ� ����
void Animal::sleep() {
    if (desire_for_sleep < 1) {
        state = MOVING;
    }
    // ���� �ڴ� ���� ����
    // ���⿡ �� �ڴ� ��� �ֱ�
}

// moveTo �Լ��� �̿��Ͽ� ������ Ư�� ��ġ�� �̵���Ű�� �Լ� �߰�
bool Animal::moveTo(int dt, const Vector2f& targetPos) {
    float delta_x = targetPos.x - pos.x;
    float delta_y = targetPos.y - pos.y;
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

void Animal::draw_arr(char* arr, int width, int height) {
    int index;
    int width_check = (width * 3) / 2;
    int height_check = (height * 3) / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) {
            index = i * width + j;
            if (arr[index] == '1')
            {
                sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                shape_r.setFillColor(sf::Color(0, 0, 0));
                shape_r.setPosition(pos.x + j * 3 - width_check, pos.y + i * 3 - height_check);
                world.window->draw(shape_r);
            }
            else if (arr[index] == '2')
            {
                sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                shape_r.setFillColor(sf::Color(255, 255, 255));
                shape_r.setPosition(pos.x + j * 3 - width_check, pos.y + i * 3 - height_check);
                world.window->draw(shape_r);
            }
            else if (arr[index] == '3')
            {
                sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                shape_r.setFillColor(sf::Color(255, 130, 255));
                shape_r.setPosition(pos.x + j * 3 - width_check, pos.y + i * 3 - height_check);
                world.window->draw(shape_r);
            }
            else if (arr[index] == '4')
            {
                sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                shape_r.setFillColor(sf::Color(255, 30, 30));
                shape_r.setPosition(pos.x + j * 3 - width_check, pos.y + i * 3 - height_check);
                world.window->draw(shape_r);
            }
            else if (arr[index] == '5')
            {
                sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                shape_r.setFillColor(sf::Color(50, 68, 68));
                shape_r.setPosition(pos.x + j * 3 - width_check, pos.y + i * 3 - height_check);
                world.window->draw(shape_r);
                //
            }
        }
    }
}

void Animal::check_dir() {
    float theta = atan2(target.y - pos.y, target.x - pos.x) * 180 / PI;
    if ((theta <= 45) && (theta >= -45)) {
        direction = RIGHT;
    }
    else if ((theta >= 45) && (theta <= 135)) {
        direction = TOP;
    }
    else if ((theta >= 135) || (theta <= -135)) {
        direction = LEFT;
    }
    else if ((theta <= -45) && (theta >= -135)) {
        direction = DOWN;
    }
}

int Animal::get_state() {
    return state;
}
int Animal::get_hunger() {
    return hunger;
}

int Animal::get_thirsty() {
    return thirst;
}


int Animal::get_dir() { return direction; }