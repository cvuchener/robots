#ifndef GRAPHICSOBJECTIVEITEM_H
#define GRAPHICSOBJECTIVEITEM_H

#include <QGraphicsItem>

#include "Objective.h"

class GraphicsObjectiveItem: public QGraphicsItem {
public:
	GraphicsObjectiveItem (const Objective *objective, QGraphicsItem *parent = nullptr);
	virtual ~GraphicsObjectiveItem ();

	virtual QRectF boundingRect () const;
	virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	const Objective *_objective;
};

#endif // GRAPHICSOBJECTIVEITEM_H
