#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextEdit>
#include "Game.hpp"

class QListWidget;
class QPushButton;
class QLabel;
class QVBoxLayout;

extern int numOfPlayers;

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    MainWindow();

private Q_SLOTS:
	void roll_dice();
	void display_cell(const QModelIndex&);

private:
    void createDockWindows();
    void mainMenu(std::vector<std::string>& names);
	// right dock
    QWidget* right_dock;
//    QPushButton* buy_button;
    QPushButton* roll_button;
    QPushButton* upgrade_button;
//    QWidget* bottom_dock;
//    QListWidget* description;
	QVBoxLayout* right_dock_layout;
	
	// left dock
    QWidget* left_dock;
    QLabel* die_1;
	QLabel* die_2;
	QWidget* dice_widget;
	std::map<int, QPixmap*> die_sides;
	std::vector<QLabel*> player_tabs; 
	QTabWidget* players_widget;

    //Added in order to be visible inside of function for creating docks
    QStandardItemModel *model;
    QTableView *view;
    QTextEdit *infoText;

	static Game* game;
	static std::vector<Space*> spaces;
};


#endif // MAINWINDOW_H
