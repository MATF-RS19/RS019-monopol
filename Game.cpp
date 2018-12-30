#include "Game.hpp"

void Game::printPlayers() const{
    
    for(const auto i : m_players){
        std::cout << "Player " << i->get_name() << std::endl;
    }
    
}

Game::Game(int numPlayers){
    
    std::vector<Player*> players = Player::initializePlayers(numPlayers);
    std::copy(players.cbegin(), players.cend(), std::back_inserter(m_players));
    
    m_board = new Board();
    
}
