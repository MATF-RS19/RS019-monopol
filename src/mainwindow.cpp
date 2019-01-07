#include <QtWidgets>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <iostream>

#include "mainwindow.h"
#include "Game.hpp"
#include "Player.hpp"
#include "Bank.hpp"

int numOfPlayers;
Game* MainWindow::game;
QStandardItemModel *model;

MainWindow::MainWindow()
{
    //Create vector of names
    std::vector<std::string> names(numOfPlayers);
	
	mainMenu(names);

	die_sides[1] = new QPixmap("./images/die1.png");
	die_sides[2] = new QPixmap("./images/die2.png");
	die_sides[3] = new QPixmap("./images/die3.png");
	die_sides[4] = new QPixmap("./images/die4.png");
	die_sides[5] = new QPixmap("./images/die5.png");
	die_sides[6] = new QPixmap("./images/die6.png");

    //Create game for selected number of players
    game = new Game(numOfPlayers, names);

    //Get spaces
    std::vector<Space*> spaces = game->getBoard()->getSpaces();

    //Create model for all spaces on the board
	model = new QStandardItemModel(11,11);

    //Populate model with space images
    int i=10,j=10,i_increment=0,j_increment=-1;
        foreach(const auto& s, spaces){
            QStandardItem *spaceItem = new QStandardItem();
            spaceItem->setText(QString::fromStdString(s->getName()));
            //spaceItem->setData(QVariant(QPixmap::fromImage(image)), Qt::DisplayRole);
            //QBrush *qb = new QBrush(QImage("/images/property1.jpg"));
            //spaceItem->setForeground(*qb);
            //spaceItem->setBackground(QBrush(QPixmap::fromImage(image)));
            //spaceItem->setIcon(QIcon(":MyResources/images/monopoly_board.jpg"));

            model->setItem(i,j,spaceItem);

            i+=i_increment;
            j+=j_increment;
            if(i==10 && j==0){
                i_increment=-1;
                j_increment=0;
            }
            if(i==0 && j==0){
                i_increment=0;
                j_increment=1;
            }
            if(i==0 && j==10){
                i_increment=1;
                j_increment=0;
            }

        }
	
//     QGraphicsScene *scene = new QGraphicsScene(this);
//     scene->setSceneRect(0, 0, 885, 885);
//     scene->setItemIndexMethod(QGraphicsScene::NoIndex);
// 
//     QPixmap pix("./images/monopoly_board.jpg");
//     scene->setBackgroundBrush(QPixmap(pix));

    QTableView *view = new QTableView();
    view->setModel(model);
    view->resize(500, 500);
    view->setStyleSheet("selection-background-color : red;");
    view->setSortingEnabled(false);



    QModelIndexList selected = view->selectionModel()->selectedIndexes();
    foreach(QModelIndex i, selected){
        int row = i.row();
        int col = i.column();
        QMessageBox msgBox;
        msgBox.setText(tr("Hello!"));
        msgBox.exec();
    }
    //view->setRenderHint(QPainter::Antialiasing);
    //view->setDragMode(QGraphicsView::ScrollHandDrag);

    setCentralWidget(view);
    createDockWindows();
	setWindowState(Qt::WindowMaximized);

	connect(roll_button, SIGNAL(clicked(bool)),
			this, SLOT(roll_dice()));
}

void MainWindow::mainMenu(std::vector<std::string>& names) 
{
	// ask for number of players
	QMessageBox msgBox;
	msgBox.setText(tr("Hello! Select number of players!"));
	QPushButton* btn1 = msgBox.addButton(QString("One"), QMessageBox::ActionRole);
	QPushButton* btn2 = msgBox.addButton(QString("Two"), QMessageBox::ActionRole);
	QPushButton* btn3 = msgBox.addButton(QString("Three"), QMessageBox::ActionRole);
	QPushButton* btn4 = msgBox.addButton(QString("Four"), QMessageBox::ActionRole);

	msgBox.exec();

	// set number of players depending on the answer
	if (msgBox.clickedButton() == btn1) {
	   	numOfPlayers = 1;
	} else if (msgBox.clickedButton() == btn2) {
		numOfPlayers = 2;
	} else if (msgBox.clickedButton() == btn3) {
		numOfPlayers = 3;
	} else if (msgBox.clickedButton() == btn4) {
		numOfPlayers = 4;
	}
	
	//Ask players to input their names
    bool ok;
    for(int i = 0; i < numOfPlayers; i++){
        QString name = QInputDialog::getText(
                    this, QString("Name input"), QString("Enter your name:"), QLineEdit::Normal,
                    QString::null, &ok
                    );
        if(ok && !name.isEmpty())
            names.push_back(name.toStdString());
        else
            i--;
    }
}

