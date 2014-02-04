#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "Robot.h"

class Objective {
public:
	class Symbol {
	public:
		Symbol (const Symbol &) = delete;

		static const Symbol *A, *B, *C, *D;

		QString toString () const;

	private:
		Symbol (const QString &name);
		QString _name;
	};

	Objective (RobotColor color, const Symbol *symbol, QPoint position);
	~Objective ();

	bool accept (const Robot *) const;
	RobotColor color () const;
	const Symbol *symbol () const;
	QPoint position () const;

private:
	RobotColor _color;
	const Symbol *_symbol;
	QPoint _position;
};

typedef const Objective::Symbol *ObjectiveSymbol;

#endif // OBJECTIVE_H
