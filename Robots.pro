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
    Board.h \
    PathFinder.h \
    GraphicsPathItem.h \
    Target.h \
    GraphicsTargetItem.h

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
    Board.cpp \
    PathFinder.cpp \
    GraphicsPathItem.cpp \
    Target.cpp \
    GraphicsTargetItem.cpp

FORMS += \
    MainWindow.ui
