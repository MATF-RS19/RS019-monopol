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

	for (int i=1; i<7; i++) {
	    die_sides[i] = new QPixmap("./images/die" + QString::number(i) + ".png");
	}

    //Create game for selected number of players
    game = new Game(names);

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

		// initializing item for the model
        QStandardItem *spaceItem = new QStandardItem();
		QVariant v_data;
		v_data.setValue(s);
        spaceItem->setData(v_data);

		if ((i==10 && j==10) || (i==10 && j==0) || (i==0 && j==10) || (i==0 && j==0)) {
	        spaceItem->setSizeHint(QSize(100,100));
		} else if (j==10 || j==0) {
			spaceItem->setSizeHint(QSize(100, 60));
		} else {
			spaceItem->setSizeHint(QSize(60, 100));
		}

		// setting cell icon (space on the board)
        QString filename = "./images/image" + QString::number(img_num) + ".png";
	    spaceItem->setIcon(QIcon(filename));

		// setting item in the model
        model->setItem(i,j,spaceItem);

        img_num++;
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
    view->setStyleSheet("selection-background-color : red; border-style: none;");
    view->setSortingEnabled(false);
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    view->verticalHeader()->setVisible(false);
    view->horizontalHeader()->setVisible(false);

    view->setIconSize(QSize(100,100));

    setCentralWidget(view);
    createDockWindows();
	setWindowState(Qt::WindowMaximized);

	connect(roll_button, SIGNAL(clicked(bool)),
			this, SLOT(roll_dice()));

	connect(roll_button, SIGNAL(clicked(bool)),
			this, SLOT(select_tab()));

	connect(view, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(display_cell(const QModelIndex&)));

	connect(upgrade_button, SIGNAL(clicked(bool)),
			this, SLOT(upgrade_property()));

	connect(game_info, SIGNAL(textChanged()),
			this, SLOT(scroll_to_bottom()));
	
    connect(mortgage_button, SIGNAL(clicked(bool)),
            this, SLOT(putUnderMortgage()));

	connect(proceed_button, SIGNAL(clicked(bool)),
			this, SLOT(proceed_action()));

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
	
	// roll dice + move player + check space + ...
	roll_button = new QPushButton(tr("Roll"), right_dock);

	// upgrade button is visible only when current player selects his property
	upgrade_button = new QPushButton(tr("Upgrade"), right_dock);
	upgrade_button->setVisible(false);

    // mortage button is visible only when current player selects his property
    mortgage_button = new QPushButton(tr("Put under mortgage"), right_dock);
    mortgage_button->setVisible(false);

	// displays info for the selected space
    infoText = new QTextEdit(right_dock);

	// "Proceed" button -> visible only when action invokes another action
	proceed_button = new QPushButton(tr("Proceed"), right_dock);
	proceed_button->setVisible(false);

	// display dice
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
    right_dock_layout->addWidget(mortgage_button);
    right_dock_layout->addWidget(dice_widget);
	right_dock_layout->addWidget(proceed_button);
	right_dock_layout->addWidget(roll_button);

    // set layout for right dock area widget
    right_dock->setLayout(right_dock_layout);

    infoText->setReadOnly(true);

	// setting right dock
    dock->setWidget(right_dock);

	// add right dock widget in the main window
    addDockWidget(Qt::RightDockWidgetArea, dock);

    // left dock area
    // init widgets
    left_dock = new QWidget(this);

	
	// initializing game info widget
	game_info = new QTextEdit(left_dock);
	game_info->setText("Welcome!\nIt's " 
					+ QString::fromStdString(game->getCurrentPlayer()->get_name() + "'s turn."));

    players_widget = new QTabWidget(left_dock);
    std::vector<Player*> players;
    players = game->getPlayers();

	QTextEdit *tab;

	// setting widget for every player
	int i = 0;
	while(i < numOfPlayers) {
        tab = new QTextEdit(left_dock);
		tab->setReadOnly(true);
        tab->setText(QString("Current balance: " + QString::number(players[i]->get_wallet())));


		player_tabs.push_back(tab);
		++i;
	}

	// initialize tab for every player
	for (int i = 0; i < numOfPlayers; i++) {
		players_widget->addTab(player_tabs[i], QString::fromStdString(players[i]->get_name()));
	}

    // set layout
    QVBoxLayout *v_layout2 = new QVBoxLayout();
    v_layout2->addWidget(players_widget);
	v_layout2->addWidget(game_info);

    // set & add left dock widget
    left_dock->setLayout(v_layout2);
    dock = new QDockWidget("Players", this);
    dock->setWidget(left_dock);

	// add left dock widget in the main window
    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void MainWindow::select_tab() {
	players_widget->setCurrentIndex(game->getCurrentPlayer()->getId()-1);
}

