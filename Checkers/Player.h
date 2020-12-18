#pragma once
#include "Config.h"
#include "StdAfx.h"
#include "Chess.h"

class Player
{
public:

	int getColor();
	char* getName();
	
	POINT getPoint();
	void setPoint(POINT point);


	BOOL checkColor(int color);

	BOOL getIsPressedChess();
	void setIsPressedChess(BOOL isPressedChess);

	Player();
	Player(int color, char* name, BOOL ii = false);
	~Player();
private:
	POINT point;
	int color;
	char* name;
	BOOL isPressedChess;
};

