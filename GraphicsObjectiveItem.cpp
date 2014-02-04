#include "GraphicsObjectiveItem.h"

#include <QPainter>

GraphicsObjectiveItem::GraphicsObjectiveItem (const Objective *objective, QGraphicsItem *parent): QGraphicsItem (parent), _objective (objective) {
}

GraphicsObjectiveItem::~GraphicsObjectiveItem () {
}

QRectF GraphicsObjectiveItem::boundingRect () const {
	return QRectF (-0.5, -0.5, 1.0, 1.0);
}

void GraphicsObjectiveItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen (QPen (QBrush (*_objective->color ()), 0.01, Qt::SolidLine));
	painter->setBrush (QBrush (*_objective->color ()));
	QFont font;
	font.setPixelSize (1);
	painter->setFont (font);

	painter->drawText (QRectF (-0.5, -0.5, 1.0, 1.0),
					   Qt::AlignCenter | Qt::AlignVCenter,
					   _objective->symbol ()->toString ());
}
