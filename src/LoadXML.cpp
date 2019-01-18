#include "LoadXML.h"

LoadXML::LoadXML(const QString &filename)
{
    m_filename = filename;
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly) || !m_doc.setContent(&file))
            return;

    // Get number of players and pass it to processPlayers function
    // NOTE: unsafe if someone alters .xml file
    // should be changed to iteration over map and checking if
    // name of the attribute is num
    // TODO: change to iteration over map, add error signal that
    // will notify main window that .xml file is corrupt

    // TODO: recover from bad loading attempt
    //QDomNode node = m_doc.firstChildElement("players");
    //auto map = node.attributes();
    //auto mapItem = map.item(0);
    //auto attribute = mapItem.toAttr();


    //processPlayers(attribute.value().toInt());

}

std::vector<Player*> LoadXML::processPlayers(){

    qDebug() << "ProcessPlayers() invoked";

    std::vector<Player*> playersVector;
    // Potential bug


    QDomNodeList players = m_doc.elementsByTagName("player");

    auto numOfPlayers = players.size();
    playersVector.resize(numOfPlayers);

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
        if(std::any_of(domElements.cbegin(), domElements.cend(), [] (QDomElement c) { return c.text() == ""; }))
            qDebug() << "Bad loading";

        qDebug() << name.text() << " " << id.text() << " " << wallet.text() << " " << jail.text()
                 << " " << pos.text() << " " << turnsInJail.text() << " " << hasJailCard.text();

        qDebug() << id.text().toInt();

        Player *p = new Player(id.text().toUInt(),name.text().toStdString(),wallet.text().toInt(), jail.text().toInt(), pos.text().toInt(), turnsInJail.text().toInt(), hasJailCard.text().toInt());

        QDomElement properties = playerRoot.firstChildElement("properties");
        processProperties(properties,p);

        QDomElement utilities = playerRoot.firstChildElement("utilities");
        processUtilities(utilities,p);

        QDomElement railroads = playerRoot.firstChildElement("railroads");
        //processRailroads(railroads,p);

        //TODO: explore different ways to do this
        playersVector[turn.text().toInt()] = p;

    }

    qDebug() << playersVector.size();

    for(const auto& i : playersVector){
        qDebug() << QString::fromStdString(i->getName());
    }

    return playersVector;

}

void LoadXML::processProperties(QDomElement &properties, Player* p){

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

        if(std::any_of(domElements.cbegin(), domElements.cend(), [] (QDomElement e) { return e.text() == ""; }))
            qDebug() << "Property loading failed";
        // ============================================================================================================

        Property *prop = new Property(buyPrice.text().toDouble(), rentPrice.text().toDouble(), h1Price.text().toDouble(),
                                      h2Price.text().toDouble(),h3Price.text().toDouble(),h4Price.text().toDouble(),h5Price.text().toDouble(),
                                      mortgage.text().toDouble(), housePrice.text().toDouble(), name.text().toStdString(), colour.text().toStdString());

        prop->setNumBuildings(numBuildings.text().toInt());
        if(owned.text().toInt()){
            prop->setOwned();
            prop->setOwner(ownerId.text().toInt());
        }

        if(onMortgage.text().toInt())
            prop->setIsOnMortgage();

        p->add_property(prop);
        p->add_space(prop);

        qDebug() << "\t" << buyPrice.text() << " " << rentPrice.text() << " " << h1Price.text() << " "
                 << h2Price.text() << " " << h3Price.text() << " " << h4Price.text() << " " << h5Price.text()
                 << " " << mortgage.text() << " " << housePrice.text() << " " << name.text() << " "
                 << colour.text() << " " << numBuildings.text() << " " << owned.text() << " "
                 << onMortgage.text() << " " << ownerId.text();
    }



}

void LoadXML::processUtilities(QDomElement &utilities, Player* p){

    qDebug() << "processUtilities invoked";

    QDomNodeList utilitiesList = utilities.elementsByTagName("utility");
    for(int i = 0 ; i < utilitiesList.size(); i ++){
        QDomNode propertyRoot = utilitiesList.item(i);

        QDomElement buyPrice = propertyRoot.firstChildElement("buy_price");
        QDomElement mortgage = propertyRoot.firstChildElement("mortgage");
        QDomElement ownerId = propertyRoot.firstChildElement("owner_id");
        QDomElement group = propertyRoot.firstChildElement("group");
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

        if(std::any_of(domElements.cbegin(), domElements.cend(), [] (QDomElement e) { return e.text() == ""; }))
            qDebug() << "Loading utilities failed";
        // ============================================================================================================

        Utility *util = new Utility(buyPrice.text().toDouble(), mortgage.text().toDouble(), group.text().toStdString());
        if(owned.text().toInt()){
            util->setOwned();
            util->setOwner(ownerId.text().toInt());
        }
        if(onMortgage.text().toInt()){
            util->setIsOnMortgage();
        }

        p->add_utility(util);
        p->add_space(util);

        qDebug() << "\t" <<  buyPrice.text() << " " << mortgage.text() << " " << ownerId.text()
                 << " " << group.text() << " " << owned.text() << " " << onMortgage.text();
    }

}

void LoadXML::processRailroads(QDomElement &railroads, Player* p){

    qDebug() << "processRailroads invoked";

    QDomNodeList railroadList = railroads.elementsByTagName("utility");
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

        if(std::any_of(domElements.cbegin(), domElements.cend(), [] (QDomElement e) { return e.text() == ""; }))
            qDebug() << "Loading railroads failed";
        // ============================================================================================================

        Railroad *rail = new Railroad(buyPrice.text().toDouble(), rentPrice.text().toDouble(), mortgage.text().toDouble(), name.text().toStdString());

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
}
