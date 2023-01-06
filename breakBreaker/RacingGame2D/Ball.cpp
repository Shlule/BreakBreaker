#include "Ball.h"

Ball::Ball(float widthP, float heightP, Vector2 posP) : width{ widthP }, height{ heightP }, pos{ posP } {
	collisionBox = Rectangle{ pos.x, pos.y, width, height };
	center = { pos.x + width / 2, pos.y  };
}
void Ball::setSpeed (Vector2 speedP) {
	speed = speedP;
}
void Ball::setPos(Vector2 posP) {
	pos = posP;
}

void Ball::draw() {
	DrawRectangle(pos.x, pos.y, width, height, WHITE);
}

void Ball::update() {

	pos.x += speed.x;
	pos.y += speed.y;
	collisionBox.x = pos.x;
	collisionBox.y = pos.y;
	center.x += speed.x;
	center.y += speed.y;
}

void Ball::reverseSpeed(int CaseP) {

	switch (CaseP) {
	case 1:
		speed.x = -speed.x;
		break;

	case 2:
		speed.y = -speed.y;
		break;
	}

}