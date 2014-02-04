#include "GraphicsRobotItem.h"

#include <QPainter>

GraphicsRobotItem::GraphicsRobotItem (Robot::Color color, QGraphicsItem *parent): QGraphicsItem (parent), _color (color), _selected (false) {

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
	QMap<Robot::Color, QColor> colors;
	colors.insert (Robot::WHITE, Qt::white);
	colors.insert (Robot::RED, Qt::red);
	colors.insert (Robot::BLUE, Qt::blue);
	colors.insert (Robot::GREEN, Qt::green);
	colors.insert (Robot::YELLOW, Qt::yellow);

	painter->setPen (QPen (QBrush (Qt::black), 0.1, Qt::SolidLine));
	painter->setBrush (QBrush (colors[_color]));
	painter->drawEllipse (QPointF (0.0, 0.0), 0.3, 0.3);
}
