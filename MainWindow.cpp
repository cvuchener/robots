#include "MainWindow.h"

#include "DefaultRules.h"

MainWindow::MainWindow (QWidget *parent): QMainWindow (parent), _pathfinder (nullptr) {
	setupUi (this);

	_game = new Game (new DefaultRules ());
	_scene = new GameScene (_game);
	_game_view->setScene (_scene);
	_game_view->setTransform (QTransform::fromScale (32.0, 32.0));

	const QList<const Objective *> &objs = _game->board ().objectives ();
	for (unsigned int i = 0; i < objs.count (); i++)
		_objective_combobox->addItem (QString::number(i), QVariant (i));
}

MainWindow::~MainWindow () {
	delete _scene;
	delete _game;
}

void MainWindow::on__zoom_slider_valueChanged (int value) {
	_game_view->setTransform (QTransform::fromScale (value, value));
}

void MainWindow::on__search_path_button_clicked () {
	if (_pathfinder) {
		_pathfinder->terminate();
	}
	_path_cost->setText (QString());
	_search_progressbar->setEnabled (true);
	_search_progressbar->setValue (0);

	_pathfinder = new PathFinder (_game->rules (), _game->board (), _game->robots (), _game->board ().objectives ().at (_objective_combobox->currentData().toInt()));
	qRegisterMetaType<QList<QPair<Robot::Color, QPoint>>> ("QList<QPair<Robot::Color, QPoint>>");
	connect (_pathfinder, SIGNAL (pathFound (unsigned int, QList<QPair<Robot::Color, QPoint>>)), _scene, SLOT (showPath (unsigned int, QList<QPair<Robot::Color, QPoint>>)));
	connect (_pathfinder, SIGNAL (pathFound (unsigned int, QList<QPair<Robot::Color, QPoint>>)), this, SLOT (pathFound (unsigned int, QList<QPair<Robot::Color, QPoint>>)));
	connect (_pathfinder, SIGNAL (progress (int)), _search_progressbar, SLOT (setValue (int)));
	connect (_pathfinder, SIGNAL (finished ()), this, SLOT (searchFinished ()) );
	_pathfinder->start ();

}

void MainWindow::searchFinished () {
	if (_pathfinder) {
		delete _pathfinder;
		_pathfinder = nullptr;
	}
	_search_progressbar->setValue (400);
	_search_progressbar->setEnabled (false);
}

void MainWindow::pathFound (unsigned int cost, QList<QPair<Robot::Color, QPoint>>) {
	_path_cost->setText (QString::number (cost));
}
