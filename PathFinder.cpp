#include "PathFinder.h"

#include <QDebug>

PathFinder::PathFinder (const Rules *rules, const Board &board, const Robots &robots, const Objective *objective, int max_length):
		_canceled (false), _max_length (max_length), _rules (rules), _board (board), _robots (robots), _objective (objective) {
}

PathFinder::~PathFinder () {
}

void PathFinder::cancel () {
	_canceled = true;
}

void PathFinder::run () {
	QList<QPair<RobotColor, QPoint>> path;
	_color_list = Robot::COLORS;
	if (_objective->color () != Robot::Color::WHITE) {
		_color_list.removeOne (_objective->color ());
		_color_list.prepend (_objective->color ());
	}
	qDebug () << "Search started";
	search_rec (0, INT_MAX, path);
	qDebug () << "Search ended";
}

unsigned int PathFinder::search_rec (unsigned int cost, unsigned int max_cost, QList<QPair<RobotColor, QPoint>> &path) {
	if (_canceled || cost+1 >= max_cost || path.count () >= _max_length)
		return max_cost;

	foreach (RobotColor color, _color_list) {
		QList<QPoint> moves = _rules->validMoves (_board, _robots, color);
		Robot *robot = _robots[color];
		QPoint pos = robot->position();
		foreach (QPoint move, moves) {
			path.append (QPair<RobotColor, QPoint> (color, move));
			robot->move (move);

			if (_objective->position () == move && _objective->accept (_robots[color])) {
				emit pathFound (cost+1, path);
				qDebug () << QString("Found path with cost %1").arg (cost+1);

				path.removeLast ();
				robot->move (pos);
				return cost+1;
			}
			else
				max_cost = search_rec (cost+1, max_cost, path);

			path.removeLast ();
			robot->move (pos);
		}
	}

	return max_cost;
}
