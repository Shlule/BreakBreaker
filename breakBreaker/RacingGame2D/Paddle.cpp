#include "Paddle.h"

Paddle::Paddle(float widthP, float heightP, Vector2 posP) : width{ widthP }, height{ heightP }, pos{ posP } {
	collisionBox = Rectangle{ pos.x, pos.y, width, height };
	center = { pos.x + width / 2, pos.y + height / 2 };
}
void Paddle::setSpeed(Vector2 speedP) {
	speed = speedP;
}
void Paddle::setPos(Vector2 posP) {
	pos = posP;
}

void Paddle::draw() {
	DrawRectangle(pos.x, pos.y, width, height, WHITE);
}

void Paddle::update() {
	collisionBox.x = pos.x;
	collisionBox.y = pos.y;
	center = { pos.x + width / 2, pos.y + height / 2 };
}

void Paddle::reverseSpeed(int CaseP) {

	switch (CaseP) {
	case 1:
		speed.x = -speed.x;
		break;

	case 2:
		speed.y = -speed.y;
		break;
	}

}
