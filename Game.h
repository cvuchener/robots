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
	enum Mode {
		PREPARATION,
		MOVING
	};

	Game (const Rules *rules);
	virtual ~Game ();

	const Board &board () const;
	const Robots &robots () const;
	const Robot &robot (RobotColor) const;
	const Rules *rules () const;

	QList<QPoint> validMoves (RobotColor) const;
	bool move (RobotColor, QPoint position);

	void setGameMode (Mode mode);

signals:
	void robotMoved (const Robot *);

private:
	Mode _mode;
	Robots _robots;
	Board _board;
	const Rules *_rules;
};

#endif // GAME_H
