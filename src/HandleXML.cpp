#include "HandleXML.h"

HandleXML::HandleXML(const QString &filename, HandleXML::XMLMode mode)
{
    m_filename = filename;
    QFile m_file(m_filename);
    if(mode == HandleXML::XMLMode::LOAD){
        if (!m_file.open(QIODevice::ReadOnly) || !m_doc.setContent(&m_file))
            return;
        m_board = new Board();
    }

}

Board* HandleXML::board(){
    return m_board;
}

Bank* HandleXML::bank(){
    return m_bank;
}

void HandleXML::saveGame(const Game* game) const{

    QFile file(m_filename);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("players");
    int numOfPlayers = game->getPlayers().size();
    xmlWriter.writeAttribute("num", QString::number(numOfPlayers));

    std::vector<Player*> players = game->getPlayers();
    // get index of current player in order to calculate player turns
    auto iter = std::find_if(players.begin(), players.end(), [&] (Player *p) { return p->getId() == game->getCurrentPlayer()->getId(); });
    auto index = std::distance(players.begin(), iter);

    std::vector<uint> indexes;
    for(std::vector<uint>::size_type i = 0; i < players.size(); i++){
        indexes.push_back((index + i)%players.size());
    }

    savePlayers(players, indexes, xmlWriter);

    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

}

void HandleXML::savePlayers(std::vector<Player*> players, std::vector<uint> indexes, QXmlStreamWriter& writer) const{
    for(int i = 0; i < players.size(); i++){
        writer.writeStartElement("player");
        writer.writeTextElement("turn", QString::number(indexes.at(i)));
        writer.writeTextElement("name", QString::fromStdString(players.at(i)->getName()));
        writer.writeTextElement("id", QString::number(players.at(i)->getId()));
        writer.writeTextElement("wallet", QString::number(players.at(i)->get_wallet()));
        writer.writeTextElement("jail", QString::number(players.at(i)->is_in_jail()));
        writer.writeTextElement("pos", QString::number(players.at(i)->get_pos()));
        writer.writeTextElement("jail_turns", QString::number(players.at(i)->get_num_turns()));
        writer.writeTextElement("jail_card", QString::number(players.at(i)->jail_card()));

        writer.writeStartElement("properties");
        saveProperties(players.at(i), writer);
        writer.writeEndElement();

        writer.writeStartElement("railroads");
        saveRailroads(players.at(i), writer);
        writer.writeEndElement();

        writer.writeStartElement("utilities");
        saveUtilities(players.at(i), writer);
        writer.writeEndElement();

        writer.writeEndElement();
    }
}

void HandleXML::saveProperties(const Player* player, QXmlStreamWriter& writer) const{
    std::vector<Property*> properties = player->get_properties();
    for(const auto& i : properties){
        writer.writeStartElement("property");
        writer.writeTextElement("buy_price", QString::number(i->getBuyPrice()));
        writer.writeTextElement("rent_price", QString::number(i->getRentPrice()));
        writer.writeTextElement("h1_price", QString::number(i->getH1Price()));
        writer.writeTextElement("h2_price", QString::number(i->getH2Price()));
        writer.writeTextElement("h3_price", QString::number(i->getH3Price()));
        writer.writeTextElement("h4_price", QString::number(i->getH4Price()));
        writer.writeTextElement("h5_price", QString::number(i->getH5Price()));
        writer.writeTextElement("mortgage", QString::number(i->getMortgage()));
        writer.writeTextElement("house_price", QString::number(i->getHousePrice()));
        writer.writeTextElement("name", QString::fromStdString(i->getName()));
        writer.writeTextElement("colour", QString::fromStdString(i->getColour()));
        writer.writeTextElement("num_buildings", QString::number(i->getNumBuildings()));
        writer.writeTextElement("owned", QString::number(i->isOwned()));
        writer.writeTextElement("on_mortgage", QString::number(i->isOnMortgage()));
        writer.writeTextElement("owner_id", QString::number(i->getOwner()));
        writer.writeEndElement();
    }
}

