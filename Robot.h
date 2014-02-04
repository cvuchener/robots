#ifndef ROBOT_H
#define ROBOT_H

#include <QPoint>
#include <QColor>

class Robot {
public:
	class Color {
	public:
		Color (const Color &) = delete;

		static const Color
				*WHITE,
				*RED,
				*BLUE,
				*GREEN,
				*YELLOW;

		operator QColor () const;
		operator unsigned int () const;
		QString toString () const;

	private:
		Color (unsigned int, const QColor &, const QString &);

		unsigned int _index;
		QColor _color;
		QString _name;
	};

	static const QList<const Color *> COLORS;
	static const unsigned int ROBOT_COUNT;

	Robot () = delete;
	Robot (const Color *color, const QPoint &position);
	virtual ~Robot ();

	QPoint position () const;
	const Color *color () const;

	void move (const QPoint &position);
private:
	const Color *_color;
	QPoint _position;
};

typedef const Robot::Color *RobotColor;

#endif // ROBOT_H
