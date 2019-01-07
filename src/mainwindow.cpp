#include <QtWidgets>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>

#include "mainwindow.h"
#include "Game.hpp"

int numOfPlayers;

QStandardItemModel *model;

MainWindow::MainWindow()
{
	QMessageBox msgBox;
	msgBox.setText(tr("Hello! Select number of players!"));
	QPushButton* btn1 = msgBox.addButton(QString("One"), QMessageBox::ActionRole);
	QPushButton* btn2 = msgBox.addButton(QString("Two"), QMessageBox::ActionRole);
	QPushButton* btn3 = msgBox.addButton(QString("Three"), QMessageBox::ActionRole);
	QPushButton* btn4 = msgBox.addButton(QString("Four"), QMessageBox::ActionRole);

	msgBox.exec();

	if (msgBox.clickedButton() == btn1) {
	   	numOfPlayers = 1;
	} else if (msgBox.clickedButton() == btn2) {
		numOfPlayers = 2;
	} else if (msgBox.clickedButton() == btn3) {
		numOfPlayers = 3;
	} else if (msgBox.clickedButton() == btn4) {
		numOfPlayers = 4;
	}


    //Create vector of names
    std::vector<std::string> names(numOfPlayers);

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

    //Create game for selected number of players
    Game g(numOfPlayers, names);

    //Get spaces
    std::vector<Space*> spaces = g.getBoard()->getSpaces();

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
    pass_button = new QPushButton(tr("Pass"), this);

    // adding widgets to horizontal layout
    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addWidget(buy_button);
    h_layout->addWidget(roll_button);
    h_layout->addWidget(upgrade_button);
    h_layout->addWidget(pass_button);

    // set layout for bottom dock area widget
    bottom_dock->setLayout(h_layout);

    // set & add bottom dock widget
    dock->setWidget(bottom_dock);
    addDockWidget(Qt::BottomDockWidgetArea, dock);

    // init widgets
    right_dock = new QWidget();
    description = new QListWidget();
    dices = new QLabel();

	// die -- jednina, dice -- mnozina
    dices->setText(tr("dice"));

    // adding widgets to vertical layout
    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addWidget(description);
    v_layout->addWidget(dices);

    // set layout for right dock area widget
    right_dock->setLayout(v_layout);

    // set & add right dock widget
    dock = new QDockWidget("Info", this);
    dock->setWidget(right_dock);

    addDockWidget(Qt::RightDockWidgetArea, dock);

    // left dock area
    // init widgets
    left_dock = new QWidget();

    players = new QTabWidget();

	QLabel *tab;
	int i = 0;
	while(i < numOfPlayers) {
		tab = new QLabel();
		tab->setText(QString("Player " + QString().setNum(i+1)) + " info");

		player_tabs.push_back(tab);
		++i;
	}
    // TODO: add tabs depending on number of players
	for (int i = 0; i < numOfPlayers; i++) {
		players->addTab(player_tabs[i], QString("Player " + QString().setNum(i+1)));
	}

    // set layout
    QVBoxLayout *v_layout2 = new QVBoxLayout();
    v_layout2->addWidget(players);

    // set & add left dock widget
    left_dock->setLayout(v_layout2);
    dock = new QDockWidget("Players", this);
    dock->setWidget(left_dock);

    addDockWidget(Qt::LeftDockWidgetArea, dock);
}
