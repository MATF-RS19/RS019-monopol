#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextEdit>
#include <QListView>
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
	void upgrade_property();
	void scroll_to_bottom();
	void proceed_action();
	void select_tab();

private:
    void createDockWindows();
    void mainMenu(std::vector<std::string>& names);
	void reactToField();
	void display_tabs();
	
	// right dock
    QWidget* right_dock;
    QPushButton* roll_button;
    QPushButton* upgrade_button;
	QVBoxLayout* right_dock_layout;
	
	// left dock
    QWidget* left_dock;
    QLabel* die_1;
	QLabel* die_2;
	QWidget* dice_widget;
	std::map<int, QPixmap*> die_sides;
	std::vector<QTextEdit*> player_tabs; 
	QTabWidget* players_widget;
	QTextEdit *game_info;
	QString *game_info_text;
	QPushButton *proceed_button;

    //Added in order to be visible inside of function for creating docks
    QStandardItemModel *model;
    QStandardItemModel *players_model;
    QListView* player_view;
    QTableView *view;
    QTextEdit *infoText;

	static Game* game;
	static std::vector<Space*> spaces;
    static std::vector<Player*> playersTest;
};


#endif // MAINWINDOW_H
