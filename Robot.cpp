#include "Robot.h"

#include <QList>

const Robot::Color *Robot::Color::WHITE	= new Robot::Color (0, Qt::white,	"White");
const Robot::Color *Robot::Color::RED		= new Robot::Color (1, Qt::red,		"Red");
const Robot::Color *Robot::Color::BLUE		= new Robot::Color (2, Qt::blue,	"Blue");
const Robot::Color *Robot::Color::GREEN	= new Robot::Color (3, Qt::green,	"Green");
const Robot::Color *Robot::Color::YELLOW	= new Robot::Color (4, Qt::yellow,	"Yellow");

const QList<const Robot::Color *>Robot::COLORS = QList<const Robot::Color *> ()
											  << Robot::Color::WHITE
											  << Robot::Color::RED
											  << Robot::Color::BLUE
											  << Robot::Color::GREEN
											  << Robot::Color::YELLOW;
const unsigned int Robot::ROBOT_COUNT = 5;

Robot::Color::Color (unsigned int index, const QColor &color, const QString &name):
		_index (index), _color (color), _name (name) {
}

Robot::Color::operator QColor () const {
	return _color;
}

Robot::Color::operator unsigned int () const {
	return _index;
}

QString Robot::Color::toString () const {
	return _name;
}

Robot::Robot (const Color *color, const QPoint &position):
	_color (color), _position (position) {
}

Robot::~Robot () {
}

const Robot::Color *Robot::color () const {
	return _color;
}

QPoint Robot::position () const {
	return _position;
}

void Robot::move (const QPoint &position) {
	_position = position;
}
