QT += widgets

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    Robot.h \
    Rules.h \
    Game.h \
    MainWindow.h \
    GameScene.h \
    DefaultRules.h \
    GraphicsRobotItem.h \
    GraphicsBoardItem.h \
    Robots.h \
    Objective.h \
    Board.h \
    PathFinder.h \
    GraphicsObjectiveItem.h \
    GraphicsPathItem.h

SOURCES += \
    Robot.cpp \
    Rules.cpp \
    main.cpp \
    MainWindow.cpp \
    GameScene.cpp \
    GraphicsRobotItem.cpp \
    DefaultRules.cpp \
    Game.cpp \
    GraphicsBoardItem.cpp \
    Robots.cpp \
    Objective.cpp \
    Board.cpp \
    PathFinder.cpp \
    GraphicsObjectiveItem.cpp \
    GraphicsPathItem.cpp

FORMS += \
    MainWindow.ui
