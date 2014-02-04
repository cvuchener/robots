#include "GraphicsRobotItem.h"

#include <QPainter>

GraphicsRobotItem::GraphicsRobotItem (RobotColor color, QGraphicsItem *parent): QGraphicsItem (parent), _color (color), _selected (false) {

}

GraphicsRobotItem::~GraphicsRobotItem () {

}

void GraphicsRobotItem::setSelectedState (bool selected) {
	_selected = selected;
}


QRectF GraphicsRobotItem::boundingRect () const {
	return QRectF (-0.3, -0.3, 0.6, 0.6);
}

void GraphicsRobotItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen (QPen (QBrush (Qt::black), 0.1, Qt::SolidLine));
	painter->setBrush (QBrush (*_color));
	painter->drawEllipse (QPointF (0.0, 0.0), 0.3, 0.3);
}
