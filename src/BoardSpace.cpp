#include <QtWidgets>
#include <iostream>

#include "BoardSpace.hpp"

BoardSpace::BoardSpace(int pos, int numOfBuildings)
	: myNumOfBuildings(numOfBuildings), myPos(pos)
{
	buildingPolygon << QPointF(5, 5) << QPointF(7, 5)
					<< QPointF(7, 7) << QPointF(5, 7);
}

QSize BoardSpace::sizeHint(int row, int col) const 
{
	if (row >= 1 && row <=10 && col >= 1 && col <= 10) {
		return QSize(0,0);
	}

	if ((row == 10 && col == 10) || (row == 10 && col == 0) 
			|| (row == 0 && col == 10) || (row == 0 && col == 0)) {
		return QSize(100, 100);
	} else if (col == 10 || col == 0) {
		return QSize(100, 60);
	} else {
		return QSize(60, 100);
	}
}

void BoardSpace::paint(int row, int col, QPainter *painter, const QRect &rect,
						const QPalette &palette) const
{
	painter->save();

	if (row >=1 && row < 10 && col >= 1 && col < 10)
		return;

	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(Qt::NoPen);

	painter->setBrush(palette.window());
	
	std::cout << myPos << std::endl;

	QPixmap pix("./images/image0" + QString::number(myPos) + ".png");
	painter->drawPixmap(rect, pix, pix.rect());

	painter->translate(rect.x(), rect.y());
	painter->drawPolygon(buildingPolygon, Qt::WindingFill);
	
	if (myNumOfBuildings > 0) {
		for (int i=0; i < myNumOfBuildings; ++i) {
			painter->drawPolygon(buildingPolygon, Qt::WindingFill);
			painter->translate(1.0, 0.0);
		}
	}

	painter->restore();
}
