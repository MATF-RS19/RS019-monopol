#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


private:
    void createDockWindows();
    QWidget* right_dock;
    QPushButton* buy_button;
    QPushButton* pass_button;
    QPushButton* roll_button;
    QPushButton* upgrade_button;
    QWidget* bottom_dock;
    QListWidget* description;
    QWidget* left_dock;
    QTabWidget* players;
    QLabel* dices;
	std::vector<QLabel*> player_tabs; 
};


#endif // MAINWINDOW_H