// roll dice -> move player -> do specific action depending on the current position
void MainWindow::roll_dice()
{
//	std::pair<int, int> dice = game->throwDice();
	game->throwDice();

	std::pair<int, int> dice = game->getDice();
	die_1->setPixmap(*(die_sides[dice.first]));
	die_2->setPixmap(*(die_sides[dice.second]));
	game_info->append("- " + QString::fromStdString(game->getCurrentPlayer()->get_name()) + " rolled a " 
						+ QString::number(dice.first) + " and a " + QString::number(dice.second) + ".");

    Player* curr_player = game->getCurrentPlayer();

    game->movePlayer(curr_player, dice.first+dice.second);
	reactToField();
	display_tabs();

	// SLOT method proceed_action will do the rest
	if (proceed_button->isVisible()) {
		return;
	}

	infoText->setText(QString());
	// if player got dice with different sides, switch to next player
	if (dice.first != dice.second) {
		game->nextPlayer();
		game_info->append("- It's " + QString::fromStdString(game->getCurrentPlayer()->get_name() + "'s turn."));
	}
}

void MainWindow::scroll_to_bottom()
{
	game_info->verticalScrollBar()->setValue(game_info->verticalScrollBar()->maximum());
	return;
}

void MainWindow::proceed_action()
{
	proceed_button->setVisible(false);
	Player* p = game->getCurrentPlayer(); 
	if(p->is_in_jail()) 
	{ 
		p->set_num_turns(p->get_num_turns()+1); 
		return; 
	}
	reactToField();
	if (game->getDice().first != game->getDice().second) {
		game->nextPlayer();
		game_info->append("- It's " + QString::fromStdString(game->getCurrentPlayer()->get_name() + "'s turn."));
	}
	roll_button->setVisible(true);
}

void MainWindow::display_tabs()
{
	Player* curr_player = game->getCurrentPlayer();
	int index = curr_player->getId();

    std::string owned_spaces;
    foreach(const auto& i, curr_player->get_spaces()){
        owned_spaces += "    ->" + i->getName() + "\n";
    }

	player_tabs.at(index-1)->setText("Current balance: \n"
                                             + QString::number(curr_player->get_wallet())
                                             + "\nOwned spaces: \n"
                                             + QString::fromStdString(owned_spaces));
}

