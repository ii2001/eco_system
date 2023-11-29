#include "Animal.h"

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
		// cout << hunger;
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
			state == EATING;
			eatGrass();
		}
	}
}

void Animal::eatGrass() {
	{
		// 여기에 풀을 먹는 동작을 추가
		// 예시로 배경을 검정색으로 변화시키는 것으로 표현
		// std::cout << "Eating grass at (" << pos.x << ", " << pos.y << ")" << std::endl;

		// 예시: 토끼가 있던 배경 색을 검정색으로

		//**** 이 부분 디버그 오류 자꾸남 어려움 추가 수정 필요할듯

		world.window->display();
	}
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