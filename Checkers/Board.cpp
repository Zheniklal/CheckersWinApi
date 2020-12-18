#include "Board.h"



Board::Board()
{
	canNotSelectAnother = FALSE;
	POINT point;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			point.x = i;
			point.y = j;
			this->boardChess[i][j] = new Chess(point);
		}
	}
}


Board::~Board()
{
	if (this->boardChess != NULL) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				delete this->boardChess[i][j];
				this->boardChess[i][j] = nullptr;
				delete this->boardChess[i][j];
			}
		}
	}
}

BOOL Board::getCanNotSelectAnother() {
	return this->canNotSelectAnother;
}

void Board::setCanNotSelectAnother(BOOL canNotSelectAnother) {
	this->canNotSelectAnother = canNotSelectAnother;
}

BOOL Board::getIsChess(POINT point) {
	return this->boardChess[point.x][point.y]->getIsChess();
}

BOOL Board::checkColor(int color, POINT point) {
	return this->boardChess[point.x][point.y]->checkColor(color);
}

void Board::setIsShine(BOOL isShine, POINT point) {
	if (this->boardChess[point.x][point.y]->getIsChess()) {
		this->boardChess[point.x][point.y]->setIsShine(isShine);
	}
}
BOOL Board::getIsShine(POINT point) {
	return this->boardChess[point.x][point.y]->getIsShine();
}

BOOL Board::getIsQueen(POINT point) {
	return this->boardChess[point.x][point.y]->getIsQueen();
}

BOOL Board::getStrikeOnThis(POINT point) {
	return this->boardChess[point.x][point.y]->getStrikeOnThis();
}

BOOL Board::isMove(POINT point) {
	Chess * chess = this->boardChess[point.x][point.y];
	BOOL result = FALSE;
	if (chess->getIsQueen()) {
		if (this->isMoveLeftTop(*chess)) {
			result = TRUE;
		}
		if (this->isMoveRightTop(*chess)) {
			result = TRUE;
		}
		if (this->isMoveLeftBottom(*chess)) {
			result = TRUE;
		}
		if (this->isMoveRightBottom(*chess)) {
			result = TRUE;
		}
	}
	else {
		if (chess->getColor() == WH) {
			if (this->isMoveLeftTop(*chess)) {
				result = TRUE;
			}
			if (this->isMoveRightTop(*chess)) {
				result = TRUE;
			}
		}
		else if (chess->getColor() == BL) {
			if (this->isMoveLeftBottom(*chess)) {
				result = TRUE;
			}
			if (this->isMoveRightBottom(*chess)) {
				result = TRUE;
			}
		}
	}
	return result;
}

BOOL Board::isStrike(POINT point) {
	int x = point.x;
	int y = point.y;
	Chess * chess = this->boardChess[x][y];
	BOOL result = FALSE;
		if (this->isStrikeLeftBottom(*chess)) {
			result = TRUE;
		}
		if (this->isStrikeLeftTop(*chess)) {
			result = TRUE;
		}
		if (this->isStrikeRightBottom(*chess)) {
			result = TRUE;
		}
		if (this->isStrikeRightTop(*chess)) {
			result = TRUE;
		}
	return result;
}

