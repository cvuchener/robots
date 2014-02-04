#include "Rules.h"

Rules::Rules () {
}

Rules::~Rules () {
}

QList<QPoint> Rules::validMoves (const Board &board, const Robots &robots, Robot::Color color) const {
	if (color == Robot::WHITE)
		return specialRobotMoves (board, robots, color);
	else
		return regularRobotMoves (board, robots, color);
}
