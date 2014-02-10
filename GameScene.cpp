#include "GameScene.h"

#include <QGraphicsSceneMouseEvent>

#include <qdebug.h>

GameScene::GameScene (Game *game):
		_game (game), _board (game->board ()),
		_selection (nullptr) {
	addItem (&_board);

	foreach (RobotColor color, Robot::COLORS) {
		GraphicsRobotItem *robot = new GraphicsRobotItem (color);
		_robots.insert (color, robot);
		robot->setPos (_game->robots ()[color]->position ());
		addItem (robot);
	}

	connect (_game, SIGNAL (robotMoved (const Robot *)), this, SLOT (updateRobot (const Robot *)));
}

GameScene::~GameScene () {
	foreach (GraphicsRobotItem *robot, _robots)
		delete robot;
	foreach (QGraphicsRectItem *item, _move_items)
		delete item;
}

void GameScene::updateRobot (const Robot *robot) {
	_robots[robot->color ()]->setPos (robot->position ());
}

void GameScene::setPathVisible (bool visible) {
	foreach (GraphicsPathItem *item, _path)
		item->setVisible (visible);
}

void GameScene::clearPath () {
	foreach (GraphicsPathItem *item, _path)
		delete item;
	_path.clear ();
}

void GameScene::mousePressEvent (QGraphicsSceneMouseEvent *event) {
	QPoint pos = event->scenePos ().toPoint ();
	qDebug () << pos;
	const Robot *robot = _game->robots ().atPosition (pos);

	if (!robot && !_moves.contains (pos))
		return;

	foreach (QGraphicsRectItem *item, _move_items) {
		delete item;
	}
	_move_items.clear ();

	if (robot) {
		_moves.clear ();
		if (_selection == robot->color ())
			_selection = nullptr;
		else {
			_selection = robot->color ();
			QList<QPoint> valid_moves = _game->validMoves (robot->color ());
			foreach (QPoint p, valid_moves) {
				QGraphicsRectItem *item = new QGraphicsRectItem (QRectF (-0.5, -0.5, 1.0, 1.0).translated(p));
				item->setBrush (QColor (128, 255, 64, 64));
				item->setPen (Qt::NoPen);
				addItem (item);
				_move_items << item;
				_moves << p;
			}
		}
		return;
	}
	if (_selection && _moves.contains (pos)) {
		_game->move (_selection, pos);
		_moves.clear ();
		_selection = nullptr;
	}
}


void GameScene::showPath (unsigned int cost, QList<QPair<RobotColor, QPoint>> path) {
	clearPath ();

	Robots *robots = new Robots (_game->robots ());
	for (QList<QPair<RobotColor, QPoint>>::iterator it = path.begin (); it != path.end (); it++) {
		RobotColor color = (*it).first;
		Robot *robot = (*robots)[color];
		QPoint &pos = (*it).second;
		GraphicsPathItem *item = new GraphicsPathItem (robot->position (), pos, color);
		addItem (item);
		_path << item;
		robot->move (pos);
	}
	delete robots;
}