BOOL Board::isCheckStrike(int color) {
	POINT point;
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			if (this->boardChess[i][j]->getIsChess() && this->boardChess[i][j]->checkColor(color)) {
				point.x = i;
				point.y = j;
				if ((this->isStrike(point))) {
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void Board::initializationBoard() {
	int color = 2;
	BOOL chess = FALSE;
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			if ((i % 2) ^ (j % 2)) {
				if (i < 3) {
					chess = TRUE;
					color = BL;
				}
				else if (i >= 3 && i <= 4) {
					chess = FALSE;
					color = NONE;
				}
				else if (i > 4) {
					chess = TRUE;
					color = WH;
				}
				this->boardChess[i][j]->setChess(chess, color);
			}
		}
	}
}

BOOL Board::isMoveLeftBottom(Chess chess) {
	POINT point = chess.getPoint();
	if ((chess.isMoveLeftBottom()) && (!(*this->boardChess[point.x + 1][point.y - 1]).getIsChess())) {
		(*this->boardChess[point.x + 1][point.y - 1]).setStrikeOnThis(TRUE);
		if (chess.getIsQueen()) {
			for (int i = 2; i < 8; i++)
			{
				if (((point.x + i < 8) && (point.y - i >= 0)) && !(*this->boardChess[point.x + i][point.y - i]).getIsChess()) {
					(*this->boardChess[point.x + i][point.y - i]).setStrikeOnThis(TRUE);
				}
				else {
					break;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL Board::isMoveRightBottom(Chess chess) {
	POINT point = chess.getPoint();
	if ((chess.isMoveRightBottom()) && (!(*this->boardChess[point.x + 1][point.y + 1]).getIsChess())) {
		(*this->boardChess[point.x + 1][point.y + 1]).setStrikeOnThis(TRUE);
		if (chess.getIsQueen()) {
			for (int i = 2; i < 8; i++)
			{
				if (((point.x + i < 8) && (point.y + i < 8)) && !(*this->boardChess[point.x + i][point.y + i]).getIsChess()) {
					(*this->boardChess[point.x + i][point.y + i]).setStrikeOnThis(TRUE);
				}
				else {
					break;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL Board::isMoveLeftTop(Chess chess) {
	POINT point = chess.getPoint();
	if ((chess.isMoveLeftTop()) && (!(*this->boardChess[point.x - 1][point.y - 1]).getIsChess())) {
		(*this->boardChess[point.x - 1][point.y - 1]).setStrikeOnThis(TRUE);
		if (chess.getIsQueen()) {
			for (int i = 2; i < 8; i++)
			{
				if (((point.x - i >= 0) && (point.y - i >= 0)) && !(*this->boardChess[point.x - i][point.y - i]).getIsChess()) {
					(*this->boardChess[point.x - i][point.y - i]).setStrikeOnThis(TRUE);
				}
				else {
					break;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL Board::isMoveRightTop(Chess chess) {
	POINT point = chess.getPoint();
	if ((chess.isMoveRightTop()) && (!(*this->boardChess[point.x - 1][point.y + 1]).getIsChess())) {
		(*this->boardChess[point.x - 1][point.y + 1]).setStrikeOnThis(TRUE);
		if (chess.getIsQueen()) {
			for (int i = 2; i < 8; i++)
			{
				if (((point.x - i >= 0) && (point.y + i < 8)) && !(*this->boardChess[point.x - i][point.y + i]).getIsChess()) {
					(*this->boardChess[point.x - i][point.y + i]).setStrikeOnThis(TRUE);
				}
				else {
					break;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL Board::isStrikeLeftBottom(Chess chess) {
	POINT point = chess.getPoint();
	if (chess.isStrikeLeftBottom()) {
		if (chess.getIsQueen()) {
			for (int i = 1; i < 7; i++)
			{
				if (((point.x + i < 7) && (point.y - i > 0)) && ((*this->boardChess[point.x + i][point.y - i]).getIsChess())) {
					if ((!chess.checkColor(this->boardChess[point.x + i][point.y - i]->getColor())) && (!(*this->boardChess[point.x + i + 1][point.y - i - 1]).getIsChess())) {
						for (int j = i + 1; j < 8; j++)
						{
							if (((point.x + j < 8) && (point.y - j >= 0)) && !(*this->boardChess[point.x + j][point.y - j]).getIsChess()) {
								(*this->boardChess[point.x + j][point.y - j]).setStrikeOnThis(TRUE);
							}
							else {
								break;
							}
						}
						return TRUE;
					}
					break;
				}
			}
		}
		else {
			if (((*this->boardChess[point.x + 1][point.y - 1]).getIsChess()) && (!chess.checkColor(this->boardChess[point.x + 1][point.y - 1]->getColor())) && (!(*this->boardChess[point.x + 2][point.y - 2]).getIsChess())) {
				(*this->boardChess[point.x + 2][point.y - 2]).setStrikeOnThis(TRUE);
				return TRUE;
			}
		}
		
	}
	return FALSE;
}

BOOL Board::isStrikeRightBottom(Chess chess) {
	POINT point = chess.getPoint();
	if (chess.isStrikeRightBottom()) {
		if (chess.getIsQueen()) {
			for (int i = 1; i < 7; i++)
			{
				if (((point.x + i < 7) && (point.y + i < 7)) && ((*this->boardChess[point.x + i][point.y + i]).getIsChess())) {
					if ((!chess.checkColor(this->boardChess[point.x + i][point.y + i]->getColor())) && (!(*this->boardChess[point.x + i + 1][point.y + i + 1]).getIsChess())) {
						for (int j = i + 1; j < 8; j++)
						{
							if (((point.x + j < 8) && (point.y + j < 8)) && !(*this->boardChess[point.x + j][point.y + j]).getIsChess()) {
								(*this->boardChess[point.x + j][point.y + j]).setStrikeOnThis(TRUE);
							}
							else {
								break;
							}
						}
						return TRUE;
					}
					break;
				}
			}
		}
		else {
			if (((*this->boardChess[point.x + 1][point.y + 1]).getIsChess()) && (chess.getColor() != this->boardChess[point.x + 1][point.y + 1]->getColor()) && (!(*this->boardChess[point.x + 2][point.y + 2]).getIsChess())) {
				(*this->boardChess[point.x + 2][point.y + 2]).setStrikeOnThis(TRUE);
				return TRUE;
			}
		}

	}
	return FALSE;
}

BOOL Board::isStrikeLeftTop(Chess chess) {
	POINT point = chess.getPoint();
	if (chess.isStrikeLeftTop()) {
		if (chess.getIsQueen()) {
			for (int i = 1; i < 7; i++)
			{
				if (((point.x - i > 0) && (point.y - i > 0)) && ((*this->boardChess[point.x - i][point.y - i]).getIsChess())) {
					if ((!chess.checkColor(this->boardChess[point.x - i][point.y - i]->getColor())) && (!(*this->boardChess[point.x - i - 1][point.y - i - 1]).getIsChess())) {
						for (int j = i + 1; j < 8; j++)
						{
							if (((point.x - j >= 0) && (point.y - j >= 0)) && !(*this->boardChess[point.x - j][point.y - j]).getIsChess()) {
								(*this->boardChess[point.x - j][point.y - j]).setStrikeOnThis(TRUE);
							}
							else {
								break;
							}
						}
						return TRUE;
					}
					break;
				}
			}
		}
		else {
			if (((*this->boardChess[point.x - 1][point.y - 1]).getIsChess()) && (chess.getColor() != this->boardChess[point.x - 1][point.y - 1]->getColor()) && (!(*this->boardChess[point.x - 2][point.y - 2]).getIsChess())) {
				(*this->boardChess[point.x - 2][point.y - 2]).setStrikeOnThis(TRUE);
				return TRUE;
			}
		}

	}
	return FALSE;
}

BOOL Board::isStrikeRightTop(Chess chess) {
	POINT point = chess.getPoint();
	if (chess.isStrikeRightTop()) {
		if (chess.getIsQueen()) {
			for (int i = 1; i < 7; i++)
			{
				if (((point.x - i > 0) && (point.y + i < 7)) && ((*this->boardChess[point.x - i][point.y + i]).getIsChess())) {
					if ((!chess.checkColor(this->boardChess[point.x - i][point.y + i]->getColor())) && (!(*this->boardChess[point.x - i - 1][point.y + i + 1]).getIsChess())) {
						for (int j = i + 1; j < 8; j++)
						{
							if (((point.x - j >= 0) && (point.y + j < 8)) && !(*this->boardChess[point.x - j][point.y + j]).getIsChess()) {
								(*this->boardChess[point.x - j][point.y + j]).setStrikeOnThis(TRUE);
							}
							else {
								break;
							}
						}
						return TRUE;
					}
					break;
				}
			}
		}
		else {
			if (((*this->boardChess[point.x - 1][point.y + 1]).getIsChess()) && (chess.getColor() != this->boardChess[point.x - 1][point.y + 1]->getColor()) && (!(*this->boardChess[point.x - 2][point.y + 2]).getIsChess())) {
				(*this->boardChess[point.x - 2][point.y + 2]).setStrikeOnThis(TRUE);
				return TRUE;
			}
		}

	}
	return FALSE;
}

BOOL Board::isMoveFromTo(POINT pointFrom, POINT pointTo) {

	if (this->boardChess[pointTo.x][pointTo.y]->getStrikeOnThis()) {
		this->moveChess(pointFrom, pointTo);
		return TRUE;
	}
	return FALSE;
}


void Board::moveChess(POINT pointFrom, POINT pointTo) {
	Chess * chessFrom = this->boardChess[pointFrom.x][pointFrom.y];
	Chess * chessTo = this->boardChess[pointTo.x][pointTo.y];
	int color = chessFrom->getColor();
	BOOL isChess = chessFrom->getIsChess();
	BOOL isQueen = chessFrom->getIsQueen();

	chessFrom->setColor(chessTo->getColor());
	chessFrom->setIsChess(chessTo->getIsChess());
	chessFrom->setIsQueen(chessTo->getIsQueen());
	chessFrom->setIsShine(chessTo->getIsShine());

	chessTo->setColor(color);
	chessTo->setIsChess(isChess);
	if (((pointTo.x == 0) && (chessTo->checkColor(WH))) || ((pointTo.x == 7) && (chessTo->checkColor(BL)))) {
		chessTo->setIsQueen(TRUE);
	}
	else {
		chessTo->setIsQueen(isQueen);
	}
	chessTo->setIsShine(FALSE);

	int xI = -(pointFrom.x - pointTo.x) / abs(pointFrom.x - pointTo.x);
	int yI = -(pointFrom.y - pointTo.y) / abs(pointFrom.y - pointTo.y);
	int count = abs(pointFrom.x - pointTo.x);
	for (int i = 1; i < count; i++) {
		this->boardChess[pointFrom.x + i * xI][pointFrom.y + i * yI]->setChess();
	}
}

void Board::initializationMoves() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->boardChess[i][j]->setStrikeOnThis(FALSE);
		}
	}
}