void MainWindow::reactToField()
{
	Player* curr_player = game->getCurrentPlayer();
	Space* curr_space = game->getCurrentPlayerSpace();

    std::pair<int, int> matrixCoordinates = game->getMatrixAtPos(curr_player->get_pos());

    QModelIndex index = view->model()->index(matrixCoordinates.first,matrixCoordinates.second);
    view->setCurrentIndex(index);

	// if space is not action space and is not owned
	if (curr_space->getType() != "ACTION SPACE" && !curr_space->isOwned()) {
		infoText->setText(QString::fromStdString(curr_space->getInfo()));
		// display message
		QMessageBox buy_msg;
		buy_msg.setWindowTitle(QString::fromStdString(curr_space->getName()));
		double balance = curr_player->balance().first;
		if(balance < curr_space->getBuyPrice())
		{
			std::cout << "You can't afford this." << std::endl;
			return;
		}
		buy_msg.setText("Do you want to buy this " + QString::fromStdString(curr_space->getType()) + "?");
		QPushButton *yesButton = buy_msg.addButton(QMessageBox::Yes);
		QPushButton *noButton = buy_msg.addButton(QMessageBox::No);
		buy_msg.exec();

		if (buy_msg.clickedButton() == yesButton) {
			game->getBank()->sellSpace(curr_player, curr_space);
			game_info->append("~ " + QString::fromStdString(curr_player->get_name())
							  + " bought " + QString::fromStdString(curr_space->getName()));
		}
    } else if (curr_space->getType() != "ACTION SPACE" && curr_space->isOwned()) {
		infoText->setText(QString::fromStdString(curr_space->getInfo()));

		if(curr_space->getOwner() == curr_player->getId()) 
		{
			if (curr_space->getType() == "PROPERTY" 
		   		&& game->getCurrentPlayer()->check_properties(curr_space)) {

				upgrade_button->setVisible(true);
			}
        }else{
            double amt = game->pay_rent(curr_space);
            QMessageBox rent_msg;
            rent_msg.setWindowTitle("PAY RENT");

			QString owner;
			owner = QString::fromStdString(playersTest.at(curr_space->getOwner()-1)->get_name());
            rent_msg.setText("You have to pay $" + QString::number(amt) + " to "
                             + owner);
            rent_msg.exec();

			game_info->append(owner + " received rent from " + QString::fromStdString(curr_player->get_name()) + ".");
        }
	} else if (curr_space->getType() == "ACTION SPACE") {
		// action space is not upgradable
		if (upgrade_button->isVisible()) {
			upgrade_button->setVisible(false);
		}

		ActionSpace* curr_act_space = (ActionSpace*)curr_space;
        std::string action = curr_act_space->getSpaceAction();

//		game_info->append(QString::fromStdString(curr_act_space->))

		if(action == "GO")
		{
			game_info->append("* " + QString::fromStdString(curr_player->get_name()) + " passed GO.\n"
							  + "  " + QString::fromStdString(curr_player->get_name()) + " receives 200$.");
			game->getBank()->giveMoney(curr_player, 200);
		}
		else if(action == "GOTO_JAIL")
		{
			game_info->append("* " + QString::fromStdString(curr_player->get_name()) + " goes to jail.");
			game->send_to_jail(curr_player);
		}
		else if(action == "INCOME_TAX")
		{
			if(curr_player->balance().first < 200.0)
			{
				std::vector<Player*> players = game->getPlayers();
				curr_player->set_bankrupt();
				Player* pTemp = curr_player;
				curr_player = players.at(curr_player->getId());
				delete pTemp;
				return;
			}
			game_info->append("* " + QString::fromStdString(curr_player->get_name()) + " pays income tax (200$).");
			game->getBank()->takeMoney(curr_player, 200);
		}
		else if(action == "LUXURY_TAX")
		{
			if(curr_player->balance().first < 75.0)
			{
				std::vector<Player*> players = game->getPlayers();
				curr_player->set_bankrupt();
				Player* pTemp = curr_player;
				curr_player = players.at(curr_player->getId());
				delete pTemp;
				return;
			}
			game_info->append("* " + QString::fromStdString(curr_player->get_name()) + " pays luxury tax (75%).");
			game->getBank()->takeMoney(curr_player, 75);
		}
		else if(action == "CHANCE")
		{
			Card chance = game->getBoard()->drawChanceCard();
			int num_card = chance.getAction();
			if(num_card == 0)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				game->moveToPos(curr_player, 0);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 1)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				// if they pass go, they get $200
				if(curr_player->get_pos() > 24)
					game->getBank()->giveMoney(curr_player, 200);
				// Illinos Avenue
				game->moveToPos(curr_player, 24);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 2)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				// if they pass go, they get $200
				if(curr_player->get_pos() > 11)
					game->getBank()->giveMoney(curr_player, 200);
				// St. Charles Place
				game->moveToPos(curr_player, 11);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 3)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				int electric_distance = abs(12-curr_player->get_pos());
				int water_distance = abs(28-curr_player->get_pos());
				int nearest;
				if(electric_distance <= water_distance)
					nearest = 12;
				else
					nearest = 28;
				// nearest utility
				game->moveToPos(curr_player, nearest);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 4)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				int quotient = curr_player->get_pos() / 10;
				int move_to = quotient * 10 + 5;
				// nearest railroad
				game->moveToPos(curr_player, move_to);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 5)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				int quotient = curr_player->get_pos() / 10;
				int move_to = quotient * 10 + 5;
				// nearest railroad
				game->moveToPos(curr_player, move_to);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 6)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				game->getBank()->giveMoney(curr_player, 50);
			}
			else if(num_card == 7)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				if(curr_player->is_in_jail())
					game->release_from_jail(curr_player);
				else
					game->give_jail_card(curr_player);
			}
			else if(num_card == 8)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				int current = curr_player->get_pos();
				if(current == 0)
					game->moveToPos(curr_player, 37);
				else if(current == 1)
					game->moveToPos(curr_player, 38);
				else if(current == 2)
					game->moveToPos(curr_player, 39);
				else 
					game->moveToPos(curr_player, current-3);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 9)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				// placing him at the go to jail action field for a moment
				game->moveToPos(curr_player, 30);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 10)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				std::vector<Property*> props = curr_player->get_properties();
				unsigned size = props.size();
				int num = 0;
				for(unsigned i=0; i<size; i++)
					num += props[i]->getNumBuildings();
	
				game->getBank()->takeMoney(curr_player, num*25);
			}
			else if(num_card == 11)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				game->getBank()->takeMoney(curr_player, 15);
			}
			else if(num_card == 12)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				if(curr_player->get_pos() > 5)
					game->getBank()->giveMoney(curr_player, 200);
				// Reading Railroad
				game->moveToPos(curr_player, 5);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 13)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				// Boardwalk
				game->moveToPos(curr_player, 39);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 14)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				std::vector<Player*> players = game->getPlayers();
				game->getBank()->takeMoney(curr_player, 50*(numOfPlayers-1));
				for(int i=0; i<numOfPlayers; i++)
				{
					if(players[i] != curr_player)
						game->getBank()->giveMoney(players[i], 50);
				}
			}
			else if(num_card == 15)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				game->getBank()->giveMoney(curr_player, 150);
			}
			else if(num_card == 16)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				game->getBank()->giveMoney(curr_player, 100);
			}
		}
		else if(action == "COMMUNITY_CHEST")
		{
			Card chest = game->getBoard()->drawCommunityCard();
			int num_card = chest.getAction();
			if(num_card == 17)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->moveToPos(curr_player, 0);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 18)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->giveMoney(curr_player, 200);
			}
			else if(num_card == 19)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->takeMoney(curr_player, 50);
			}
			else if(num_card == 20)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->giveMoney(curr_player, 50);
			}
			else if(num_card == 21)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				if(curr_player->is_in_jail())
					game->release_from_jail(curr_player);
				else
					game->give_jail_card(curr_player);
			}
			else if(num_card == 22)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				std::vector<Player*> players = game->getPlayers();
				game->getBank()->takeMoney(curr_player, 50*(numOfPlayers-1));
				for(int i=0; i<numOfPlayers; i++)
				{
					if(players[i] != curr_player)
						game->getBank()->giveMoney(players[i], 50);
				}
			}
			else if(num_card == 23)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->giveMoney(curr_player, 100);
			}
			else if(num_card == 24)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->giveMoney(curr_player, 20);
			}
			else if(num_card == 25)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				std::vector<Player*> players = game->getPlayers();
				game->getBank()->giveMoney(curr_player, 10*(numOfPlayers-1));
				for(int i=0; i<numOfPlayers; i++)
				{
					if(players[i] != curr_player)
						game->getBank()->takeMoney(players[i], 10);
				}
			}
			else if(num_card == 26)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->giveMoney(curr_player, 100);
			}
			else if(num_card == 27)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->takeMoney(curr_player, 50);
			}
			else if(num_card == 28)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->takeMoney(curr_player, 50);
			}
			else if(num_card == 29)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->giveMoney(curr_player, 25);
			}
			else if(num_card == 30)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				std::vector<Property*> props = curr_player->get_properties();
				unsigned size = props.size();
				int num = 0;
				int num_h = 0;
				double total = 0;
				for(unsigned i=0; i<size; i++)
				{
					int num_h = props[i]->getNumBuildings();
					if(num_h == 5)
						total += 115;
					else
						num += num_h;
				}		
				game->getBank()->takeMoney(curr_player, num * 40 + total);
			}
			else if(num_card == 31)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->giveMoney(curr_player, 10);
			}
			else if(num_card == 32)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				game->getBank()->giveMoney(curr_player, 100);
			}
		}
	} 
}

