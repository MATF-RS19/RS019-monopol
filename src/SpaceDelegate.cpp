#include <QtWidgets>
#include <iostream>

#include "SpaceDelegate.hpp"
#include "Space.hpp"

void SpaceDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
						 const QModelIndex &index) const 
{
	int row = index.row();
	int col = index.column();
	Space* space = index.data(Qt::UserRole+1).value<Space*>();

	if (row > 0 && row < 10 && col > 0 && col < 10) {
		return;
	}	

	painter->save();

	QPolygonF polygon;
	polygon << QPointF(0.5,0.5) << QPointF(2.5,0.5)
			<< QPointF(2.5,2.5) << QPointF(0.5,2.5);
	
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(Qt::NoPen);

	painter->setBrush(option.palette.window());

	int num, dx, dy, tx, ty;
   	double sx, sy;
	if (row == 10) {
		num = 10 - col;
		dx = option.rect.x();
		dy = option.rect.y();
		sx = 4.5; sy = 7;
		tx = 1; ty = 0;
	} else if (row < 10 && col == 0) {
		num = 20 - row;
		dx = option.rect.x() + option.rect.width() - 20;
		dy = option.rect.y();
		sx = 7;	sy = 4.5;
		tx = 0; ty = 1;
	} else if (row == 0 && col > 0) {
		num = 20+col;
		dx = option.rect.x() + option.rect.width() - 14;
		dy = option.rect.y() + option.rect.height() - 20;
		sx = 4.5; sy = 7;
		tx = -1; ty = 0;
	} else if (row <= 10 && col == 10) {
		num = 30 + row;
		dx = option.rect.x();
		dy = option.rect.y() + option.rect.height() - 14;
		sx = 7; sy = 4.5;
		tx = 0; ty = -1;
	}

	QImage img("./images/image" + QString::number(num) + ".png");
	painter->drawImage(option.rect, img, img.rect()); 
	
	if (!space->player().empty()) {
		for (int p : space->player()) {
			painter->setPen(Qt::black);
			
			int x=0, y=0;
			if (p == 1) {
				x = -1; y = -1;
			} else if (p == 2) {
				x = 1; y = -1;
			} else if (p == 3) {
				x = -1; y = 1;
			} else if (p == 4) {
				x = 1; y = 1;
			}

			int diametar = 20;
			QRectF rect(option.rect.x() + option.rect.width()/2.0 + x*diametar/2, 
						option.rect.y() + option.rect.height()/2.0 + y*diametar/2, 
						diametar, diametar);
			painter->drawEllipse(rect);
			painter->setPen(Qt::white);
			painter->drawText(rect, Qt::AlignCenter, QString::number(p));
		}
	}

	painter->setBrush(option.palette.window());
	painter->setPen(Qt::NoPen);

	painter->translate(dx, dy);
	painter->scale(sx, sy);
	for (int i = 0; i < space->getNumBuildings(); ++i) {
		painter->drawPolygon(polygon, Qt::WindingFill);
		painter->translate(2.5*tx, 2.5*ty);
	}

	painter->restore();
/*	} else {
		std::cout << "Ne moze da konvertuje u boardspace" << std::endl;
		QStyledItemDelegate::paint(painter, option, index);
	}*/
}

QSize SpaceDelegate::sizeHint(const QStyleOptionViewItem &option, 
							  const QModelIndex &index) const
{
//	if (index.data().canConvert<BoardSpace>()) {
//		BoardSpace space = qvariant_cast<BoardSpace>(index.data());
		
		int row = index.row();
		int col = index.column();

		if (row >= 1 && row < 10 && col >= 1 && col < 10) {
			return QSize(0,0);
		}

		if ((row == 10 && col == 10) || (row == 10 && col == 0) 
				|| (row == 0 && col == 10) || (row == 0 && col == 0)) {
			return QSize(100, 100);
		} else if (col == 0 || col == 10) {
			return QSize(100, 60);
		} else {
			return QSize(60, 100);
		}

/*	} else {
		return QStyledItemDelegate::sizeHint(option, index);
	}*/
}
