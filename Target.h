#ifndef TARGET_H
#define TARGET_H

#include "Robot.h"

class Target {
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

	Target (RobotColor color, const Symbol *symbol, QPoint position);
	~Target ();

	bool accept (const Robot *) const;
	RobotColor color () const;
	const Symbol *symbol () const;
	QPoint position () const;

private:
	RobotColor _color;
	const Symbol *_symbol;
	QPoint _position;
};

typedef const Target::Symbol *TargetSymbol;

#endif // TARGET_H
