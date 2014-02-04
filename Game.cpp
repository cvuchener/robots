#include "Game.h"

Game::Game (const Rules *rules):
		_robots (QList<QPoint> () << QPoint (0, 0)
								  << QPoint (1, 1)
								  << QPoint (2, 2)
								  << QPoint (3, 3)
								  << QPoint (4, 4)),
		_rules (rules) {
}

Game::~Game () {
}

const Board &Game::board () const {
	return _board;
}

const Robots &Game::robots () const {
	return _robots;
}

const Robot &Game::robot (Robot::Color color) const {
	return *_robots[color];
}

const Rules *Game::rules () const {
	return _rules;
}

QList<QPoint> Game::validMoves (Robot::Color color) const {
	return _rules->validMoves (_board, _robots, color);
}

bool Game::move (Robot::Color color, QPoint position) {
	if (true) {
		Robot *robot = _robots[color];
		robot->move (position);
		emit robotMoved (robot);
		return true;
	}
	return false;
}
