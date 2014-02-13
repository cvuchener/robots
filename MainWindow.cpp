#include "MainWindow.h"

#include "DefaultRules.h"

MainWindow::MainWindow (QWidget *parent): QMainWindow (parent), _pathfinder (nullptr) {
	setupUi (this);
	_cancel_search_button->setVisible (false);

	_game = new Game (new DefaultRules ());
	_scene = new GameScene (_game);
	_game_view->setScene (_scene);
	_game_view->setTransform (QTransform::fromScale (32.0, 32.0));

	const QList<const Target *> &objs = _game->board ().targets ();
	for (int i = 0; i < objs.count (); i++)
		_target_combobox->addItem (QString ("%1 %2").arg (objs.at (i)->color()->toString ()).arg (objs.at (i)->symbol()->toString ()), QVariant (i));

	connect (_show_path_checkbox, SIGNAL (toggled (bool)), _scene, SLOT (setPathVisible (bool)));
	connect (_clear_path_button, SIGNAL (clicked ()), _scene, SLOT (clearPath ()));

	connect (_save_button, SIGNAL (clicked ()), _game, SLOT (saveRobots ()));
	connect (_restore_button, SIGNAL (clicked ()), _game, SLOT (restoreRobots ()));
	connect (_end_preparation_button, SIGNAL (clicked ()), _game, SLOT (endPreparation ()));

	connect (_game, SIGNAL (stateChanged (Game::State)), this, SLOT (onGameStateChanged (Game::State)));
	connect (_game, SIGNAL (newTarget (const Target *)), this, SLOT (onNewTarget (const Target *)));
}

MainWindow::~MainWindow () {
	if (_pathfinder) {
		_pathfinder->cancel ();
		_pathfinder->wait ();
		delete _pathfinder;
	}

	delete _scene;
	delete _game;
}

void MainWindow::on__zoom_slider_valueChanged (int value) {
	_game_view->setTransform (QTransform::fromScale (value, value));
}

void MainWindow::on__search_path_button_clicked () {
	_cancel_search_button->setVisible (true);
	_search_path_button->setVisible (false);
	_search_param_group->setEnabled (false);

	_path_cost->setText (QString());
	_path_widget->clear ();

	_search_progressbar->setValue (0);
	_search_progressbar->setMaximum (0);

	_pathfinder = new PathFinder (_game->rules (), _game->board (), _game->robots (),
								  _game->board ().targets ().at (_target_combobox->currentData().toInt()),
								  _maximum_path_length->value ());
	qRegisterMetaType<QList<QPair<RobotColor, QPoint>>> ("QList<QPair<RobotColor, QPoint>>");
	connect (_pathfinder, SIGNAL (pathFound (unsigned int, QList<QPair<RobotColor, QPoint>>)), _scene, SLOT (showPath (unsigned int, QList<QPair<RobotColor, QPoint>>)));
	connect (_pathfinder, SIGNAL (pathFound (unsigned int, QList<QPair<RobotColor, QPoint>>)), this, SLOT (pathFound (unsigned int, QList<QPair<RobotColor, QPoint>>)));
	connect (_pathfinder, SIGNAL (finished ()), this, SLOT (searchFinished ()) );
	_pathfinder->start ();

}

void MainWindow::on__cancel_search_button_clicked () {
	_pathfinder->cancel ();
}

void MainWindow::searchFinished () {
	if (_pathfinder) {
		delete _pathfinder;
		_pathfinder = nullptr;
	}
	_search_progressbar->setValue (1);
	_search_progressbar->setMaximum (1);

	_cancel_search_button->setVisible (false);
	_search_path_button->setVisible (true);
	_search_param_group->setEnabled (true);

}

void MainWindow::pathFound (unsigned int cost, QList<QPair<RobotColor, QPoint>> moves) {
	_path_cost->setText (QString::number (cost));

	_path_widget->clear ();
	for (QList<QPair<RobotColor, QPoint>>::const_iterator it = moves.begin (); it != moves.end (); it++) {
		QTreeWidgetItem *item = new QTreeWidgetItem (_path_widget);
		item->setData (0, Qt::DisplayRole, (*it).first->toString ());
		item->setData (1, Qt::DisplayRole, QString ("%1, %2").arg ((*it).second.x ()).arg ((*it).second.y ()));
	}
}

void MainWindow::on__target_combobox_currentIndexChanged (int) {
	_search_progressbar->setValue (0);
	_search_progressbar->setMaximum (1);
}

void MainWindow::onGameStateChanged (Game::State state) {
	switch (state) {
	case Game::PREPARATION:
		_game_phase->setText ("Preparation");
		_end_preparation_button->setVisible (true);
		_current_target_group->setVisible (false);
		break;

	case Game::SEARCH:
		_game_phase->setText ("Search");
		_end_preparation_button->setVisible (false);
		break;

	case Game::TIMED_SEARCH:
		_game_phase->setText ("Timed search");
		break;

	case Game::MOVING:
		_game_phase->setText ("Moving");
		break;

	default:
			break;
	}
}

void MainWindow::onNewTarget (const Target *target) {
	_current_target->setText (QString ("%1 %2").arg (target->color()->toString ()).arg (target->symbol()->toString ()));
}

void MainWindow::on__state_new_cost_button_clicked () {
	_game->stateMoveCount (_new_cost->value ());
}
