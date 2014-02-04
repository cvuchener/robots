#include "Objective.h"

const Objective::Symbol *Objective::Symbol::A = new Objective::Symbol ("A");
const Objective::Symbol *Objective::Symbol::B = new Objective::Symbol ("B");
const Objective::Symbol *Objective::Symbol::C = new Objective::Symbol ("C");
const Objective::Symbol *Objective::Symbol::D = new Objective::Symbol ("D");

QString Objective::Symbol::toString () const {
	return _name;
}

Objective::Symbol::Symbol (const QString &name): _name (name) {
}

Objective::Objective (RobotColor color, const Objective::Symbol *symbol, QPoint position):
		_color (color), _symbol (symbol), _position (position) {
}

Objective::~Objective () {
}

bool Objective::accept (const Robot *robot) const {
	return (_color == Robot::Color::WHITE) || (_color == robot->color ());
}

RobotColor Objective::color () const {
	return _color;
}

const Objective::Symbol *Objective::symbol () const {
	return _symbol;
}

QPoint Objective::position () const {
	return _position;
}
