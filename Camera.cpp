#include "camera.h"
#include "World.h"

Camera::Camera() //:isFocusing(false), focusAnimal(NULL), viewSize(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	view = View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	interface = View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}

Camera::~Camera() {

}

void Camera::update(sf::Event event) {
	/*if (isFocusing) {
		view.setCenter(focusAnimal.center());
	}*/

	if (event.type == sf::Event::MouseWheelScrolled)
	{
		float zoom_size = 1 - event.mouseWheelScroll.delta * ZOOM_SPEED;
		view.zoom(zoom_size);
		viewSize.x *= zoom_size;
		viewSize.y *= zoom_size;
	}
}

void Camera::setCenter(sf::Vector2f center)
{
	view.setCenter(center);
}

void Camera::setView(ViewMode mode)
{
	if (mode == GAME)
		world.window->setView(view);
	else if (mode == INTERFACE)
		world.window->setView(interface);
}

//void Camera::setFocus(Animal* a) {
//	this->focusAnimal = a;
//	this->isFocusing = true;
//}

//bool Camera::isVisiable(Entity e) {
//	//View center, size�� Entit center, size ����ؼ� �ȿ� �ִ��� �˻�
//	//rect �浹 �˻�� �ϸ� ���� ����
//  //intersect ������ �� ���� ����
//}