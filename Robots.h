#ifndef ROBOTS_H
#define ROBOTS_H

#include "Robot.h"

class Robots {
public:
	Robots (const QList<QPoint> &positions);
	explicit Robots (const Robots &);
	~Robots ();

	Robot *operator[] (Robot::Color);
	const Robot *operator[] (Robot::Color) const;

	Robot *atPosition (const QPoint &position);
	const Robot *atPosition (const QPoint &position) const;

	Robots &operator= (const Robots &) = delete;

private:
	Robot *_robots[Robot::ROBOT_COUNT];
};

#endif // ROBOTS_H
