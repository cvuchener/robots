#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QThread>

#include <QPair>
#include <QPoint>

#include "Rules.h"
#include "Board.h"
#include "Robots.h"

class PathFinder: public QThread {
	Q_OBJECT
public:
	PathFinder (const Rules *rules, const Board &board, const Robots &robots, const Objective *objective);
	virtual ~PathFinder ();

signals:
	void pathFound (unsigned int cost, QList<QPair<Robot::Color, QPoint>>);
	void progress (int value);

protected:
	virtual void run ();

private:
	unsigned int search_rec (unsigned int cost, unsigned int max_cost, QList<QPair<Robot::Color, QPoint>> &path, unsigned int max_length);

	const Rules *_rules;
	const Board &_board;
	Robots _robots;
	const Objective *_objective;
	QList<Robot::Color> _color_list;
};

#endif // PATHFINDER_H
