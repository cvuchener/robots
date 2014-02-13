#include "GraphicsTargetItem.h"

#include <QPainter>

GraphicsTargetItem::GraphicsTargetItem (const Target *target, QGraphicsItem *parent): QGraphicsItem (parent), _target (target) {
}

GraphicsTargetItem::~GraphicsTargetItem () {
}

QRectF GraphicsTargetItem::boundingRect () const {
	return QRectF (-0.5, -0.5, 1.0, 1.0);
}

void GraphicsTargetItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen (QPen (QBrush (*_target->color ()), 0.01, Qt::SolidLine));
	painter->setBrush (QBrush (*_target->color ()));
	QFont font;
	font.setPixelSize (1);
	painter->setFont (font);

	painter->drawText (QRectF (-0.5, -0.5, 1.0, 1.0),
					   Qt::AlignCenter | Qt::AlignVCenter,
					   _target->symbol ()->toString ());
}
