#include "GraphicsPathItem.h"

#include <QPainter>

GraphicsPathItem::GraphicsPathItem (const QPoint &start, const QPoint &end, RobotColor color):
		_start (start), _end (end), _color (color) {
}

GraphicsPathItem::~GraphicsPathItem () {
}

QRectF GraphicsPathItem::boundingRect () const {
	QRectF rect = QRectF (_start, _end).normalized ().translated (-0.5, -0.5);
	rect.setBottomRight (rect.bottomRight() + QPointF (1.0, 1.0));
	return rect;
}

void GraphicsPathItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen (QPen (QBrush (*_color), 0.1, Qt::SolidLine));
	painter->setBrush (QBrush (*_color));

	painter->drawLine (_start, _end);

	QPainterPath path;
	QLineF unit  = QLineF (_start, _end).unitVector ();
	QLineF normal = unit.normalVector ();
	QPointF u (unit.dx (), unit.dy ());
	QPointF v (normal.dx (), normal.dy ());
	QPointF middle = 0.5 * (QPointF(_start) + QPointF (_end));
	path.moveTo (middle + 0.4*u);
	path.lineTo (middle - 0.2*u + 0.2*v);
	path.lineTo (middle - 0.2*u - 0.2*v);
	path.closeSubpath ();
	painter->drawPath (path);
}
