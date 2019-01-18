#pragma once

#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QtDebug>
#include "Player.hpp"
#include "Property.hpp"
#include "Railroad.hpp"
#include "Utility.hpp"

/*
    XML parsing class used to create new game from xml data
*/


class LoadXML
{
public:
    LoadXML(const QString &filename);

    std::vector<Player*> processPlayers();

    // Bolje bi bilo da se prosledjuje po referenci, ali vec je ceo
    // program napisan sa pokazivacima, bilo bi neophodno veliko
    // refaktorisanje
    void processProperties(QDomElement &properties, Player* p);
    void processUtilities(QDomElement &properties, Player* p);
    void processRailroads(QDomElement &properties, Player* p);
    void processSpaces();

private:
    QString m_filename;
    QDomDocument m_doc;

};