void HandleXML::saveUtilities(const Player* player, QXmlStreamWriter& writer) const{
    std::vector<Utility*> utilities = player->get_utilities();
    for(const auto& i : utilities){
        writer.writeStartElement("utility");
        writer.writeTextElement("name", QString::fromStdString(i->getName()));
        writer.writeTextElement("buy_price", QString::number(i->getBuyPrice()));
        writer.writeTextElement("mortgage", QString::number(i->getMortgage()));
        writer.writeTextElement("owner_id", QString::number(i->getOwner()));
        writer.writeTextElement("group", QString::fromStdString(i->getGroup()));
        writer.writeTextElement("owned", QString::number(i->isOwned()));
        writer.writeTextElement("on_mortgage", QString::number(i->isOnMortgage()));
        writer.writeEndElement();
    }
}

void HandleXML::saveRailroads(const Player* player, QXmlStreamWriter& writer) const{
    std::vector<Railroad*> railroads = player->get_railroads();
    for(const auto& i : railroads){
        writer.writeStartElement("railroad");
        writer.writeTextElement("buy_price", QString::number(i->getBuyPrice()));
        writer.writeTextElement("rent_price", QString::number(i->getRentPrice()));
        writer.writeTextElement("mortgage", QString::number(i->getMortgage()));
        writer.writeTextElement("name", QString::fromStdString(i->getName()));
        writer.writeTextElement("owned", QString::number(i->isOwned()));
        writer.writeTextElement("owner_id", QString::number(i->getOwner()));
        writer.writeTextElement("on_mortgage", QString::number(i->isOnMortgage()));
        writer.writeEndElement();
    }
}

std::vector<Player*> HandleXML::processPlayers(bool &ok){

    qDebug() << "ProcessPlayers() invoked";

    std::vector<Player*> playersVector;
    // Potential bug

    QDomNodeList players = m_doc.elementsByTagName("player");

    auto numOfPlayers = players.size();
    playersVector.resize(numOfPlayers);

    if(!numOfPlayers){
        ok = false;
        qDebug() << "No players";
        return playersVector;
    }

    ok = true;

    for(int i = 0; i < players.size(); i++){
        QDomNode playerRoot = players.item(i);

        QDomElement turn = playerRoot.firstChildElement("turn");
        QDomElement name = playerRoot.firstChildElement("name");
        QDomElement id = playerRoot.firstChildElement("id");
        QDomElement wallet = playerRoot.firstChildElement("wallet");
        QDomElement jail = playerRoot.firstChildElement("jail");
        QDomElement pos = playerRoot.firstChildElement("pos");
        QDomElement turnsInJail = playerRoot.firstChildElement("jail_turns");
        QDomElement hasJailCard = playerRoot.firstChildElement("jail_card");

        // QDomElement list doesn't provide iterators, so std::any_of cannot be used
        // Another way of doing this would be to get list of all children and traverse
        // it with a normal loop
        std::vector<QDomElement> domElements;
        domElements.push_back(turn);
        domElements.push_back(name);
        domElements.push_back(id);
        domElements.push_back(wallet);
        domElements.push_back(jail);
        domElements.push_back(pos);
        domElements.push_back(turnsInJail);
        domElements.push_back(hasJailCard);


        //TODO: Stop loading if .xml file is corrupt and notify mainwindow about it (add signal)
        if(std::any_of(domElements.cbegin(), domElements.cend(), [] (QDomElement c) { return c.text() == ""; })){
            ok = false;
            qDebug() << "Bad loading";
        }

        qDebug() << name.text() << " " << id.text() << " " << wallet.text() << " " << jail.text()
                 << " " << pos.text() << " " << turnsInJail.text() << " " << hasJailCard.text();

        Player *p = new Player(id.text().toUInt(),name.text().toStdString(),wallet.text().toInt(), jail.text().toInt(), pos.text().toInt(), turnsInJail.text().toInt(), hasJailCard.text().toInt());

        QDomElement properties = playerRoot.firstChildElement("properties");
        if(!processProperties(properties,p))
            ok = false;

        QDomElement utilities = playerRoot.firstChildElement("utilities");
        if(!processUtilities(utilities,p))
            ok = false;

        QDomElement railroads = playerRoot.firstChildElement("railroads");
        if(!processRailroads(railroads,p))
            ok = false;

        //TODO: explore different ways to do this
        playersVector[turn.text().toInt()] = p;

    }

    qDebug() << playersVector.size();

    for(const auto& i : playersVector){
        qDebug() << QString::fromStdString(i->getName());
    }

    m_bank = new Bank(num_houses, num_hotels);
    return playersVector;

}

