#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QList>

#include "Robots.h"
#include "Rules.h"
#include "Board.h"

class Game: public QObject {
	Q_OBJECT
public:
	Game (const Rules *rules);
	virtual ~Game ();

	const Board &board () const;
	const Robots &robots () const;
	const Robot &robot (Robot::Color) const;
	const Rules *rules () const;

	QList<QPoint> validMoves (Robot::Color) const;
	bool move (Robot::Color, QPoint position);

signals:
	void robotMoved (const Robot *);

private:
	Robots _robots;
	Board _board;
	const Rules *_rules;
};

#endif // GAME_H