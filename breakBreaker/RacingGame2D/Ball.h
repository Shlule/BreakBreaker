#pragma once
#include "raylib.h"

class Ball {
public:

	Ball(float widthP, float heightP, Vector2 posP);

	Vector2 getPos() const { return pos; }
	Vector2 getSpeed() const { return speed; }
	float getWidth() const { return width; }
	float getHeight() const { return height; }
	Vector2 getCenter() const { return center; }
	Rectangle getCollisionBox() const{ return collisionBox; }

	void setPos(const Vector2 posP);
	void setSpeed(const Vector2 speedP);

	void reverseSpeed(int caseP);
	
	void Load();
	void draw();
	void update();

	

private:

	Rectangle collisionBox;
	Vector2 center;
	float width{ 120.0 };
	float height{ 15.0 };
	Vector2 pos{ 100.0,800.0 };
	Vector2 speed{ 5,5 };

};

