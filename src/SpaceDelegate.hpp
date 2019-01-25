#pragma once

#include <QStyledItemDelegate>

class SpaceDelegate : public QStyledItemDelegate 
{
	Q_OBJECT

public:
	SpaceDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
				const QModelIndex &index) const override;

	QSize sizeHint(const QStyleOptionViewItem &option,
				   const QModelIndex &index) const override;
};
