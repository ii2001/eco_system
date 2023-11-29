#pragma once

#include "EcoSystem.h"

#define ZOOM_SPEED	0.1

enum ViewMode {
	GAME, INTERFACE
};

class Camera {
private:
	View view;
	Vector2f viewSize;

	View interface;

	//Animal* focusAnimal;
	//bool isFocusing;
public:
	Camera();
	~Camera();

	void update(sf::Event event);			//마우스 휠, 이동(x), 클릭(x) 등 구현 예정

	void setCenter(sf::Vector2f center);	//카메라 가운데 설정
	void setView(ViewMode mode);			//이걸 호출해줘야 현재 camera가 화면에 반영 됨, update 마지막에 호출

	//void setFocus(Animal a);
	//bool isVisible(Entity e);

	// 필요한거
	// void SetFocus(Animal) -> Focus 잡아주고 만약 focus 있으면 계속 카메라 중심 옮겨가기
	// bool isVisible(Entity) -> 아무거나 넣으면 카메라 범위 내에 보이는지 true/false
	// void update(sf::Event) -> 마우스에 대한 이벤트 전부 잡아서 왼클릭 -> focus,
	//							 우클릭 -> 잡고 카메라 이동, 휠 -> 보이는 범위 조정
	// 사실 update부분도 Controller class에서 하는게 맞는데..
};