#ifndef GRAPHICSBOARDITEM_H
#define GRAPHICSBOARDITEM_H

#include <QGraphicsItem>

#include "Game.h"

class GraphicsBoardItem: public QGraphicsItem {
public:
	GraphicsBoardItem (const Board &board);
	virtual ~GraphicsBoardItem ();

	virtual	QRectF boundingRect () const;
	virtual	void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	const static QPen _WALL_PEN;
	const static QPen _GRID_PEN;

	QSize _board_size;
};

#endif // GRAPHICSBOARDITEM_H
