#pragma once

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextEdit>
#include <QListView>
#include <QFile>
#include <QFileInfo>
#include <QDomDocument>
#include "Game.hpp"
#include "SpaceDelegate.hpp"

class QListWidget;
class QPushButton;
class QLabel;
class QVBoxLayout;
class QMenu;
class QAction;
class QWidget;

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
    void sell_house();
    void putUnderMortgage();
	void scroll_to_bottom();
	void proceed_action();
	void select_tab();
    void loadGame();
    void saveGame();
    void handleBadXML();

private:
    void createDockWindows();
    void updateTabs(std::vector<Player*> players);
    void updateModel();
    void mainMenu(std::vector<std::string>& names);
	void reactToField();
	void display_tabs();
    void createActions();
    void createMenus();
	void handle_proceed(bool bot);
    inline void load(const QString& fileName);
    inline void save(const QString& fileName);
	
    // menus
    QMenu* loadSaveMenu;
    QAction* saveAct;
    QAction* loadAct;

	// right dock
    QWidget* right_dock;
    QPushButton* roll_button;
    QPushButton* upgrade_button;
    QPushButton* mortgage_button;
    QPushButton* sell_house_button;
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
    QListView* player_view;
    QTableView *view;
    QTextEdit *infoText;

	static Game* game;
	static std::vector<Space*> spaces;
    static std::vector<Player*> playersTest;

    //HACK: global variable used to store currently selected field
    QVariant currentSelection;

	SpaceDelegate *spaceDelegate;

Q_SIGNALS:
    void dataChanged();

};
