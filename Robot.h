#ifndef ROBOT_H
#define ROBOT_H

#include <QPoint>

class Robot {
public:
	enum Color {
		WHITE = 0,
		RED,
		BLUE,
		GREEN,
		YELLOW,
		ROBOT_COUNT
	};

	Robot (Color color, const QPoint &position);
	virtual ~Robot ();

	QPoint position () const;
	Color color () const;

	void move (const QPoint &position);

	const static QList<Color> COLORS;
private:
	Color _color;
	QPoint _position;
};

#endif // ROBOT_H
