#pragma once

#include "EcoSystem.h"

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class Entity {
protected:
	int type;
	Vector2f pos;
	Vector2f size;
	FloatRect rect;

public:
	Entity();
	Entity(Vector2f pos);		// Vector2f로 생성
	Entity(float x, float y);	// x, y로 생성
	~Entity();

	virtual void update(int dt);		// dt = deltatime = 지난 시간
	virtual void draw();

	void setPos(Vector2f pos);
	void setPos(float x, float y);

	Vector2f getPos();
	Vector2f center();
	FloatRect getRect();

	float distance(Entity& entity);
	virtual int get_type() { return type; };
};