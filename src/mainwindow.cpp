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

	connect(game_info, SIGNAL(textChanged()),
			this, SLOT(scroll_to_bottom()));
	
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
    right_dock_layout->addWidget(dice_widget);
	right_dock_layout->addWidget(proceed_button);
	right_dock_layout->addWidget(roll_button);

    // set layout for right dock area widget
    right_dock->setLayout(right_dock_layout);

    //infoText->setText()
    int row = view->selectionModel()->currentIndex().row();
    int col = view->selectionModel()->currentIndex().column();

    std::cout << "ROW " << row << " COL " << col << std::endl;
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
	game_info->setText("Welcome!\nIt's" 
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
							// TODO: banka jos ne da novce 
							// + "\nMoney: " + QString::number(players[0]->balance().first)
							// + "\nProperty value: " + QString::number(players[0]->balance().second)

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

// roll dice -> move player -> do specific action depending on the current position
void MainWindow::roll_dice()
{
	std::pair<int, int> dice = game->throwDice();

	die_1->setPixmap(*(die_sides[dice.first]));
	die_2->setPixmap(*(die_sides[dice.second]));
	game_info->append("- " + QString::fromStdString(game->getCurrentPlayer()->get_name()) + " rolled a " 
						+ QString::number(dice.first) + " and a " + QString::number(dice.second) + ".");

    Player* curr_player = game->getCurrentPlayer();
    std::cout << "Before" << curr_player->get_pos() << std::endl;

    game->movePlayer(curr_player, dice.first+dice.second);
	reactToField();
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
	reactToField();
	roll_button->setVisible(true);
}

void MainWindow::reactToField()
{
	Player* curr_player = game->getCurrentPlayer();
	Space* curr_space = game->getCurrentPlayerSpace();

    std::cout << curr_space->getName() << std::endl;

    std::cout << curr_player->get_pos() << std::endl;


    std::pair<int, int> matrixCoordinates = game->getMatrixAtPos(curr_player->get_pos());
    std::cout << matrixCoordinates.first << ", " << matrixCoordinates.second << std::endl;
    QModelIndex index = view->model()->index(matrixCoordinates.first,matrixCoordinates.second);
    view->setCurrentIndex(index);

	// if space is not action space and is not owned
	if (curr_space->getType() != "ACTION SPACE" && !curr_space->isOwned()) {
		infoText->setText(QString::fromStdString(curr_space->getInfo()));
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
			game_info->append("~ " + QString::fromStdString(curr_player->get_name())
							  + " bought " + QString::fromStdString(curr_space->getName()));

            std::cout << "New owner: " << curr_space->getOwner() << std::endl;
            std::cout << "Money after: " << curr_player->get_wallet() << std::endl;
            int index = curr_player->getId();

            std::string owned_spaces;
            foreach(const auto& i, curr_player->get_spaces()){
                owned_spaces += "    ->" + i->getName() + "\n";
            }

            //TODO: initialize these tabs and add if player is in jail,
            //has get out of jail free card etc...
            player_tabs.at(index-1)->setText("Current balance: \n"
                                             + QString::number(curr_player->get_wallet())
                                             + "\nOwned spaces: \n"
                                             + QString::fromStdString(owned_spaces));
		}
    } else if (curr_space->getType() != "ACTION SPACE" && curr_space->isOwned()) {
		infoText->setText(QString::fromStdString(curr_space->getInfo()));

		if(curr_space->getOwner() == curr_player->getId()) {
			upgrade_button->setVisible(true);
        }else{
            double amt = game->pay_rent(curr_space);
			//TODO: ako je bankrotirao, prelaz na sledeceg igraca
            QMessageBox rent_msg;
            rent_msg.setWindowTitle("PAY RENT");

            rent_msg.setText("You have to pay $" + QString::number(amt) + " to "
                             + QString::fromStdString(playersTest.at(curr_space->getOwner()-1)->get_name()));
            rent_msg.exec();
        }
	} else if (curr_space->getType() == "ACTION SPACE") {
		// action space is not upgradeable
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
			curr_player->receive(200.0);
		}
		else if(action == "GOTO_JAIL")
		{
			game_info->append("* " + QString::fromStdString(curr_player->get_name()) + " goes to jail.");
			curr_player->send_to_jail();
			curr_player->set_num_turns(1);
		}
		else if(action == "INCOME_TAX")
		{
			game_info->append("* " + QString::fromStdString(curr_player->get_name()) + " pays income tax (200$).");
			curr_player->pay(200.0);
		}
		else if(action == "LUXURY_TAX")
		{
			game_info->append("* " + QString::fromStdString(curr_player->get_name()) + " pays luxury tax (75%).");
			curr_player->pay(75.0);
		}
		else if(action == "CHANCE")
		{
			Card chance = game->getBoard()->drawChanceCard();
			int num_card = chance.getAction();
			if(num_card == 0)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				curr_player->set_pos(0);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 1)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				// if they pass go, they get $200
				if(curr_player->get_pos() > 24)
					curr_player->receive(200.0);
				// Illinos Avenue
				curr_player->set_pos(24);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 2)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				// if they pass go, they get $200
				if(curr_player->get_pos() > 11)
					curr_player->receive(200.0);
				// St. Charles Place
				curr_player->set_pos(11);
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
				curr_player->set_pos(nearest);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 4)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				int quotient = curr_player->get_pos() / 10;
				int move_to = quotient * 10 + 5;
				// nearest railroad
				curr_player->set_pos(move_to);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 5)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				int quotient = curr_player->get_pos() / 10;
				int move_to = quotient * 10 + 5;
				// nearest railroad
				curr_player->set_pos(move_to);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 6)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				curr_player->receive(50.0);
			}
			else if(num_card == 7)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				if(curr_player->is_in_jail())
					curr_player->release_from_jail();
				else
					curr_player->receive_jail_card();
			}
			else if(num_card == 8)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				int current = curr_player->get_pos();
				if(current == 0)
					curr_player->set_pos(37);
				else if(current == 1)
					curr_player->set_pos(38);
				else if(current == 2)
					curr_player->set_pos(39);
				else 
					curr_player->set_pos(current-3);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 9)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				// placing him at the go to jail action field for a moment
				curr_player->set_pos(30);
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
	
				curr_player->pay(num*25.0);
			}
			else if(num_card == 11)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				curr_player->pay(15.0);
			}
			else if(num_card == 12)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				if(curr_player->get_pos() > 5)
					curr_player->receive(200.0);
				// Reading Railroad
				curr_player->set_pos(5);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 13)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				// Boardwalk
				curr_player->set_pos(39);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 14)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				std::vector<Player*> players = game->getPlayers();
				curr_player->pay(50.0*(numOfPlayers-1)); 
				for(int i=0; i<numOfPlayers; i++)
				{
					if(players[i] != curr_player)
						players[i]->receive(50.0);
				}
			}
			else if(num_card == 15)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				curr_player->receive(150.0);
			}
			else if(num_card == 16)
			{
				game_info->append("* Chance: " + QString::fromStdString(chance.getMsg()));
				curr_player->receive(100.0);
			}
		}
		else if(action == "COMMUNITY_CHEST")
		{
			Card chest = game->getBoard()->drawCommunityCard();
			int num_card = chest.getAction();
			if(num_card == 17)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->set_pos(0);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 18)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->receive(200.0);
			}
			else if(num_card == 19)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->pay(50.0);
			}
			else if(num_card == 20)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->receive(50.0);
			}
			else if(num_card == 21)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				if(curr_player->is_in_jail())
					curr_player->release_from_jail();
				else
					curr_player->receive_jail_card();
			}
			else if(num_card == 22)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				std::vector<Player*> players = game->getPlayers();
				curr_player->receive(50.0*(numOfPlayers-1)); 
				for(int i=0; i<numOfPlayers; i++)
				{
					if(players[i] != curr_player)
						players[i]->pay(50.0);
				}
			}
			else if(num_card == 23)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->receive(100.0);
			}
			else if(num_card == 24)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->receive(20.0);
			}
			else if(num_card == 25)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				std::vector<Player*> players = game->getPlayers();
				curr_player->receive(10.0*(numOfPlayers-1)); 
				for(int i=0; i<numOfPlayers; i++)
				{
					if(players[i] != curr_player)
						players[i]->pay(10.0);
				}
			}
			else if(num_card == 26)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->receive(100.0);
			}
			else if(num_card == 27)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->pay(50.0);
			}
			else if(num_card == 28)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->pay(50.0);
			}
			else if(num_card == 29)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->receive(25.0);
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
				curr_player->pay(num * 40.0 + total);
			}
			else if(num_card == 31)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->receive(10.0);
			}
			else if(num_card == 32)
			{
				game_info->append("* Community chest:" + QString::fromStdString(chest.getMsg()));
				curr_player->receive(100.0);
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
		std::string test_string = data.value<Space*>()->getInfo();
		infoText->setText(QString::fromStdString(test_string));

		if (data.value<Space*>()->getOwner() == game->getCurrentPlayerSpace()->getOwner()
			&& game->getCurrentPlayerSpace()->getType() == "PROPERTY") {
			upgrade_button->setVisible(true);
		} else {
			upgrade_button->setVisible(false);
		}
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
