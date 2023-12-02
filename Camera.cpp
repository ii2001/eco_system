#include "Camera.h"
#include "World.h"

Camera::Camera()
	:isFocusing(false), focusAnimal(NULL), viewSize(WINDOW_WIDTH, WINDOW_HEIGHT) {
	view = View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	interface = View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}

Camera::~Camera() {

}

void Camera::handleEvent(sf::Event event) {
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		float zoom_size = 1 - event.mouseWheelScroll.delta * ZOOM_SPEED;
		view.zoom(zoom_size);
		viewSize.x *= zoom_size;
		viewSize.y *= zoom_size;
	}

	if (Mouse::isButtonPressed(sf::Mouse::Left))
	{
		(*world.window).setView(view);

		Vector2i mousePos = Mouse::getPosition(*world.window);

		Vector2f worldPos = (*world.window).mapPixelToCoords(mousePos);

		//cout << "Mouse WorldPos (x, y): (" << worldPos.x << ", " << worldPos.y << ")\n";

		setFocus(getClickedAnimal(worldPos));
	}

	if (Keyboard::isKeyPressed(Keyboard::F)) {
		releaseFocus(focusAnimal);
	}
}

void Camera::update(int dt) {
	if (isFocusing) {
		view.setCenter((*focusAnimal).center());
	}

	else {
		Vector2f center = view.getCenter();

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			center.y -= dt;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			center.y += dt;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			center.x -= dt;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			center.x += dt;
		}

		setCenter(center);
	}
}

void Camera::setCenter(sf::Vector2f center)
{
	view.setCenter(center);
}

void Camera::setView(ViewMode mode) {
	if (mode == GAME)
		world.window->setView(view);
	else if (mode == INTERFACE)
		world.window->setView(interface);
}

void Camera::setFocus(Animal* a) {
	if (a == NULL)
		return;

	this->focusAnimal = a;
	this->isFocusing = true;
}

void Camera::releaseFocus(Animal* a) {
	if (focusAnimal == a) {
		this->focusAnimal = NULL;
		this->isFocusing = false;
	}
}

Animal* Camera::getFocus() {
	if (isFocusing)
		return focusAnimal;
	return NULL;
}

bool Camera::isVisiable(Entity e) {
	FloatRect rect = FloatRect(view.getCenter().x - viewSize.x / 2, view.getCenter().y - viewSize.y / 2, \
		viewSize.x, viewSize.y);

	return rect.intersects(e.getRect());
}

Animal* Camera::getClickedAnimal(Vector2f pos) {
	for (int i = 0; i < world.get_entity_num(WOLF); i++) {
		if (world.get_entity(i, WOLF)->getRect().contains(pos)) {
			return (Animal*)world.get_entity(i, WOLF);
		}
	}

	for (int i = 0; i < world.get_entity_num(RABBIT); i++) {
		if (world.get_entity(i, RABBIT)->getRect().contains(pos)) {
			return (Animal*)world.get_entity(i, RABBIT);
		}
	}

	return NULL;
}

Camera camera;