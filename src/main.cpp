#include <vector>
#include <iostream>
#include <ctime>
#include <QApplication>
#include "mainwindow.h"
#include "Board.hpp"
#include "Game.hpp"

int main(int argc, char** argv)
{
    std::srand(unsigned(std::time(0)));
    
    QApplication app(argc, argv);
    MainWindow main;
    main.show();
    return app.exec();
    
}
