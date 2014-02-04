#ifndef RULES_H
#define RULES_H

#include <QList>
#include <QPoint>

#include "Board.h"
#include "Robots.h"

class Rules {
public:
	Rules ();
	virtual ~Rules ();

	QList<QPoint> validMoves (const Board &, const Robots &, RobotColor) const;
	virtual QList<QPoint> regularRobotMoves (const Board &, const Robots &, RobotColor) const = 0;
	virtual QList<QPoint> specialRobotMoves (const Board &, const Robots &, RobotColor) const = 0;
};

#endif // RULES_H
