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
	void on__search_path_button_clicked ();
	void searchFinished ();
	void pathFound (unsigned int cost, QList<QPair<Robot::Color, QPoint>>);

private:
	Game *_game;
	GameScene *_scene;
	PathFinder *_pathfinder;
};

#endif // MAINWINDOW_H
