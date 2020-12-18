#include "Player.h"

Player::Player()
{
	this->point.x = 0;
	this->point.y = 0;
	this->color = NONE;
	this->name = NULL;
	this->isPressedChess = FALSE;
}

Player::Player(int color, char* name, BOOL ii) : name(new char[strlen(name) + 1]) {
	this->point.x = 0;
	this->point.y = 0;
	this->color = color;
	strcpy_s(this->name, strlen(name) + 1, name);
	this->isPressedChess = FALSE;
}

Player::~Player()
{
	delete[] name;
}

POINT Player::getPoint() {
	return this->point;
}
void Player::setPoint(POINT point) {
	this->point = point;
}

int Player::getColor() {
	return this->color;
}

char* Player::getName() {
	return this->name;
}

BOOL Player::checkColor(int color) {
	if (this->color == color) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL Player::getIsPressedChess() {
	return this->isPressedChess;
}
void Player::setIsPressedChess(BOOL isPressedChess) {
	this->isPressedChess = isPressedChess;
}

