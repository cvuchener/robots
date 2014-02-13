#include "Game.h"

#include <QDebug>

Game::Game (const Rules *rules):
		_state (PREPARATION),
		_robots (QList<QPoint> () << QPoint (0, 0)
								  << QPoint (1, 1)
								  << QPoint (2, 2)
								  << QPoint (3, 3)
								  << QPoint (4, 4)),
		_saved (_robots),
		_rules (rules),
		_remaining_target (_board.targets()) {
	_timer.setSingleShot (true);
	_timer.setInterval (60000);
	connect (&_timer, SIGNAL (timeout ()), this, SLOT (onSearchTimeout ()));
	connect (this, SIGNAL (stateChanged (Game::State)), this, SLOT (onStateChanged (Game::State)));
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
	switch (_state) {
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
	Robot *robot = _robots[color];
	if (_state == PREPARATION ||
			(_state == MOVING && _rules->validMoves (_board, _robots, color).contains (position))) {
		robot->move (position);
		emit robotMoved (robot);
		if (_state == MOVING) {
			_move_counter++;
			emit moveCounterUpdated (_move_counter);
			if (position == _current_target->position ())
				setState (SEARCH);
			else if (_move_counter >= _move_count_stack.top ()) {
				giveup ();
				return false;
			}
		}
		return true;
	}
	return false;
}

void Game::saveRobots () {
	_saved = _robots;
}

void Game::restoreRobots () {
	_robots = _saved;
	foreach (RobotColor color, Robot::COLORS)
		emit robotMoved (_robots[color]);
}

void Game::endPreparation () {
	if (_state == PREPARATION)
		setState (SEARCH);
}

void Game::stateMoveCount (unsigned int count) {
	if (_state != SEARCH && _state != TIMED_SEARCH)
		return;

	if (!_move_count_stack.empty() && count >= _move_count_stack.top())
		return;

	_move_count_stack.push (count);
	if (_state != TIMED_SEARCH)
		setState (TIMED_SEARCH);
}

void Game::setSearchTimeout (int msec) {
	_timer.setInterval (msec);
}

void Game::onSearchTimeout () {
	setState (MOVING);
}

void Game::onStateChanged (State state) {
	qDebug () << "State changed: " << state;
	switch (state) {
	case SEARCH:
		_current_target = _remaining_target.at (qrand () % _remaining_target.count ());
		_remaining_target.removeOne (_current_target);
		_move_count_stack.clear ();
		emit newTarget (_current_target);
		break;

	case TIMED_SEARCH:
		_timer.start ();
		break;

	case MOVING:
		saveRobots();
		_move_counter = 0;
		emit moveCounterUpdated (_move_counter);
		break;

	default:
		break;
	}
}

void Game::setState (State state) {
	_state = state;
	emit stateChanged (state);
}

void Game::giveup () {
	if (_state == MOVING) {
		_move_count_stack.pop ();
		restoreRobots ();
		setState (MOVING);
	}
}