void MainWindow::display_cell(const QModelIndex& index)
{
	if (index.isValid()) {
		if (index.row()>0 && index.row()<10 && index.column()>0 && index.column()<10) {
			return;
		}
		QVariant data = index.data(Qt::UserRole+1);

        //HACK: set global selection var
        currentSelection = data;

		std::string test_string = data.value<Space*>()->getInfo();
		infoText->setText(QString::fromStdString(test_string));

        if (data.value<Space*>()->getOwner() == game->getCurrentPlayer()->getId()
            && data.value<Space*>()->getType() == "PROPERTY" && game->getCurrentPlayer()->check_properties(data.value<Space*>())) {
			upgrade_button->setVisible(true);
		} else {
			upgrade_button->setVisible(false);
		}

        if (data.value<Space*>()->getOwner() == game->getCurrentPlayer()->getId()){
            mortgage_button->setVisible(true);
        } else {
            mortgage_button->setVisible(false);
        }

	} else {
		return;
	}
}

//TODO: implement me
void MainWindow::putUnderMortgage(){
    return;
}

//FIXME: doesn't allow player to upgrade more than once, don't know why
void MainWindow::upgrade_property()
{


    Space* upgradeMe = currentSelection.value<Space*>();
    Player* curr_player = game->getCurrentPlayer();

    game->build(curr_player, upgradeMe);
}
