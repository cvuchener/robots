#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QList>
#include <QStack>
#include <QTimer>

#include "Robots.h"
#include "Rules.h"
#include "Board.h"

class Game: public QObject {
	Q_OBJECT
public:
	enum State {
		PREPARATION,
		SEARCH,
		TIMED_SEARCH,
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

public slots:
	void saveRobots ();
	void restoreRobots ();
	void endPreparation ();
	void stateMoveCount (unsigned int);
	void setSearchTimeout (int);
	void giveup ();

signals:
	void robotMoved (const Robot *);
	void newTarget (const Target *);
	void stateChanged (Game::State);
	void moveCounterUpdated (unsigned int);

private slots:
	void onSearchTimeout ();
	void onStateChanged (Game::State);

private:
	void setState (State state);

	State _state;
	Robots _robots;
	Robots _saved;
	Board _board;
	const Rules *_rules;
	QTimer _timer;
	const Target *_current_target;
	unsigned int _move_counter;
	QStack<unsigned int> _move_count_stack;
	QList<const Target *> _remaining_target;

};

#endif // GAME_H
