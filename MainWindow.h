#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_MainWindow.h>

#include "Game.h"
#include "GameScene.h"
#include "PathFinder.h"

class MainWindow: public QMainWindow, private Ui::MainWindow {
	Q_OBJECT
public:
	MainWindow (QWidget *parent = nullptr);
	virtual ~MainWindow ();

public slots:
	void on__zoom_slider_valueChanged (int);
	void on__target_combobox_currentIndexChanged (int);
	void on__search_path_button_clicked ();
	void on__cancel_search_button_clicked ();
	void on__state_new_cost_button_clicked ();
	void searchFinished ();
	void pathFound (unsigned int cost, QList<QPair<RobotColor, QPoint>>);
	void onGameStateChanged (Game::State);
	void onNewTarget (const Target *);

private:
	Game *_game;
	GameScene *_scene;
	PathFinder *_pathfinder;
};

#endif // MAINWINDOW_H
