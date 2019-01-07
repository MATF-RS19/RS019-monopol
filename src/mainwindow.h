#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Game.hpp"

class QListWidget;
class QPushButton;
class QLabel;

extern int numOfPlayers;

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    MainWindow();

private Q_SLOTS:
	void roll_dice();

private:
    void createDockWindows();
    void mainMenu(std::vector<std::string>& names);
    QWidget* right_dock;
    QPushButton* buy_button;
    QPushButton* roll_button;
    QPushButton* upgrade_button;
    QWidget* bottom_dock;
    QListWidget* description;
    QWidget* left_dock;
    QTabWidget* players_widget;
    QLabel* die_1;
	QLabel* die_2;
	QWidget* dice_widget;
	std::vector<QLabel*> player_tabs; 
	std::map<int, QPixmap*> die_sides;

	static Game* game;
};


#endif // MAINWINDOW_H