void MainWindow::createDockWindows()
{
    // initialize dock widget
    QDockWidget *dock = new QDockWidget(tr("Game"), this);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea |
                          Qt::RightDockWidgetArea  |
                          Qt::LeftDockWidgetArea );

    // init widgets
    bottom_dock = new QWidget();
    buy_button = new QPushButton(tr("Buy"), this);
    roll_button = new QPushButton(tr("Roll"), this);
    upgrade_button = new QPushButton(tr("Upgrade"), this);

    // adding widgets to horizontal layout
    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addWidget(buy_button);
    h_layout->addWidget(roll_button);
    h_layout->addWidget(upgrade_button);

    // set layout for bottom dock area widget
    bottom_dock->setLayout(h_layout);

    // set & add bottom dock widget
    dock->setWidget(bottom_dock);
    addDockWidget(Qt::BottomDockWidgetArea, dock);

    // init widgets
    right_dock = new QWidget(this);
    description = new QListWidget(this);
    die_1 = new QLabel(this);
	die_2 = new QLabel(this);
	dice_widget = new QWidget(this);
	die_1->setPixmap(QPixmap("./images/die0.png"));
	die_2->setPixmap(QPixmap("./images/die0.png"));

	QHBoxLayout *dice_layout = new QHBoxLayout();
	dice_layout->addWidget(die_1);
	dice_layout->addWidget(die_2);

	dice_widget->setLayout(dice_layout);
	
    // adding widgets to vertical layout
    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addWidget(description);
    v_layout->addWidget(dice_widget);

    // set layout for right dock area widget
    right_dock->setLayout(v_layout);

    // set & add right dock widget
    dock = new QDockWidget("Info", this);
    dock->setWidget(right_dock);

    addDockWidget(Qt::RightDockWidgetArea, dock);

    // left dock area
    // init widgets
    left_dock = new QWidget();

    players_widget = new QTabWidget();
	std::vector<Player*> players;
	players = game->getPlayers();	

	QLabel *tab;
	int i = 0;
	while(i < numOfPlayers) {
		tab = new QLabel();
		tab->setText(QString("Name: " + QString::fromStdString(players[i]->get_name()) 
							// TODO: banka jos ne da novce 
							// + "\nMoney: " + QString::number(players[0]->balance().first)
							// + "\nProperty value: " + QString::number(players[0]->balance().second)
					));
		tab->setAlignment(Qt::AlignTop);

		player_tabs.push_back(tab);
		++i;
	}

	for (int i = 0; i < numOfPlayers; i++) {
		players_widget->addTab(player_tabs[i], QString::fromStdString(players[i]->get_name()));
	}

    // set layout
    QVBoxLayout *v_layout2 = new QVBoxLayout();
    v_layout2->addWidget(players_widget);

    // set & add left dock widget
    left_dock->setLayout(v_layout2);
    dock = new QDockWidget("Players", this);
    dock->setWidget(left_dock);

    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

// roll dice -> move player -> do specific action depending on the current position
void MainWindow::roll_dice()
{
	std::pair<int, int> dice = game->throwDice();

	die_1->setPixmap(*(die_sides[dice.first]));
	die_2->setPixmap(*(die_sides[dice.second]));

	game->movePlayer(game->getCurrentPlayer(), dice.first+dice.second);

	Space* curr_space = game->getCurrentPlayerSpace();
	Player* curr_player = game->getCurrentPlayer();

	// if space is not action space and is not owned
	if (curr_space->getType() != "ACTION SPACE" && !curr_space->isOwned()) {
		// display message
		QMessageBox buy_msg;
		buy_msg.setWindowTitle(QString::fromStdString(curr_space->getName()));
		buy_msg.setText("Do you want to buy this " + QString::fromStdString(curr_space->getType()) + "?");
		QPushButton *yesButton = buy_msg.addButton(QMessageBox::Yes);
		QPushButton *noButton = buy_msg.addButton(QMessageBox::No);
		buy_msg.exec();

		if (buy_msg.clickedButton() == yesButton) {
			game->getBank()->sellSpace(curr_player, curr_space);
		}
	} else if (curr_space->getType() == "PROPERTY" && curr_space->isOwned()) {
		// TODO: current player: pay rent or upgrade
		game->pay_rent(curr_space, curr_player);
	} else if (curr_space->getType() == "ACTION SPACE") {
		// TODO: do action on player
	} 

	// if player got dice with different sides, switch to next player
	if (dice.first != dice.second) {
		game->nextPlayer();
	}
}
