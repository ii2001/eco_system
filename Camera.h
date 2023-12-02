#pragma once

#include "EcoSystem.h"
#include "Animal.h"

#define ZOOM_SPEED	0.1

enum ViewMode {
	GAME, INTERFACE
};

class Camera {
private:
	View view;
	Vector2f viewSize;

	View interface;

	Animal* focusAnimal;
	bool isFocusing;

	Animal* getClickedAnimal(Vector2f pos);
public:
	Camera();
	~Camera();

	void handleEvent(sf::Event event);		//���콺 ��, �̵�(x), Ŭ��(x) �� ���� ����
	void update(int dt);

	void setCenter(sf::Vector2f center);	//ī�޶� ��� ����
	void setView(ViewMode mode);			//�̰� ȣ������� ���� camera�� ȭ�鿡 �ݿ� ��, update �������� ȣ��

	void setFocus(Animal* a);
	void releaseFocus(Animal* a);
	Animal* getFocus();
	bool isVisiable(Entity e);

	// �ʿ��Ѱ�
	// void SetFocus(Animal) -> Focus ����ְ� ���� focus ������ ��� ī�޶� �߽� �Űܰ���
	// bool isVisible(Entity) -> �ƹ��ų� ������ ī�޶� ���� ���� ���̴��� true/false
	// void update(sf::Event) -> ���콺�� ���� �̺�Ʈ ���� ��Ƽ� ��Ŭ�� -> focus,
	//							 ��Ŭ�� -> ��� ī�޶� �̵�, �� -> ���̴� ���� ����
	// ��� update�κе� Controller class���� �ϴ°� �´µ�..
};