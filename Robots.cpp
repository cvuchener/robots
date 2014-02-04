#include "Robots.h"

#include <QList>

Robots::Robots (const QList<QPoint> &positions) {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		_robots[i] = new Robot (static_cast<Robot::Color>(i), positions.at(i));
}

Robots::Robots (const Robots &robots) {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		_robots[i] = new Robot (*robots._robots[i]);
}

Robots::~Robots () {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		delete _robots[i];
}

Robot *Robots::operator[] (Robot::Color color) {
	return _robots[color];
}

const Robot *Robots::operator[] (Robot::Color color) const {
	return _robots[color];
}

Robot *Robots::atPosition (const QPoint &position) {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		if (_robots[i]->position () == position)
			return _robots[i];
	return nullptr;
}

const Robot *Robots::atPosition (const QPoint &position) const {
	for (unsigned int i = 0; i < Robot::ROBOT_COUNT; i++)
		if (_robots[i]->position () == position)
			return _robots[i];
	return nullptr;
}
