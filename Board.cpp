#include "Board.h"

const static unsigned int DEFAULT_BOARD_WIDTH = 16;
const static unsigned int DEFAULT_BOARD_HEIGHT = 16;
const static unsigned int DEFAULT_BOARD[DEFAULT_BOARD_HEIGHT][DEFAULT_BOARD_WIDTH] = {
	{ 9, 1, 5, 1, 3, 9, 1, 1, 3, 9, 1, 1, 1, 1, 1, 3 },
	{ 8, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 2 },
	{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 2,12, 0, 1, 0, 0, 2 },
	{ 8, 0, 0, 0, 0, 2,12, 0, 0, 0, 1, 0, 0, 0, 0, 6 },
	{12, 0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 4, 0, 0, 0, 3 },
	{ 9, 0, 0, 0, 3, 8, 0, 0, 0, 0, 0, 3, 8, 0, 4, 2 },
	{ 8, 6, 8, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 2, 9, 2 },
	{ 8, 1, 0, 0, 0, 0, 2,15,15,10,12, 0, 0, 0, 0, 2 },
	{ 8, 0, 0, 0, 0, 6,10,15,15, 8, 1, 0, 4, 0, 0, 2 },
	{ 8, 0, 4, 0, 0, 1, 0, 1, 1, 0, 0, 0, 3 ,8, 0, 6 },
	{ 8, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
	{12, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 2 },
	{ 9, 0, 0, 0, 4, 0, 0, 0, 2, 9, 0, 0, 0, 0, 0, 2 },
	{ 8, 0, 0, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 2,12, 2 },
	{ 8, 0, 0, 0, 0, 2,12, 0, 0, 0, 0, 6, 8, 0, 1, 2 },
	{12, 4, 4, 4, 6,12, 5, 4, 4, 4, 4, 5, 4, 6,12, 6 }
};

Board::Board (): _width (DEFAULT_BOARD_WIDTH), _height (DEFAULT_BOARD_HEIGHT) {
	_cells = new unsigned int *[_height];
	for (unsigned int y = 0; y < _height; y++) {
		_cells[y] = new unsigned int [_width];
		::memcpy (_cells[y], DEFAULT_BOARD[y], _width * sizeof (unsigned int));
	}

	_objectives << new Objective (Robot::WHITE, Objective::A, QPoint (11, 5))
				<< new Objective (Robot::RED, Objective::A, QPoint (2, 1))
				<< new Objective (Robot::RED, Objective::B, QPoint (4, 13))
				<< new Objective (Robot::RED, Objective::C, QPoint (12, 1))
				<< new Objective (Robot::RED, Objective::D, QPoint (9, 12))
				<< new Objective (Robot::BLUE, Objective::A, QPoint (6, 3))
				<< new Objective (Robot::BLUE, Objective::B, QPoint (2, 10))
				<< new Objective (Robot::BLUE, Objective::C, QPoint (10, 2))
				<< new Objective (Robot::BLUE, Objective::D, QPoint (12, 9))
				<< new Objective (Robot::GREEN, Objective::A, QPoint (1, 6))
				<< new Objective (Robot::GREEN, Objective::B, QPoint (6, 14))
				<< new Objective (Robot::GREEN, Objective::C, QPoint (14, 6))
				<< new Objective (Robot::GREEN, Objective::D, QPoint (14, 13))
				<< new Objective (Robot::YELLOW, Objective::A, QPoint (4, 5))
				<< new Objective (Robot::YELLOW, Objective::B, QPoint (5, 8))
				<< new Objective (Robot::YELLOW, Objective::C, QPoint (10, 7))
				<< new Objective (Robot::YELLOW, Objective::D, QPoint (11, 14));
}

Board::~Board () {
	for (unsigned int y = 0; y < _height; y++)
		delete[] _cells[y];
	delete _cells;
}

QSize Board::size () const {
	return QSize (_width, _height);
}

unsigned int Board::cell (QPoint position) const {
	return _cells[position.y ()][position.x ()];
}

const QList<const Objective *> &Board::objectives () const {
	return _objectives;
}
