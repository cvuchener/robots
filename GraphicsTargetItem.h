#ifndef GRAPHICSTARGETITEM_H
#define GRAPHICSTARGETITEM_H

#include <QGraphicsItem>

#include "Target.h"

class GraphicsTargetItem: public QGraphicsItem {
public:
	GraphicsTargetItem (const Target *target, QGraphicsItem *parent = nullptr);
	virtual ~GraphicsTargetItem ();

	virtual QRectF boundingRect () const;
	virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	const Target *_target;
};

#endif // GRAPHICSTARGETITEM_H
