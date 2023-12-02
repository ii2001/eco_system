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
	void update(int dt);					//focus ������ ��� ���� �̵�, �ƴϸ� ����Ű �޾Ƽ� �̵�

	void setCenter(sf::Vector2f center);	//ī�޶� ��� ����
	void setView(ViewMode mode);			//�̰� ȣ������� ���� camera�� ȭ�鿡 �ݿ� ��, update �������� ȣ��

	void setFocus(Animal* a);				//a�� focus��
	void releaseFocus(Animal* a);			//a�� ���� focus ����� ������ focus ����
											//*** �̰� ��ü �����Ҷ� ��� ȣ������� �� ***

	Animal* getFocus();						//���� focus ��� return
	bool isVisiable(Entity e);				//entity�� ī�޶� �� �׷����� �ϴ��� true/false ��ȯ
};