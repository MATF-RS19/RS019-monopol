#include "Game.hpp"

void Game::printPlayers() const{
    
    for(const auto i : m_players){
        std::cout << "Player " << i->get_name() << std::endl;
    }
    
}

void Game::movePlayer(Player *player, int steps){
    player->set_pos((player->get_pos() + steps) % 40);
}

std::pair<int , int> Game::throwDice(){
    return std::make_pair(rand()%6+1, rand()%6+1);
}

void Game::nextPlayer(){
    Player* p = m_players.front();
    m_players.erase(m_players.begin());
    m_players.push_back(p);
    m_current_player = m_players.at(0);
}

Player* Game::getCurrentPlayer() const{
    return m_current_player;
}

void Game::showBoard() const{
        m_board->printBoard();
    }

std::vector<Player*> Game::getPlayers() const{
    return m_players;
}

Space* Game::getCurrentPlayerSpace() const{
    return m_board->getSpaces().at(m_current_player->get_pos());
}

Game::Game(int numPlayers){
    
    // Init players
    std::vector<Player*> players = Player::initializePlayers(numPlayers);
    std::copy(players.cbegin(), players.cend(), std::back_inserter(m_players));
    
    // Set first player
    m_current_player = m_players.front();
        
    // Create board
    m_board = new Board();
    
    // Create AuctionHouse
    
}
