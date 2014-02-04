#ifndef DEFAULTRULES_H
#define DEFAULTRULES_H

#include "Rules.h"

class DefaultRules: public Rules {
public:
	DefaultRules ();
	virtual ~DefaultRules ();

	virtual QList<QPoint> regularRobotMoves (const Board &, const Robots &, RobotColor) const;
	virtual QList<QPoint> specialRobotMoves (const Board &, const Robots &, RobotColor) const;
};

#endif // DEFAULTRULES_H
