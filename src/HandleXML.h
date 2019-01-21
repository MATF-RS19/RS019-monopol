#pragma once

#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QtDebug>
#include <QXmlStreamWriter>
#include "Player.hpp"
#include "Property.hpp"
#include "Railroad.hpp"
#include "Utility.hpp"
#include "Game.hpp"

/*
    XML parsing class used to create new game from xml data
*/


class HandleXML
{

Q_SIGNALS:
    void badXML();


public:
    enum class XMLMode{
        LOAD,
        SAVE
    };

    HandleXML(const QString &filename, HandleXML::XMLMode mode);

    std::vector<Player*> processPlayers(bool &ok);

    // Bolje bi bilo da se prosledjuje po referenci, ali vec je ceo
    // program napisan sa pokazivacima, bilo bi neophodno veliko
    // refaktorisanje
    bool processProperties(QDomElement &properties, Player* p);
    bool processUtilities(QDomElement &properties, Player* p);
    bool processRailroads(QDomElement &properties, Player* p);

    void saveGame(const Game* game) const;
    void savePlayers(const std::vector<Player*> players, std::vector<uint> indexes, QXmlStreamWriter& writer) const;
    void saveProperties(const Player* player, QXmlStreamWriter& writer) const;
    void saveUtilities(const Player* player, QXmlStreamWriter& writer) const;
    void saveRailroads(const Player* player, QXmlStreamWriter& writer) const;

private:
    QFile m_file;
    QString m_filename;
    QDomDocument m_doc;
    QXmlStreamWriter m_writer;

};
