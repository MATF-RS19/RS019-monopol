#include <QtWidgets>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <iostream>

#include "mainwindow.h"
#include "Game.hpp"
#include "HandleXML.h"

int numOfPlayers;
Game* MainWindow::game;
std::vector<Space*> MainWindow::spaces;
std::vector<Player*> MainWindow::playersTest;

MainWindow::MainWindow()
{
    //Create vector of names
    std::vector<std::string> names(numOfPlayers);
	
	mainMenu(names);

    createActions();
    createMenus();

	for (int i=1; i<7; i++) {
	    die_sides[i] = new QPixmap("./images/die" + QString::number(i) + ".png");
	}

    //Create game for selected number of players
    game = new Game(names);

    //Get spaces
	spaces = game->getBoard()->getSpaces();

    //Populate model for players
    playersTest = game->getPlayers();

    updateModel();

    qDebug() << "Entering view setup";
	// setting view
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

	// add view to central widget and create dock widgets
    setCentralWidget(view);
    createDockWindows();
	setWindowState(Qt::WindowMaximized);

	// set up connection to buttons in GUI
	// "Roll" button clicked -> roll_dice function is called
	connect(roll_button, SIGNAL(clicked(bool)),
			this, SLOT(roll_dice()));

	// "Roll" button clicked -> set tab to current player
	connect(roll_button, SIGNAL(clicked(bool)),
			this, SLOT(select_tab()));

	// space on the board clicked -> display space info
	connect(view, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(display_cell(const QModelIndex&)));

	// "Upgrade" button clicked -> build on the property
	connect(upgrade_button, SIGNAL(clicked(bool)),
			this, SLOT(upgrade_property()));

    connect(sell_house_button, SIGNAL(clicked(bool)),
            this, SLOT(sell_house()));

	// when the text in game_info is changed, scroll (if necessary) to bottom 
	connect(game_info, SIGNAL(textChanged()),
			this, SLOT(scroll_to_bottom()));
	
	// "Mortgage" button clicked -> put property under mortgage
    connect(mortgage_button, SIGNAL(clicked(bool)),
            this, SLOT(putUnderMortgage()));

	// "Proceed" button clicked -> proceed with action
	connect(proceed_button, SIGNAL(clicked(bool)),
			this, SLOT(proceed_action()));

}

void MainWindow::updateModel(){
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
        spaceItem->setEditable(false);

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
}

