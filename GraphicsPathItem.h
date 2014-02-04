#ifndef GRAPHICSPATHITEM_H
#define GRAPHICSPATHITEM_H

#include <QGraphicsItem>

#include "Robot.h"

class GraphicsPathItem: public QGraphicsItem {
public:
	GraphicsPathItem (const QPoint &start, const QPoint &end, RobotColor color);
	virtual ~GraphicsPathItem ();

	virtual QRectF boundingRect () const;
	virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	QPoint _start, _end;
	RobotColor _color;
};

#endif // GRAPHICSPATHITEM_H
