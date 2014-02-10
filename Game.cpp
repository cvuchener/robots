#include "Game.h"

Game::Game (const Rules *rules):
		_mode (PREPARATION),
		_robots (QList<QPoint> () << QPoint (0, 0)
								  << QPoint (1, 1)
								  << QPoint (2, 2)
								  << QPoint (3, 3)
								  << QPoint (4, 4)),
		_saved (_robots),
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

const Robot &Game::robot (RobotColor color) const {
	return *_robots[color];
}

const Rules *Game::rules () const {
	return _rules;
}

QList<QPoint> Game::validMoves (RobotColor color) const {
	QList<QPoint> moves;
	switch (_mode) {
	case PREPARATION:
		for (int x = 0; x < _board.size().width(); x++)
			for (int y = 0; y < _board.size().height(); y++)
				moves << QPoint (x, y);
		foreach (RobotColor color, Robot::COLORS)
			moves.removeAll (_robots[color]->position ());
		return moves;

	case MOVING:
		return _rules->validMoves (_board, _robots, color);

	default:
		return moves;
	}

}

bool Game::move (RobotColor color, QPoint position) {
	if (true) {
		Robot *robot = _robots[color];
		robot->move (position);
		emit robotMoved (robot);
		return true;
	}
	return false;
}

void Game::setGameMode (Mode mode) {
	_mode = mode;
}

void Game::saveRobots () {
	_saved = _robots;
}

void Game::restoreRobots () {
	_robots = _saved;
	foreach (RobotColor color, Robot::COLORS)
		emit robotMoved (_robots[color]);
}
