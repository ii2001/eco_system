#include "Entity.h"
#include "Camera.h"
#include "World.h"

Entity::Entity() {
	//world vector에 추가해야 함
	pos = Vector2f(0, 0);
	size = Vector2f(40, 40);
	rect = FloatRect(pos, size);
	type = ENTITY;
}

Entity::Entity(Vector2f pos) {
	pos = pos;
	size = Vector2f(0, 0);
	rect = FloatRect(pos, size);
	type = ENTITY;
}

Entity::Entity(float x, float y) {
	pos = Vector2f(x, y);
	size = Vector2f(0, 0);
	rect = FloatRect(pos, size);
	type = ENTITY;
}

Entity::~Entity() {
	//world vector에서 삭제 필요
	if (camera.getFocus() == this)
		camera.releaseFocus();
	world.delete_entity(this, (Type)type);
}

void Entity::update(int dt) {

}

void Entity::draw() {

}

void Entity::setPos(Vector2f pos) {
	this->pos = pos;
}

void Entity::setPos(float x, float y) {
	this->pos.x = x;
	this->pos.y = y;
}

Vector2f Entity::getPos() {
	return pos;
}

Vector2f Entity::center() {
	Vector2f center = pos;
	center.x += size.x;
	center.y += size.y;
	return center;
}

FloatRect Entity::getRect() {
	FloatRect r(pos.x - rect.width / 2, pos.y - rect.height / 2, rect.width, rect.height);

	//cout << "Rect : " << pos.x << " " << pos.y << " " << rect.width << " " << rect.height << endl;

	return r;
}

float Entity::distance(Entity& entity) {
	return sqrt(pow(pos.x - entity.getPos().x, 2) + pow(pos.y - entity.getPos().y, 2));
}