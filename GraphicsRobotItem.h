#ifndef GRAPHICSROBOTITEM_H
#define GRAPHICSROBOTITEM_H

#include <QGraphicsItem>

#include "Robot.h"

class GraphicsRobotItem: public QGraphicsItem {
public:
	GraphicsRobotItem (Robot::Color color, QGraphicsItem *parent = nullptr);
	virtual ~GraphicsRobotItem ();

	void setSelectedState (bool selected);

	virtual	QRectF boundingRect () const;
	virtual	void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	Robot::Color _color;
	bool _selected;
};

#endif // GRAPHICSROBOTITEM_H
