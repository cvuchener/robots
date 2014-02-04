#include "Rules.h"

Rules::Rules () {
}

Rules::~Rules () {
}

QList<QPoint> Rules::validMoves (const Board &board, const Robots &robots, RobotColor color) const {
	if (color == Robot::Color::WHITE)
		return specialRobotMoves (board, robots, color);
	else
		return regularRobotMoves (board, robots, color);
}
