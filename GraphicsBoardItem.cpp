#include "GraphicsBoardItem.h"

#include <QPen>
#include <QPainter>

const QPen GraphicsBoardItem::_WALL_PEN = QPen (QBrush (Qt::black), 0.2, Qt::SolidLine, Qt::RoundCap);
const QPen GraphicsBoardItem::_GRID_PEN = QPen (QBrush (Qt::darkGray), 0.05, Qt::DashLine, Qt::FlatCap);

GraphicsBoardItem::GraphicsBoardItem (const Board &board): _board_size (board.size ()) {
	QMap<Board::Wall, QLineF> lines;
	lines.insert (Board::NORTH, QLineF (-0.5, -0.5, +0.5, -0.5));
	lines.insert (Board::EAST,  QLineF (+0.5, -0.5, +0.5, +0.5));
	lines.insert (Board::SOUTH, QLineF (-0.5, +0.5, +0.5, +0.5));
	lines.insert (Board::WEST,  QLineF (-0.5, -0.5, -0.5, +0.5));
	unsigned int w = board.size ().width (), h = board.size ().width ();
	for (unsigned int x = 0; x < w; x++)
		for (unsigned int y = 0; y < h; y++) {
			if (board.cell (QPoint (x, y)) == Board::FULL) {
				QGraphicsRectItem *block = new QGraphicsRectItem (QRectF (-0.5, -0.5, 1.0, 1.0).translated (x, y), this);
				block->setPen (_WALL_PEN);
				block->setBrush (Qt::black);
			}
			else {
				foreach (Board::Wall wall, lines.keys ()) {
					QGraphicsLineItem *border = new QGraphicsLineItem (lines[wall].translated (x, y), this);
					border->setPen (board.cell (QPoint (x, y)) & wall ? _WALL_PEN : _GRID_PEN);
					border->setZValue (board.cell (QPoint (x, y)) & wall ? 0.2 : 0.1);
				}
			}
		}
}

GraphicsBoardItem::~GraphicsBoardItem () {
}

QRectF GraphicsBoardItem::boundingRect () const {
	return QRectF (QPointF (-0.5, -0.5), QSizeF (_board_size));
}

void GraphicsBoardItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush (QBrush (QColor (Qt::lightGray)));
	painter->setPen (QPen (Qt::NoPen));
	painter->drawRect (boundingRect ());
}
