#ifndef ROBOTS_H
#define ROBOTS_H

#include "Robot.h"

class Robots {
public:
	Robots (const QList<QPoint> &positions);
	explicit Robots (const Robots &);
	~Robots ();

	Robot *operator[] (RobotColor);
	const Robot *operator[] (RobotColor) const;

	Robot *atPosition (const QPoint &position);
	const Robot *atPosition (const QPoint &position) const;

	Robots &operator= (const Robots &);

private:
	Robot *_robots;
};

#endif // ROBOTS_H
