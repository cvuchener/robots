#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include "GraphicsRobotItem.h"
#include "GraphicsBoardItem.h"
#include "GraphicsPathItem.h"
#include "Game.h"

class GameScene: public QGraphicsScene {
	Q_OBJECT
public:
	GameScene (Game *game);
	virtual ~GameScene ();

public slots:
	void setPathVisible (bool visible);
	void clearPath ();
	void updateRobot (const Robot *);
	void showPath (unsigned int cost, QList<QPair<RobotColor, QPoint>> path);

protected:
	virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);

private:
	Game *_game;
	GraphicsBoardItem _board;
	QMap<RobotColor, GraphicsRobotItem *> _robots;
	QList<QGraphicsRectItem *> _move_items;
	QList<QPoint> _moves;
	QList<GraphicsPathItem *> _path;
	RobotColor _selection;
};

#endif // GAMESCENE_H
