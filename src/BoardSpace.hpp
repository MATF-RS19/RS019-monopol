#pragma once

#include <QMetaType>
#include <QPixmap>
#include <QLabel>

class Space;

class BoardSpace 
{
public:
	explicit BoardSpace(int pos = 0, int numOfBuildings = 0);

	void paint(int row, int col, QPainter *painter, const QRect &rect,
			   const QPalette &palette) const;
	QSize sizeHint(int row, int col) const;
	int numOfBuildings() const { return myNumOfBuildings; }
	void setNumOfBuildings(int num) { myNumOfBuildings = num; }

private:
	QPolygonF buildingPolygon;
	int myNumOfBuildings, myPos;
	bool hasPlayer;
};

Q_DECLARE_METATYPE(BoardSpace);
