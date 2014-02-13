#include "PathFinder.h"

#include <QTime>
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

	QTime search_time;
	_tested_path_count = 0;

	qDebug () << "Search started";
	search_time.start ();
	search_rec (0, INT_MAX, path);
	qDebug () << "Search ended (time = " << search_time.elapsed ()/1000.0 << ", path tested = " << _tested_path_count << ")";
}

unsigned int PathFinder::search_rec (unsigned int cost, unsigned int max_cost, QList<QPair<RobotColor, QPoint>> &path) {
	if (_canceled || cost+1 >= max_cost || path.count () >= _max_length)
		return max_cost;

	foreach (RobotColor color, _color_list) {
		QList<QPoint> moves = _rules->validMoves (_board, _robots, color);
		Robot *robot = _robots[color];
		QPoint pos = robot->position();
		foreach (QPoint move, moves) {
			// Analyze previous moves to decide if the new move is useful
			{
				QList<QPair<RobotColor, QPoint>>::const_iterator it = path.constEnd ();
				QList<QPair<RobotColor, QPoint>>::const_iterator previous_move;
				bool found_last_move = false;
				bool found_previous_pos = false;
				QPoint previous_pos;
				while (it != path.constBegin ()) {
					it--;
					if (it->first == color) {
						if (found_last_move) {
							found_previous_pos = true;
							previous_pos = it->second;
							break;
						}
						else {
							previous_move = it;
							found_last_move = true;
						}
					}
				}
				if (found_previous_pos) {
					QPoint last_move = pos - previous_pos;
					QPoint current_move = move - pos;
					if (last_move.x () * current_move.y () - last_move.y () * current_move.x () == 0) { // Current and last moves are along the same axe
						bool found_intersecting_move = false; // Search for an intersecting move from another robot after the last move from the current robot
						for (it = previous_move; it != path.constEnd (); it++) {
							if (it->first != color) {
								QPoint v = it->second - pos;
								if (v.x () * last_move.y () - v.y () * last_move.x () == 0) {
									found_intersecting_move = true;
									break;
								}
							}
						}
						if (!found_intersecting_move)
							continue;	// Skip the current move
					}
				}
			}

			path.append (QPair<RobotColor, QPoint> (color, move));
			robot->move (move);

			// count tested paths for debug
			_tested_path_count++;

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
