#include "Animal.h"
#include <cmath>

Animal::Animal(Vector2f pos) {
    this->setPos(pos);
}

Animal::Animal(float x, float y) {
	this->setPos(x, y);
}

Animal::~Animal() {

}

void Animal::update(int dt) {
	if (rand() % 100 <= temp) {
		//change state
		if (state == IDLE) {
			change_dir();
			state = MOVING;
		}
		else {
			state = IDLE;
		}
	}
	else {
		temp++;
		switch (state)
		{
		case IDLE:
			jump = false;
			break;
		case MOVING:
			move();
			break;
        case SLEEP:
            sleep();
            break;
		default:
			break;
		}
	}
}

void Animal::move() {
	{
		pos.x += vel.x;
		pos.y += vel.y;
		hunger -= 1;
        desire_for_sleep += 1;
        if (desire_for_sleep > 100) {
            state = SLEEP;
        }

		if (jump == false && jump_frame > 5)
		{
			jump = true;
			jump_frame = 0;
		}
		else if (jump == true && jump_frame > 10)
		{
			jump = false;
			jump_frame = 0;
		}
		jump_frame++;

		if (state == MOVING && hunger < 10) {
			eatGrass();
		}
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

void Animal::eatGrass() {
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
        moveTo(closestGrassPos);

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
void Animal::change_dir() {
	direction = rand() % 360;
	temp = 0;
	vel.y = speed * sin(direction * PI / 180);
	vel.x = speed * cos(direction * PI / 180);
	jump = false;
	jump_frame = 0;
}
void Animal::draw() {
    {
        char rabbit_move[13][14] = {
            {'0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '3', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '0', '1', '3', '1', '3', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'0', '1', '2', '2', '2', '2', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'1', '2', '2', '2', '2', '2', '2', '1', '1', '1', '0', '0', '0', '0'},
            {'1', '2', '2', '1', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'1', '3', '2', '1', '2', '2', '2', '2', '2', '2', '2', '1', '1', '1'},
            {'1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '2', '1'},
            {'0', '1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '1', '1', '2', '2', '2', '1'},
            {'0', '0', '1', '2', '2', '1', '1', '1', '2', '2', '2', '2', '2', '1'},
            {'0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1'} };


        char rabbit_jump[14][16] = {
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
            {'0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1'} };


        char rabbit_back[16][13] = {
            {'0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0'},
            {'0', '1', '2', '1', '0', '0', '0', '0', '0', '1', '2', '1', '0'},
            {'0', '1', '3', '2', '1', '0', '0', '0', '1', '2', '3', '1', '0'},
            {'0', '0', '1', '3', '2', '1', '1', '1', '2', '3', '1', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0'},
            {'0', '1', '2', '2', '1', '2', '2', '2', '1', '2', '2', '1', '0'},
            {'0', '0', '1', '1', '1', '2', '2', '2', '1', '1', '1', '0', '0'},
            {'0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '0', '0', '0'} };


        char rabbit_back_jump[19][13] = {
            {'0', '1', '1', '0', '0', '1', '0', '1', '0', '0', '1', '1', '0'},
            {'0', '1', '2', '1', '1', '2', '1', '2', '1', '1', '2', '1', '0'},
            {'0', '1', '3', '2', '1', '2', '1', '2', '1', '2', '3', '1', '0'},
            {'0', '0', '1', '3', '2', '1', '1', '1', '2', '3', '1', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '1', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0'},
            {'0', '1', '2', '1', '2', '2', '2', '2', '2', '1', '2', '1', '0'},
            {'0', '1', '1', '2', '1', '2', '2', '2', '1', '2', '1', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '0'},
            {'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '1', '1', '1', '1', '1', '2', '1', '0', '0'},
            {'0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0'},
            {'0', '1', '0', '0', '1', '0', '0', '0', '1', '0', '0', '1', '0'},
            {'0', '1', '0', '0', '1', '0', '0', '0', '1', '0', '0', '1', '0'},
            {'0', '0', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0'} };


        char rabbit_front[17][13] = {
            {'1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0'},
            {'1', '2', '1', '0', '0', '0', '1', '2', '1', '0', '0', '0', '0'},
            {'1', '3', '2', '1', '0', '1', '2', '3', '1', '0', '0', '0', '0'},
            {'0', '1', '3', '1', '0', '1', '3', '1', '0', '0', '0', '0', '0'},
            {'0', '1', '2', '2', '1', '2', '2', '1', '0', '0', '0', '0', '0'},
            {'1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0', '0', '0'},
            {'1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0'},
            {'1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0', '0', '0'},
            {'1', '2', '2', '2', '3', '2', '2', '2', '1', '0', '0', '0', '0'},
            {'0', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0', '0', '0'},
            {'0', '0', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '0'},
            {'0', '1', '1', '2', '2', '2', '2', '1', '1', '1', '2', '2', '1'},
            {'1', '2', '1', '2', '2', '2', '2', '1', '2', '1', '2', '2', '1'},
            {'1', '2', '1', '2', '2', '2', '2', '1', '2', '2', '1', '1', '0'},
            {'1', '2', '1', '2', '1', '2', '2', '1', '2', '2', '1', '0', '0'},
            {'1', '1', '2', '2', '1', '2', '2', '1', '2', '2', '1', '0', '0'},
            {'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0'} };


        char rabbit_front_jump[14][13] = {
            {'0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '2', '1', '1', '1', '2', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '2', '2', '2', '2', '2', '1', '0', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '0', '1', '3', '2', '1', '2', '1', '2', '3', '1', '0', '0'},
            {'0', '0', '0', '1', '3', '1', '1', '1', '3', '1', '0', '0', '0'},
            {'0', '0', '1', '2', '2', '2', '2', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '1', '2', '2', '2', '1', '2', '1', '0', '0'},
            {'0', '0', '1', '2', '2', '2', '3', '2', '2', '2', '1', '0', '0'},
            {'0', '0', '1', '1', '2', '2', '2', '2', '2', '1', '1', '0', '0'},
            {'0', '1', '2', '1', '1', '1', '1', '1', '1', '1', '2', '1', '0'},
            {'0', '1', '2', '2', '1', '0', '0', '0', '1', '2', '2', '1', '0'},
            {'0', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0'} };


        if ((direction < 45) || (direction > 315)) // ������
        {
            if (!jump) // ���� x
            {
                for (int i = 0; i < 13; i++)
                {
                    for (int j = 0; j < 14; j++) {
                        if (rabbit_move[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(pos.x + 39 - j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_move[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(pos.x + 39 - j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_move[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(pos.x + 39 - j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                    }
                }
            }
            else // ���� 0
            {
                for (int i = 0; i < 14; i++)
                {
                    for (int j = 0; j < 16; j++) {
                        if (rabbit_jump[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(pos.x + 45 - j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_jump[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(pos.x + 45 - j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_jump[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(pos.x + 45 - j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                    }
                }
            }
        }
        else if ((direction >= 135) && (direction <= 225)) // ����
        {
            if (!jump) // ���� x
            {
                for (int i = 0; i < 13; i++)
                {
                    for (int j = 0; j < 14; j++) {
                        if (rabbit_move[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_move[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_move[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                    }
                }
            }
            else // ���� 0
            {
                for (int i = 0; i < 14; i++)
                {
                    for (int j = 0; j < 16; j++) {
                        if (rabbit_jump[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_jump[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_jump[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                    }
                }
            }
        }
        else if ((direction >= 225) && (direction <= 315)) // ����
        {
            if (!jump) // ���� x
            {
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j < 13; j++) {
                        if (rabbit_back[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_back[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_back[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                    }
                }
            }
            else // ���� 0
            {
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j < 13; j++) {
                        if (rabbit_back_jump[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_back_jump[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_back_jump[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                    }
                }
            }
        }
        else if ((direction >= 45) && (direction <= 135)) // �Ʒ���
        {
            if (!jump) // ���� x
            {
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 13; j++) {
                        if (rabbit_front[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_front[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_front[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                    }
                }
            }
            else // ���� 0
            {
                for (int i = 0; i < 14; i++)
                {
                    for (int j = 0; j < 13; j++) {
                        if (rabbit_front_jump[i][j] == '1')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(0, 0, 0));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_front_jump[i][j] == '2')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 255, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                        else if (rabbit_front_jump[i][j] == '3')
                        {
                            sf::RectangleShape shape_r(sf::Vector2f(3, 3));
                            shape_r.setFillColor(sf::Color(255, 130, 255));
                            shape_r.setPosition(pos.x + j * 3, pos.y + i * 3);
                            world.window->draw(shape_r);
                        }
                    }
                }
            }
        }
    }
}

void Animal::print_status() {
	printf("vel_x : %f\n", vel.x);
	printf("vel_y : %f\n", vel.y);
}

int Animal::get_state() {
    return state;
}

int Animal::get_hunger() {
    return hunger;
}

Wolf::Wolf(float x, float y) : Animal(x, y) {
    this->hunger = max_hunger;
}

void Wolf::move() {
    target = Vector2f(0.0, 0.0);
    float delta_x = target.x - pos.x;
    float delta_y = target.y - pos.y;
    float vector_size = sqrt(pow(delta_x, 2) + pow(delta_y, 2));

    pos.x += speed * delta_x / vector_size;
    pos.y += speed * delta_y / vector_size;
}

bool Wolf::find_rabbit() {
    return true;
}

void Wolf::draw() {
    sf::RectangleShape shape_r(sf::Vector2f(60, 60));
    shape_r.setFillColor(sf::Color(0, 0, 0));
    shape_r.setPosition(pos.x, pos.y);
    world.window->draw(shape_r);
}

void  Wolf::update(int dt) {
    
    //change state
    if (hunger < 1000) {
        state = HUNGRY;
    }
    else {
        hunger -= dt;
    }

    //do thing

    switch (state) {
    case IDLE:
        temp += dt;
        if (temp >= 4000) {
            //set random target
            temp = 0;
            target = Vector2f(pos.x + rand() % 100, pos.y + rand() % 100);
            state = MOVING;
        }
        break;
    case HUNGRY:
        if (find_rabbit()) {
            state = HUNTING;
        }
        break;
    case MOVING:
        move();
        break;
    
    }
}