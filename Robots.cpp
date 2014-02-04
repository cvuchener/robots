#include "Robots.h"

#include <QList>

Robots::Robots (const QList<QPoint> &positions):
		_robots (static_cast<Robot *>(operator new [] (Robot::ROBOT_COUNT * sizeof (Robot)))) {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		new (&_robots[i]) Robot (Robot::COLORS.at (i), positions.at(i));
}

Robots::Robots (const Robots &robots):
	_robots (static_cast<Robot *>(operator new [] (Robot::ROBOT_COUNT * sizeof (Robot)))) {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		new (&_robots[i]) Robot (robots._robots[i]);
}

Robots::~Robots () {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		_robots[i].~Robot ();
	operator delete[] (static_cast<void *>(_robots));
}

Robot *Robots::operator[] (RobotColor color) {
	return &_robots[*color];
}

const Robot *Robots::operator[] (RobotColor color) const {
	return &_robots[*color];
}

Robot *Robots::atPosition (const QPoint &position) {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		if (_robots[i].position () == position)
			return &_robots[i];
	return nullptr;
}

const Robot *Robots::atPosition (const QPoint &position) const {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		if (_robots[i].position () == position)
			return &_robots[i];
	return nullptr;
}
