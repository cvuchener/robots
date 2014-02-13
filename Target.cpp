#include "Target.h"

const Target::Symbol *Target::Symbol::A = new Target::Symbol ("A");
const Target::Symbol *Target::Symbol::B = new Target::Symbol ("B");
const Target::Symbol *Target::Symbol::C = new Target::Symbol ("C");
const Target::Symbol *Target::Symbol::D = new Target::Symbol ("D");

QString Target::Symbol::toString () const {
	return _name;
}

Target::Symbol::Symbol (const QString &name): _name (name) {
}

Target::Target (RobotColor color, const Target::Symbol *symbol, QPoint position):
		_color (color), _symbol (symbol), _position (position) {
}

Target::~Target () {
}

bool Target::accept (const Robot *robot) const {
	return (_color == Robot::Color::WHITE) || (_color == robot->color ());
}

RobotColor Target::color () const {
	return _color;
}

const Target::Symbol *Target::symbol () const {
	return _symbol;
}

QPoint Target::position () const {
	return _position;
}
