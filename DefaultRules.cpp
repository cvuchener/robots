#include "DefaultRules.h"

#include <QMap>

DefaultRules::DefaultRules () {
}

DefaultRules::~DefaultRules () {
}

QList<QPoint> DefaultRules::regularRobotMoves (const Board &board, const Robots &robots, RobotColor color) const {
	QMap<Board::Wall, QPoint> dirs;
	dirs.insert (Board::NORTH, QPoint (0, -1));
	dirs.insert (Board::EAST, QPoint (+1, 0));
	dirs.insert (Board::SOUTH, QPoint (0, +1));
	dirs.insert (Board::WEST, QPoint (-1, 0));

	const Robot *robot = robots[color];
	QPoint pos = robot->position ();

	QList<QPoint> list;

	foreach (Board::Wall wall, dirs.keys ()) {
		int d = 0;
		QPoint p2;
		do {
			p2 = pos + d*dirs[wall];
			const Robot *r2 = robots.atPosition (p2+dirs[wall]);
			if ((board.cell (p2) & wall) || (r2 != NULL && r2 != robot))
				break;
			d++;
		} while (true);
		if (p2 != pos)
			list << p2;
	}

	return list;
}

QList<QPoint> DefaultRules::specialRobotMoves (const Board &board, const Robots &robots, RobotColor color) const {
	return regularRobotMoves (board, robots, color);
}
