#include "Chess.h"



Chess::Chess() {
	this->isChess = FALSE;
	this->isQueen = FALSE;
	this->isSelected = FALSE;
	this->isShine = FALSE;
	this->strikeOnThis = FALSE;
	this->color = NONE;
}

Chess::Chess(POINT point) {
	this->point = point;
	this->isChess = FALSE;
	this->isQueen = FALSE;
	this->isSelected = FALSE;
	this->isShine = FALSE;
	this->strikeOnThis = FALSE;
	this->color = NONE;
}


Chess::~Chess() {

}

BOOL Chess::isMoveLeftBottom() {
	if ((this->point.x < 7) && (this->point.y > 0)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isMoveRightBottom() {
	if ((this->point.x < 7) && (this->point.y < 7)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isMoveLeftTop() {
	if ((this->point.x > 0) && (this->point.y > 0)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isMoveRightTop() {
	if ((this->point.x > 0) && (this->point.y < 7)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isStrikeLeftBottom() {
	if ((this->point.x < 6) && (this->point.y > 1)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isStrikeRightBottom() {
	if ((this->point.x < 6) && (this->point.y < 6)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isStrikeLeftTop() {
	if ((this->point.x > 1) && (this->point.y > 1)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isStrikeRightTop() {
	if ((this->point.x > 1) && (this->point.y < 6)) {
		return TRUE;
	}
	return FALSE;
}

POINT Chess::getPoint() {
	return this->point;
}

void Chess::setColor(int color) {
	this->color = color;
}
int Chess::getColor() {
	return this->color;
}
BOOL Chess::checkColor(int color) {
	if (this->color == color) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void Chess::setIsChess(BOOL isChess) {
	this->isChess = isChess;
}
BOOL Chess::getIsChess() {
	return this->isChess;
}

void Chess::setIsQueen(BOOL isQueen) {
	this->isQueen = isQueen;
}

BOOL Chess::getIsQueen() {
	return this->isQueen;
}

void Chess::setIsSelected(BOOL isSelected) {
	this->isSelected = isSelected;
}

BOOL Chess::getIsSelected() {
	return this->isSelected;
}

void Chess::setIsShine(BOOL isShine) {
	this->isShine = isShine;
}

BOOL Chess::getIsShine() {
	return this->isShine;
}

void Chess::setStrikeOnThis(BOOL strikeOnThis) {
	this->strikeOnThis = strikeOnThis;
}

BOOL Chess::getStrikeOnThis() {
	return this->strikeOnThis;
}

void Chess::setChess(BOOL chess, int color) {
	this->setIsChess(chess);
	this->setColor(color);
	this->setIsQueen(FALSE);
	this->setIsSelected(FALSE);
	this->setIsShine(FALSE);
	this->setStrikeOnThis(FALSE);
}
