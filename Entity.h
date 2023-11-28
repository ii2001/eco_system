#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {
protected:
	Vector2f pos;
	Vector2f size;
	FloatRect rect;

public:
	Entity();
	Entity(Vector2f pos);		// Vector2f�� ����
	Entity(float x, float y);	// x, y�� ����
	~Entity();

	virtual void update(int dt);		// dt = deltatime = ���� �ð�
	virtual void draw();

	void setPos(Vector2f pos);
	void setPos(float x, float y);

	Vector2f getPos();
	Vector2f center();
	FloatRect getRect();
};