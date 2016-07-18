#ifndef TURN_H
#define TURN_H

#include "player.h"
#include <list>

class Turn{
public:
    void nextPlayer(void);

    void removePlayer(Player* player);

    Player* currentPlayer(void);

    Player* firstPlayer(void);

    void addPlayer(Player* player);

    void nextPhase();

    int getPhase();

    std::list<Player*> players(void);

    Turn(std::list<Player*> players);

    ~Turn();

private:
    std::list<Player*> m_players;
    std::list<Player*>::iterator m_current;
    int m_phase;
};

#endif // TURN_H
