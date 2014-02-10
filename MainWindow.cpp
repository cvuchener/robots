#include "MainWindow.h"

#include "DefaultRules.h"

MainWindow::MainWindow (QWidget *parent): QMainWindow (parent), _pathfinder (nullptr) {
	setupUi (this);
	_cancel_search_button->setVisible (false);

	_game = new Game (new DefaultRules ());
	_scene = new GameScene (_game);
	_game_view->setScene (_scene);
	_game_view->setTransform (QTransform::fromScale (32.0, 32.0));

	const QList<const Objective *> &objs = _game->board ().objectives ();
	for (int i = 0; i < objs.count (); i++)
		_objective_combobox->addItem (QString ("%1 %2").arg (objs.at (i)->color()->toString ()).arg (objs.at (i)->symbol()->toString ()), QVariant (i));

	_mode_combobox->addItem ("Preparation", static_cast<int> (Game::PREPARATION));
	_mode_combobox->addItem ("Moving", static_cast<int> (Game::MOVING));

	connect (_show_path_checkbox, SIGNAL (toggled (bool)), _scene, SLOT (setPathVisible (bool)));
	connect (_clear_path_button, SIGNAL (clicked ()), _scene, SLOT (clearPath ()));

	connect (_save_button, SIGNAL (clicked ()), _game, SLOT (saveRobots ()));
	connect (_restore_button, SIGNAL (clicked ()), _game, SLOT (restoreRobots ()));
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
								  _game->board ().objectives ().at (_objective_combobox->currentData().toInt()),
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

void MainWindow::on__mode_combobox_activated (int index) {
	_game->setGameMode (static_cast<Game::Mode> (_mode_combobox->itemData (index).toInt ()));
}

void MainWindow::on__objective_combobox_currentIndexChanged (int) {
	_search_progressbar->setValue (0);
	_search_progressbar->setMaximum (1);
}
