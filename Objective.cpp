#include "Objective.h"

Objective::Objective (Robot::Color color, Objective::Value value, QPoint position):
		_color (color), _value (value), _position (position) {
}

Objective::~Objective () {
}

bool Objective::accept (const Robot *robot) const {
	return (_color == Robot::WHITE) || (_color == robot->color ());
}

Robot::Color Objective::color () const {
	return _color;
}

QPoint Objective::position () const {
	return _position;
}