bool HandleXML::processProperties(QDomElement &properties, Player* p){

    qDebug() << "processProperties invoked";

    QDomNodeList propertiesList = properties.elementsByTagName("property");
    for(int i = 0 ; i < propertiesList.size(); i ++){
        QDomNode propertyRoot = propertiesList.item(i);

        QDomElement buyPrice = propertyRoot.firstChildElement("buy_price");
        QDomElement rentPrice = propertyRoot.firstChildElement("rent_price");
        QDomElement h1Price = propertyRoot.firstChildElement("h1_price");
        QDomElement h2Price = propertyRoot.firstChildElement("h2_price");
        QDomElement h3Price = propertyRoot.firstChildElement("h3_price");
        QDomElement h4Price = propertyRoot.firstChildElement("h4_price");
        QDomElement h5Price = propertyRoot.firstChildElement("h5_price");
        QDomElement mortgage = propertyRoot.firstChildElement("mortgage");
        QDomElement housePrice = propertyRoot.firstChildElement("house_price");
        QDomElement name = propertyRoot.firstChildElement("name");
        QDomElement colour = propertyRoot.firstChildElement("colour");
        QDomElement numBuildings = propertyRoot.firstChildElement("num_buildings");
        QDomElement owned = propertyRoot.firstChildElement("owned");
        QDomElement onMortgage = propertyRoot.firstChildElement("on_mortgage");
        QDomElement ownerId = propertyRoot.firstChildElement("owner_id");


        // Bad XML detection and recovery =============================================================================
        std::vector<QDomElement> domElements;
        domElements.push_back(buyPrice);
        domElements.push_back(rentPrice);
        domElements.push_back(h1Price);
        domElements.push_back(h2Price);
        domElements.push_back(h3Price);
        domElements.push_back(h4Price);
        domElements.push_back(h5Price);
        domElements.push_back(mortgage);
        domElements.push_back(housePrice);
        domElements.push_back(name);
        domElements.push_back(colour);
        domElements.push_back(numBuildings);
        domElements.push_back(owned);
        domElements.push_back(onMortgage);
        domElements.push_back(ownerId);

        if(std::any_of(domElements.cbegin(), domElements.cend(), [] (QDomElement e) { return e.text() == ""; })){
            qDebug() << "Property loading failed, some elements are empty";
            qDebug() << "\t" << buyPrice.text() << " " << rentPrice.text() << " " << h1Price.text() << " "
                     << h2Price.text() << " " << h3Price.text() << " " << h4Price.text() << " " << h5Price.text()
                     << " " << mortgage.text() << " " << housePrice.text() << " " << name.text() << " "
                     << colour.text() << " " << numBuildings.text() << " " << owned.text() << " "
                     << onMortgage.text() << " " << ownerId.text();
            return false;
        }
        // ============================================================================================================

        Property *prop = new Property(buyPrice.text().toDouble(), rentPrice.text().toDouble(), h1Price.text().toDouble(),
                                      h2Price.text().toDouble(),h3Price.text().toDouble(),h4Price.text().toDouble(),h5Price.text().toDouble(),
                                      mortgage.text().toDouble(), housePrice.text().toDouble(), name.text().toStdString(), colour.text().toStdString());


        // NOTE: couldn't get it to work with std::find_if + std::distance, don't know why ...
        // Find and set space in board
        int index;
        for(int i = 0; i < m_board->getSpaces().size(); i++){
            if(m_board->getSpaces().at(i)->getName() == prop->getName()){
                index = i;
                break;
            }
        }

        m_board->setSpace(index, prop);

        if(numBuildings.text().toInt() < 5 && numBuildings.text().toInt() > 0)
            num_houses--;
        else
            num_hotels--;

        prop->setNumBuildings(numBuildings.text().toInt());
        if(owned.text().toInt()){
            prop->setOwned();
            prop->setOwner(ownerId.text().toInt());
        }

        if(onMortgage.text().toInt())
            prop->setIsOnMortgage();

        p->add_property(prop);
        p->add_space(prop);


    }

    return true;

}

