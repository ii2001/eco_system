#pragma once

#include <SFML/Graphics.hpp>
#include "World.h"

#define ZOOM_SPEED	0.1

class Camera {
private:
	sf::View view;
	//Animal* focusAnimal;
	//bool isFocusing;
	sf::Vector2f viewSize;
public:
	Camera();
	~Camera();

	void update(sf::Event event);			//���콺 ��, �̵�(x), Ŭ��(x) �� ���� ����

	void setCenter(sf::Vector2f center);	//ī�޶� ��� ����
	void setView();							//�̰� ȣ������� ���� camera�� ȭ�鿡 �ݿ� ��, update �������� ȣ��

	//void setFocus(Animal a);
	//bool isVisible(Entity e);

	// �ʿ��Ѱ�
	// void SetFocus(Animal) -> Focus ����ְ� ���� focus ������ ��� ī�޶� �߽� �Űܰ���
	// bool isVisible(Entity) -> �ƹ��ų� ������ ī�޶� ���� ���� ���̴��� true/false
	// void update(sf::Event) -> ���콺�� ���� �̺�Ʈ ���� ��Ƽ� ��Ŭ�� -> focus,
	//							 ��Ŭ�� -> ��� ī�޶� �̵�, �� -> ���̴� ���� ����
	// ��� update�κе� Controller class���� �ϴ°� �´µ�..
};