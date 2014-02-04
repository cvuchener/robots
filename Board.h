#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <QPoint>
#include <QSize>

#include "Objective.h"

class Board {
public:
	enum Wall {
		NORTH =	1,
		EAST =	2,
		SOUTH =	4,
		WEST =	8,
		FULL =	15
	};

	Board ();
	Board (const Board &) = delete;
	virtual ~Board ();

	QSize size () const;
	unsigned int cell (QPoint position) const;

	const QList<const Objective *> &objectives () const;

	Board &operator= (const Board &) = delete;

private:
	unsigned int _width, _height;
	unsigned int **_cells;
	QList<const Objective *> _objectives;
};

#endif // BOARD_H
