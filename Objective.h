#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "Robot.h"

class Objective {
public:
	enum Value {
		A, B, C, D
	};

	Objective (Robot::Color color, Value value, QPoint position);
	~Objective ();

	bool accept (const Robot *) const;
	Robot::Color color () const;
	QPoint position () const;

private:
	Robot::Color _color;
	Value _value;
	QPoint _position;
};

#endif // OBJECTIVE_H
