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

	void handleEvent(sf::Event event);		//마우스 휠, 이동(x), 클릭(x) 등 구현 예정
	void update(int dt);					//focus 있으면 대상 따라 이동, 아니면 방향키 받아서 이동

	void setCenter(sf::Vector2f center);	//카메라 가운데 설정
	void setView(ViewMode mode);			//이걸 호출해줘야 현재 camera가 화면에 반영 됨, update 마지막에 호출

	void setFocus(Animal* a);				//a를 focus함
	void releaseFocus(Animal* a);			//a와 현재 focus 대상이 같으면 focus 해제
											//*** 이거 객체 삭제할때 계속 호출해줘야 함 ***

	Animal* getFocus();						//현재 focus 대상 return
	bool isVisiable(Entity e);				//entity가 카메라 상에 그려져야 하는지 true/false 반환
};