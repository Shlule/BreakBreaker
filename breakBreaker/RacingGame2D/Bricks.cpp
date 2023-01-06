#include "Bricks.h"
Bricks::Bricks(float widthP, float heightP, Vector2 posP) : width{ widthP }, height{ heightP }, pos{ posP } {
	collisionBox = Rectangle{ pos.x, pos.y, width, height };
	center = { pos.x + width / 2, pos.y + height / 2 };
}
void Bricks::setPos(Vector2 posP) {
	pos = posP;
}
void Bricks::setIsDead(bool isDeadP) {
	isDead = isDeadP;
}

void Bricks::load() {

}
void Bricks::draw() {
	if (isDead) {
		DrawRectangle(pos.x, pos.y, width, height, BLACK);
	}
	else {
		DrawRectangle(pos.x, pos.y, width, height, BLUE);
	}
	
}
void Bricks::update() {
	collisionBox.x = pos.x;
	collisionBox.y = pos.y;
	center = { pos.x + width / 2, pos.y + height / 2 };
}
