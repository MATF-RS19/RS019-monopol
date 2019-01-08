#include <QtWidgets>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <iostream>

#include "mainwindow.h"
#include "Game.hpp"

int numOfPlayers;
Game* MainWindow::game;
std::vector<Space*> MainWindow::spaces;
std::vector<Player*> MainWindow::playersTest;

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
	spaces = game->getBoard()->getSpaces();

    //Create model for players
    players_model = new QStandardItemModel(this);

    //Populate model for players
    playersTest = game->getPlayers();

    /*
    int playerModelPos = 0;
    foreach(const auto& p, playersTest){
        QStandardItem *playerItem = new QStandardItem();
        QVariant v_data;
        v_data.setValue(p->get_wallet());
        playerItem->setData(v_data);
        //playerItem->setText(QString("Current balance:\n" + QString::number(p->get_wallet())));

        players_model->setItem(playerModelPos,playerItem);

    }
    */

    //Create model for all spaces on the board
    model = new QStandardItemModel(11,11);
    int img_num = 0;
    //Populate model with space images
    int i=10,j=10,i_increment=0,j_increment=-1;
        foreach(const auto& s, spaces){

            QStandardItem *spaceItem = new QStandardItem();
	    QVariant v_data;
	    v_data.setValue(s);
            spaceItem->setData(v_data);
            //QBrush *qb = new QBrush(QImage("/images/property1.jpg"));
            //spaceItem->setForeground(*qb);
            //spaceItem->setBackground(QBrush(QPixmap::fromImage(image)));

            QString filename = "./images/image" + QString::number(img_num) + ".png";
            img_num++;
			if ((i==10 && j==10) || (i==10 && j==0) || (i==0 && j==10) || (i==0 && j==0)) {
	            spaceItem->setSizeHint(QSize(100,100));
			} else if (j==10 || j==0) {
				spaceItem->setSizeHint(QSize(100, 60));
			} else {
				spaceItem->setSizeHint(QSize(60, 100));
			}

			
			
	        spaceItem->setIcon(QIcon(filename));

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
		
		for (int i=1; i<10; i++) {
			for (int j=1; j<10; j++) {
				QStandardItem *item = new QStandardItem();
				item->setFlags(Qt::NoItemFlags);
				model->setItem(i,j,item);
			}
		}

    view = new QTableView();
    view->setModel(model);
    view->resize(500, 500);
    view->setStyleSheet("selection-background-color : red;");
    view->setSortingEnabled(false);
    view->resizeColumnsToContents();
    view->resizeRowsToContents();

    view->setIconSize(QSize(100,100));

    setCentralWidget(view);
    createDockWindows();
	setWindowState(Qt::WindowMaximized);

	connect(roll_button, SIGNAL(clicked(bool)),
			this, SLOT(roll_dice()));

	connect(view, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(display_cell(const QModelIndex&)));

	connect(upgrade_button, SIGNAL(clicked(bool)),
			this, SLOT(upgrade_property()));

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
	QDockWidget* dock = new QDockWidget(tr("Info"), this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea  |
                          Qt::LeftDockWidgetArea );

    // init widgets for right dock widget
    right_dock = new QWidget(this);
	roll_button = new QPushButton(tr("Roll"), right_dock);
	upgrade_button = new QPushButton(tr("Upgrade"), right_dock);
	upgrade_button->setVisible(false);
    infoText = new QTextEdit(right_dock);
    die_1 = new QLabel(right_dock);
	die_2 = new QLabel(right_dock);
	dice_widget = new QWidget(right_dock);
    die_1->setPixmap(QPixmap("./images/die0.png"));
    die_2->setPixmap(QPixmap("./images/die0.png"));

	QHBoxLayout *dice_layout = new QHBoxLayout(right_dock);
	dice_layout->addWidget(die_1);
	dice_layout->addWidget(die_2);

	dice_widget->setLayout(dice_layout);
	
    // adding widgets to vertical layout
    right_dock_layout = new QVBoxLayout();
	right_dock_layout->addWidget(infoText);
	right_dock_layout->addWidget(upgrade_button);
    right_dock_layout->addWidget(dice_widget);
	right_dock_layout->addWidget(roll_button);

    // set layout for right dock area widget
    right_dock->setLayout(right_dock_layout);

    //infoText->setText()
    int row = view->selectionModel()->currentIndex().row();
    int col = view->selectionModel()->currentIndex().column();

    std::cout << "ROW " << row << " COL " << col << std::endl;
    infoText->setReadOnly(true);

    dock->setWidget(right_dock);

    addDockWidget(Qt::RightDockWidgetArea, dock);

    // left dock area
    // init widgets
    left_dock = new QWidget(this);

    players_widget = new QTabWidget(left_dock);
    std::vector<Player*> players;
    players = game->getPlayers();

	QLabel *tab;

	int i = 0;
	while(i < numOfPlayers) {
        tab = new QLabel(left_dock);
        //tab->setText(QString("Name: " + QString::fromStdString(players[i]->get_name())+
         //                    "\nCurrent balance: " + QString::number(players[i]->get_wallet())));
							// TODO: banka jos ne da novce 
							// + "\nMoney: " + QString::number(players[0]->balance().first)
							// + "\nProperty value: " + QString::number(players[0]->balance().second)

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

    Player* curr_player = game->getCurrentPlayer();
    std::cout << "Before" << curr_player->get_pos() << std::endl;

    game->movePlayer(curr_player, dice.first+dice.second);

	Space* curr_space = game->getCurrentPlayerSpace();

    std::cout << curr_space->getName() << std::endl;

    std::cout << curr_player->get_pos() << std::endl;


    std::pair<int, int> matrixCoordinates = game->getMatrixAtPos(curr_player->get_pos());
    std::cout << matrixCoordinates.first << ", " << matrixCoordinates.second << std::endl;
    QModelIndex index = view->model()->index(matrixCoordinates.first,matrixCoordinates.second);
    view->setCurrentIndex(index);

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
            std::cout << "Old owner: " << curr_space->getOwner() << std::endl;
            std::cout << "Money before: " << curr_player->get_wallet() << std::endl;
			game->getBank()->sellSpace(curr_player, curr_space);
            std::cout << "New owner: " << curr_space->getOwner() << std::endl;
            std::cout << "Money after: " << curr_player->get_wallet() << std::endl;
            int index = curr_player->getId();

            std::string owned_spaces;
            foreach(const auto& i, curr_player->get_spaces()){
                owned_spaces += i->getName() + "\n";
            }

            //TODO: initialize these tabs and add if player is in jail,
            //has get out of jail free card etc...
            player_tabs.at(index-1)->setText("Current balance: \n"
                                             + QString::number(curr_player->get_wallet())
                                             + "Owned spaces: \n"
                                             + QString::fromStdString(owned_spaces));


		}
    } else if (curr_space->getType() != "ACTION SPACE" && curr_space->isOwned()) {

		if(curr_space->getOwner() == curr_player->getId()) {
			upgrade_button->setVisible(true);
        }else{
            double amt = game->pay_rent(curr_space);
			//TODO: ako je bankrotirao, prelaz na sledeceg igraca
            QMessageBox rent_msg;
            rent_msg.setWindowTitle("PAY RENT");

            rent_msg.setText("You have to pay $" + QString::number(amt) + " to "
                             + QString::fromStdString(playersTest.at(curr_space->getOwner())->get_name()));
            rent_msg.exec();
        }
	} else if (curr_space->getType() == "ACTION SPACE") {
        curr_space->doAction(curr_player);
	} 

	// if player got dice with different sides, switch to next player
	if (dice.first != dice.second) {
		game->nextPlayer();
	}

}

void MainWindow::display_cell(const QModelIndex& index)
{
	if (index.isValid()) {
		if (index.row()>0 && index.row()<10 && index.column()>0 && index.column()<10) {
			return;
		}
		QVariant test = index.data();
		std::string test_string = index.data(Qt::UserRole+1).value<Space*>()->getInfo();
		infoText->setText(QString::fromStdString(test_string));
	} else {
		return;
	}
}

void MainWindow::upgrade_property()
{
	Player* curr_player = game->getCurrentPlayer();
	Space* curr_space = game->getCurrentPlayerSpace();

	game->build(curr_player, curr_space);
}
