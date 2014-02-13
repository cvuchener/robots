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
	PathFinder (const Rules *rules, const Board &board, const Robots &robots, const Target *target, int max_length);
	virtual ~PathFinder ();

public slots:
	void cancel ();

signals:
	void pathFound (unsigned int cost, QList<QPair<RobotColor, QPoint>>);

protected:
	virtual void run ();

private:
	unsigned int search_rec (unsigned int cost, unsigned int max_cost, QList<QPair<RobotColor, QPoint>> &path);

	bool _canceled;
	int _max_length;
	const Rules *_rules;
	const Board &_board;
	Robots _robots;
	const Target *_target;
	QList<RobotColor> _color_list;
};

#endif // PATHFINDER_H
