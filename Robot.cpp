#include "Robot.h"

#include <QList>

const QList<Robot::Color>Robot::COLORS = QList<Robot::Color> ()
											  << Robot::WHITE
											  << Robot::RED
											  << Robot::BLUE
											  << Robot::GREEN
											  << Robot::YELLOW;

Robot::Robot (Color color, const QPoint &position):
	_color (color), _position (position) {
}

Robot::~Robot () {
}

Robot::Color Robot::color () const {
	return _color;
}

QPoint Robot::position () const {
	return _position;
}

void Robot::move (const QPoint &position) {
	_position = position;
}
