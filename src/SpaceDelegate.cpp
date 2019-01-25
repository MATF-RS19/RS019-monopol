#include <QtWidgets>
#include <iostream>

#include "SpaceDelegate.hpp"
#include "Space.hpp"

void SpaceDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
						 const QModelIndex &index) const 
{
//	if (index.data().canConvert<BoardSpace>()) {
//		BoardSpace space = qvariant_cast<BoardSpace>(index.data());
	int row = index.row();
	int col = index.column();
	Space* space = index.data(Qt::UserRole+1).value<Space*>();

	if (row > 0 && row < 10 && col > 0 && col < 10) {
		return;
	}	

	/*
	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, option.palette.highlight());
	}
	*/

	painter->save();

	QPolygonF polygon;
	polygon << QPointF(1,1) << QPointF(3,1)
			<< QPointF(3,3) << QPointF(1,3);
	
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(Qt::NoPen);

	painter->setBrush(option.palette.window());

	int num, dx, dy;
	if (row == 10) {
		num = 10 - col;
	} else if (row < 10 && col == 0) {
		num = 20 - row;
	} else if (row == 0 && col > 0) {
		num = 20+col;
	} else if (row <= 10 && col == 10) {
		num = 30 + row;
	}

	
//	}

	QImage img("./images/image" + QString::number(num) + ".png");
	painter->drawImage(option.rect, img, img.rect()); 
	
	if (!space->player().empty()) {
		for (int p : space->player()) {
			painter->setPen(Qt::black);
			
			if (p == 1) {
				painter->setBrush(Qt::red);
			} else if (p == 2) {
				painter->setBrush(Qt::blue);
			} else if (p == 3) {
				painter->setBrush(Qt::green);
			} else if (p == 4) {
				painter->setBrush(Qt::yellow);
			}

			painter->drawEllipse(option.rect.x() + 15*(p+1), option.rect.y() + 15*(p+1), 10, 10);
		}
	}

	for (int i = 0; i < space->getNumBuildings(); i++) {
		painter->translate(option.rect.x(), option.rect.y());
		painter->scale(5, 5);
		painter->drawPolygon(polygon, Qt::WindingFill);
		painter->translate(1, 0);
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