bool HandleXML::processUtilities(QDomElement &utilities, Player* p){

    qDebug() << "processUtilities invoked";

    QDomNodeList utilitiesList = utilities.elementsByTagName("utility");
    for(int i = 0 ; i < utilitiesList.size(); i ++){
        QDomNode propertyRoot = utilitiesList.item(i);

        QDomElement buyPrice = propertyRoot.firstChildElement("buy_price");
        QDomElement mortgage = propertyRoot.firstChildElement("mortgage");
        QDomElement ownerId = propertyRoot.firstChildElement("owner_id");
        QDomElement group = propertyRoot.firstChildElement("group");
        QDomElement name = propertyRoot.firstChildElement("name");
        QDomElement owned = propertyRoot.firstChildElement("owned");
        QDomElement onMortgage = propertyRoot.firstChildElement("on_mortgage");

        // Bad XML detection and recovery =============================================================================
        std::vector<QDomElement> domElements;
        domElements.push_back(buyPrice);
        domElements.push_back(mortgage);
        domElements.push_back(ownerId);
        domElements.push_back(group);
        domElements.push_back(owned);
        domElements.push_back(onMortgage);
        domElements.push_back(name);

        if(std::any_of(domElements.cbegin(), domElements.cend(), [] (QDomElement e) { return e.text() == ""; })){
            qDebug() << "Loading utilities failed";
            return false;
        }
        // ============================================================================================================

        Utility *util = new Utility(buyPrice.text().toDouble(), mortgage.text().toDouble(), group.text().toStdString());
        if(owned.text().toInt()){
            util->setOwned();
            util->setOwner(ownerId.text().toInt());
        }


        // Find and set place on board
        int index;
        for(int i = 0; i < m_board->getSpaces().size(); i++){
            if(m_board->getSpaces().at(i)->getName() == util->getName()){
                index = i;
                break;
            }
        }
        m_board->setSpace(index, util);

        if(onMortgage.text().toInt()){
            util->setIsOnMortgage();
        }

        p->add_utility(util);
        p->add_space(util);

        qDebug() << "\t" <<  buyPrice.text() << " " << mortgage.text() << " " << ownerId.text()
                 << " " << group.text() << " " << owned.text() << " " << onMortgage.text();
    }

    return true;

}

bool HandleXML::processRailroads(QDomElement &railroads, Player* p){

    qDebug() << "processRailroads invoked";

    QDomNodeList railroadList = railroads.elementsByTagName("railroad");
    for(int i = 0 ; i < railroadList.size(); i ++){
        QDomNode propertyRoot = railroadList.item(i);

        QDomElement buyPrice = propertyRoot.firstChildElement("buy_price");
        QDomElement rentPrice = propertyRoot.firstChildElement("rent_price");
        QDomElement mortgage = propertyRoot.firstChildElement("mortgage");
        QDomElement name = propertyRoot.firstChildElement("name");
        QDomElement owned = propertyRoot.firstChildElement("owned");
        QDomElement ownerId = propertyRoot.firstChildElement("owner_id");
        QDomElement onMortgage = propertyRoot.firstChildElement("on_mortgage");

        // Bad XML detection and recovery =============================================================================
        std::vector<QDomElement> domElements;
        domElements.push_back(buyPrice);
        domElements.push_back(rentPrice);
        domElements.push_back(mortgage);
        domElements.push_back(name);
        domElements.push_back(owned);
        domElements.push_back(ownerId);
        domElements.push_back(onMortgage);

        if(std::any_of(domElements.cbegin(), domElements.cend(), [] (QDomElement e) { return e.text() == ""; })){
            qDebug() << "Loading railroads failed";
            return false;
        }
        // ============================================================================================================

        Railroad *rail = new Railroad(buyPrice.text().toDouble(), rentPrice.text().toDouble(), mortgage.text().toDouble(), name.text().toStdString());

        // Find and set place in board
        int index;
        for(int i = 0; i < m_board->getSpaces().size(); i++){
            if(m_board->getSpaces().at(i)->getName() == rail->getName()){
                index = i;
                break;
            }
        }
        m_board->setSpace(index, rail);

        if(owned.text().toInt()){
            rail->setOwned();
            rail->setOwner(ownerId.text().toInt());
        }

        if(onMortgage.text().toInt()){
            rail->setIsOnMortgage();
        }

        p->add_railroad(rail);
        p->add_space(rail);

    }

    return true;

}