void MainWindow::createActions(){
    loadAct = new QAction(tr("&Load game"), this);
    loadAct->setStatusTip(tr("Load game from a file"));
    connect(loadAct, &QAction::triggered, this, &MainWindow::loadGame);

    saveAct = new QAction(tr("&Save game"), this);
    saveAct->setStatusTip(tr("Save game to a file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveGame);
}

void MainWindow::createMenus(){
    loadSaveMenu = menuBar()->addMenu(tr("&Load/Save"));
    loadSaveMenu->addAction(loadAct);
    loadSaveMenu->addAction(saveAct);
}

void MainWindow::handleBadXML(){
    QMessageBox *error = new QMessageBox;
    error->setText("XML file is corrupted");
    error->exec();
}

void MainWindow::load(const QString& fileName){

    HandleXML loader(fileName, HandleXML::XMLMode::LOAD);

    bool ok;
    std::vector<Player*> loadedPlayers = loader.processPlayers(ok);

    if(ok){
        delete game;
        numOfPlayers = loadedPlayers.size();

        game = new Game(loadedPlayers, loader.board(), loader.bank());
        playersTest = game->getPlayers();
        spaces = game->getBoard()->getSpaces();
        qDebug() << "Spaces size" <<spaces.size();
        qDebug() << QString::fromStdString(spaces.at(9)->getName());
        qDebug() << QString::number(spaces.at(9)->getOwner());

        updateModel();
        view->setModel(model);
        view->update();

        game_info->clear();
        infoText->clear();
        player_tabs.clear();
        updateTabs(loadedPlayers);
    } else {
        QMessageBox *error = new QMessageBox;
        error->setWindowTitle("Error!");
        error->setText("Loading from file failed : bad XML file!");
        error->exec();
    }



}

void MainWindow::save(const QString& fileName){

    HandleXML saver(fileName,HandleXML::XMLMode::SAVE);

    saver.saveGame(game);
}

void MainWindow::loadGame(){
    qDebug() << "load invoked";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load from file"),
                                                    "./saves",
                                                    tr("(*.xml)"));

    if(!fileName.isNull()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Warning", "Are you sure? (Current game will be lost)",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Save);

        switch (reply) {
            case QMessageBox::Yes:
                qDebug() << "yes";
                load(fileName);
                break;
            case QMessageBox::No:
                qDebug() << "no";
                break;
            case QMessageBox::Save:
                qDebug() << "save";
                saveGame();
                loadGame();
                break;
            default:
                break;

        }
    }

    qDebug() << fileName << " selected";
}

void MainWindow::saveGame(){
    qDebug() << "save invoked";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save to a file"),
                                                    ".", tr("(*.xml)"));

    // Overwrite is automaticaly handled -> if 'yes' is clicked, file will be overwritten
    // else, null will be returned as fileName
    save(fileName);

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

void MainWindow::updateTabs(std::vector<Player*> players){

    QTextEdit *tab;

    players_widget->clear();

    std::string owned_spaces;

    int i = 0;
    while(i < numOfPlayers) {
        qDebug() << "Player wallet" << QString::number(players[i]->get_wallet());
        tab = new QTextEdit(left_dock);
        tab->setReadOnly(true);

        foreach(const auto& i, players.at(i)->get_spaces()){
            owned_spaces += "    ->" + i->getName() + "\n";
        }

        tab->setText(QString("Current balance: " + QString::number(players[i]->get_wallet())) + "\nOwned spaces: \n" + QString::fromStdString(owned_spaces));

        player_tabs.push_back(tab);
        ++i;
        owned_spaces.clear();
    }

    for (int i = 0; i < numOfPlayers; i++) {
        players_widget->addTab(player_tabs[i], QString::fromStdString(players[i]->getName()));
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

    // sell house button is visible only when you own houses to sell
    sell_house_button = new QPushButton(tr("Sell house"), right_dock);
    sell_house_button->setVisible(false);

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
    right_dock_layout->addWidget(sell_house_button);
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
					+ QString::fromStdString(game->getCurrentPlayer()->getName() + "'s turn."));

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
		players_widget->addTab(player_tabs[i], QString::fromStdString(players[i]->getName()));
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

// called when the "Roll" button is clicked
void MainWindow::select_tab() {
    auto iter = std::find_if(playersTest.begin(), playersTest.end(), [&] (Player *p) { return p->getId() == game->getCurrentPlayer()->getId(); });
    auto index = std::distance(playersTest.begin(), iter);
    players_widget->setCurrentIndex(index);
}

// roll dice -> move player -> do specific action depending on the current position
void MainWindow::roll_dice()
{
//	std::pair<int, int> dice = game->throwDice();
	game->throwDice();

	std::pair<int, int> dice = game->getDice();
	die_1->setPixmap(*(die_sides[dice.first]));
	die_2->setPixmap(*(die_sides[dice.second]));
	game_info->append("- " + QString::fromStdString(game->getCurrentPlayer()->getName()) + " rolled a " 
						+ QString::number(dice.first) + " and a " + QString::number(dice.second) + ".");

    Player* curr_player = game->getCurrentPlayer();

    game->movePlayer(curr_player, dice.first+dice.second);
	reactToField();
	display_tabs(); // update tabs for every player

	// SLOT method proceed_action will do the rest
	if (proceed_button->isVisible()) {
		return;
	}

	infoText->setText(QString());
	// if player got dice with different sides, switch to next player
	if (dice.first != dice.second) {
		game->nextPlayer();
		game_info->append("- It's " + QString::fromStdString(game->getCurrentPlayer()->getName() + "'s turn."));
	}
}

// called when the text in game_info is changed
void MainWindow::scroll_to_bottom()
{
	game_info->verticalScrollBar()->setValue(game_info->verticalScrollBar()->maximum());
	return;
}

// called when the "Proceed" button is clicked
void MainWindow::proceed_action()
{
	// show "Proceed" button instead of the "Roll" button
	proceed_button->setVisible(false);
	Player* p = game->getCurrentPlayer(); 

	// if player is in jail, prolong stay for one more turn
	// FIXME: not working?
	/*
	if(p->is_in_jail()) 
	{ 
		p->set_num_turns(p->get_num_turns()+1); 
		return; 
	}
	*/

	reactToField();

	// if player got dice with different sides, switch to next player
	if (game->getDice().first != game->getDice().second) {
		game->nextPlayer();
		game_info->append("- It's " + QString::fromStdString(game->getCurrentPlayer()->getName() + "'s turn."));
	}

	// "Roll" button is visible again
	roll_button->setVisible(true);
}

// function that updates players info
void MainWindow::display_tabs()
{
	Player* curr_player = game->getCurrentPlayer();
    qDebug() << "DISPLAY TABS DEBUG CURR PL = " << QString::fromStdString(curr_player->getName());
    auto iter = std::find_if(playersTest.begin(), playersTest.end(), [&] (Player *p) { return p->getId() == curr_player->getId(); });
    auto index = std::distance(playersTest.begin(), iter);

    std::string owned_spaces;
    foreach(const auto& i, curr_player->get_spaces()){
        owned_spaces += "    ->" + i->getName() + "\n";
    }

    std::string player_tab_info = "Current balance" + std::to_string(curr_player->get_wallet()) + "\nOwned spaces: \n" + owned_spaces;
    player_tabs.at(index)->setText(QString::fromStdString(player_tab_info));
}

void MainWindow::reactToField()
{
	Player* curr_player = game->getCurrentPlayer();
	Space* curr_space = game->getCurrentPlayerSpace();
	QString playerName = QString::fromStdString(curr_player->getName());
	QString spaceName = QString::fromStdString(curr_space->getName());

	// get table coordinates
    std::pair<int, int> matrixCoordinates = game->getMatrixAtPos(curr_player->get_pos());

	// take current index of the table, and set view to that index (that cell is now selected in GUI)
    QModelIndex index = view->model()->index(matrixCoordinates.first,matrixCoordinates.second);
    view->setCurrentIndex(index);

	// You can buy space that's not owned
	if (curr_space->getType() != "ACTION SPACE" && !curr_space->isOwned()) {
		infoText->setText(QString::fromStdString(curr_space->getInfo()));

		QMessageBox buy_msg;
		
		buy_msg.setWindowTitle(spaceName);
		buy_msg.setText("Do you want to buy this " + QString::fromStdString(curr_space->getType()) + "?");
		QPushButton *yesButton = buy_msg.addButton(QMessageBox::Yes);
        QPushButton *noButton = buy_msg.addButton(QMessageBox::No); //TODO: start auction
		buy_msg.exec();

		// Player buys space
		if (buy_msg.clickedButton() == yesButton) {
			if (game->isAffordable(curr_player, curr_space)) {
				game->getBank()->sellSpace(curr_player, curr_space);
				game_info->append("~ " + playerName + " bought " + spaceName);
			} else {
				game_info->append(playerName + " can't afford this. :(");
			}
		}
	// If player stepped on an owned field
    } else if (curr_space->getType() != "ACTION SPACE" && curr_space->isOwned()) {
		infoText->setText(QString::fromStdString(curr_space->getInfo()));

        // You can upgrade your property when you step on it
		if(curr_space->getOwner() == curr_player->getId()) 
		{
			if (curr_space->getType() == "PROPERTY" 
		   		&& game->getCurrentPlayer()->check_properties(curr_space)) {
				upgrade_button->setVisible(true);
            } if(curr_space->getNumBuildings() > 0){
                sell_house_button->setVisible(true);
            }
        }else{ // You have to pay rent to the owner of the current space
            double amt = game->pay_rent(curr_space);
            QMessageBox rent_msg;
            rent_msg.setWindowTitle("PAY RENT");

            //Dangerous, could not work
            if(amt != -1.0){
                QString owner;
                owner = QString::fromStdString(playersTest.at(curr_space->getOwner()-1)->getName());
                rent_msg.setText("You have to pay $" + QString::number(amt) + " to "
                                 + owner);
                rent_msg.exec();
                game_info->append(owner + " received rent from " + playerName + ".");
            }else{
                rent_msg.setText("Space is under mortgage, you don't have to pay");
                rent_msg.exec();
            }


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
			game_info->append("* " + playerName + " passed GO.\n"
							  + "  " + playerName + " receives 200$.");
			game->getBank()->giveMoney(curr_player, 200);
		}
		else if(action == "GOTO_JAIL")
		{
			game_info->append("* " + playerName + " goes to jail.");
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
			game_info->append("* " + playerName + " pays income tax (200$).");
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
			game_info->append("* " + playerName + " pays luxury tax (75%).");
			game->getBank()->takeMoney(curr_player, 75);
		}
		else if(action == "CHANCE")
		{
			Card chance = game->getBoard()->drawChanceCard();
			QString chanceMsg = QString::fromStdString(chance.getMsg());
			int num_card = chance.getAction();
			if(num_card == 0)
			{
				game_info->append("* Chance: " + chanceMsg);
				game->moveToPos(curr_player, 0);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 1)
			{
				game_info->append("* Chance: " + chanceMsg);
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
				game_info->append("* Chance: " + chanceMsg);
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
				game_info->append("* Chance: " + chanceMsg);
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
				game_info->append("* Chance: " + chanceMsg);
				int quotient = curr_player->get_pos() / 10;
				int move_to = quotient * 10 + 5;
				// nearest railroad
				game->moveToPos(curr_player, move_to);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 5)
			{
				game_info->append("* Chance: " + chanceMsg);
				int quotient = curr_player->get_pos() / 10;
				int move_to = quotient * 10 + 5;
				// nearest railroad
				game->moveToPos(curr_player, move_to);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 6)
			{
				game_info->append("* Chance: " + chanceMsg);
				game->getBank()->giveMoney(curr_player, 50);
			}
			else if(num_card == 7)
			{
				game_info->append("* Chance: " + chanceMsg);
				if(curr_player->is_in_jail())
					game->release_from_jail(curr_player);
				else
					game->give_jail_card(curr_player);
			}
			else if(num_card == 8)
			{
				game_info->append("* Chance: " + chanceMsg);
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
				game_info->append("* Chance: " + chanceMsg);
				// placing him at the go to jail action field for a moment
				game->moveToPos(curr_player, 30);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 10)
			{
				game_info->append("* Chance: " + chanceMsg);
				std::vector<Property*> props = curr_player->get_properties();
				unsigned size = props.size();
				int num = 0;
				for(unsigned i=0; i<size; i++)
					num += props[i]->getNumBuildings();
	
				game->getBank()->takeMoney(curr_player, num*25);
			}
			else if(num_card == 11)
			{
				game_info->append("* Chance: " + chanceMsg);
				game->getBank()->takeMoney(curr_player, 15);
			}
			else if(num_card == 12)
			{
				game_info->append("* Chance: " + chanceMsg);
				if(curr_player->get_pos() > 5)
					game->getBank()->giveMoney(curr_player, 200);
				// Reading Railroad
				game->moveToPos(curr_player, 5);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 13)
			{
				game_info->append("* Chance: " + chanceMsg);
				// Boardwalk
				game->moveToPos(curr_player, 39);
				proceed_button->setVisible(true);
				roll_button->setVisible(false);
			}
			else if(num_card == 14)
			{
				game_info->append("* Chance: " + chanceMsg);
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
				game_info->append("* Chance: " + chanceMsg);
				game->getBank()->giveMoney(curr_player, 150);
			}
			else if(num_card == 16)
			{
				game_info->append("* Chance: " + chanceMsg);
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

// called when a cell on the board is clicked
void MainWindow::display_cell(const QModelIndex& index)
{
    updateModel();

	if (index.isValid()) {
		if (index.row()>0 && index.row()<10 && index.column()>0 && index.column()<10) {
			return;
		}
		QVariant data = index.data(Qt::UserRole+1);

        //HACK: set global selection var to allow building, mortgage etc.
        currentSelection = data;

        std::string test_string = data.value<Space*>()->getInfo();
		infoText->setText(QString::fromStdString(test_string));

        if (data.value<Space*>()->getOwner() == game->getCurrentPlayer()->getId() && data.value<Space*>()->getNumBuildings() > 0){
            sell_house_button->setVisible(true);
        } else {
            sell_house_button->setVisible(false);
        }

        if (data.value<Space*>()->getOwner() == game->getCurrentPlayer()->getId()
            && data.value<Space*>()->getType() == "PROPERTY" && game->buildingAllowed(game->getCurrentPlayer(), data.value<Space*>())) {
			upgrade_button->setVisible(true);
        } else {
            qDebug() << "zasto " <<QString::number(data.value<Space*>()->getOwner());
            qDebug() << game->buildingAllowed(game->getCurrentPlayer(), data.value<Space*>());
			upgrade_button->setVisible(false);
		}

		// FIXME? mortgage_button->setVisible(owner == id)
        if (data.value<Space*>()->getOwner() == game->getCurrentPlayer()->getId()){
            mortgage_button->setVisible(true);
        } else {
            mortgage_button->setVisible(false);
        }

	}
}

void MainWindow::putUnderMortgage()
{

    QMessageBox *mortgageMsg = new QMessageBox;
    mortgageMsg->setWindowTitle("MORTGAGE");

    Space *s = currentSelection.value<Space*>();
    if(s->getType() == "PROPERTY") {
        Property *p = dynamic_cast<Property*>(s);
		if(!p->isOnMortgage()){
    		p->setMortgage(game->getCurrentPlayer());
       		 mortgageMsg->setText("You have put " + QString::fromStdString(p->getName()) + " under mortgage");
    	} else {
   			mortgageMsg->setText("This space is already on mortgage");
    	}
    } else if(s->getType() == "RAILROAD") {
    	Railroad *p = dynamic_cast<Railroad*>(s);
		if(!p->isOnMortgage()){
    		p->setMortgage(game->getCurrentPlayer());
        	mortgageMsg->setText("You have put " + QString::fromStdString(p->getName()) + " under mortgage");
    	} else {
   			mortgageMsg->setText("This space is already on mortgage");
    	}
    } else if(s->getType() == "UTILITY") {
        Utility *p = dynamic_cast<Utility*>(s);
		if(!p->isOnMortgage()){
    		p->setMortgage(game->getCurrentPlayer());
        	mortgageMsg->setText("You have put " + QString::fromStdString(p->getName()) + " under mortgage");
    	} else {
   			mortgageMsg->setText("This space is already on mortgage");
    	}
    }
	
    mortgageMsg->exec();
	// update tabs for every player
    display_tabs();
}

void MainWindow::sell_house(){
    Property* selectedSpace = static_cast<Property*>(currentSelection.value<Space*>());
    if(game->sellingHouseAllowed(selectedSpace)){
        selectedSpace->setNumBuildings(selectedSpace->getNumBuildings()-1);
        game->getBank()->giveMoney(game->getCurrentPlayer(), selectedSpace->getHousePrice()/2);
        if(selectedSpace->getNumBuildings() > 0 && selectedSpace->getNumBuildings() < 5)
            game->getBank()->setHouses(game->getBank()->getHouses()+1);
        else if(selectedSpace->getNumBuildings() == 5)
            game->getBank()->setHotels(game->getBank()->getHotels()+1);
    }
    infoText->setText(QString::fromStdString(selectedSpace->getInfo()));
    display_tabs();
    if(selectedSpace->getNumBuildings() > 0)
        sell_house_button->setVisible(true);
    else
        sell_house_button->setVisible(false);
}

void MainWindow::upgrade_property()
{
    Space* upgradeMe = currentSelection.value<Space*>();
    Player* curr_player = game->getCurrentPlayer();

    game->build(curr_player, upgradeMe);
    infoText->setText(QString::fromStdString(currentSelection.value<Space*>()->getInfo()));
    upgrade_button->setVisible(false);
    display_tabs();
    sell_house_button->setVisible(true);
}
