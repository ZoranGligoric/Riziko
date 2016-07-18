#include "turn.h"

void Turn::nextPlayer(){
    m_current++;
    if(m_current == m_players.end())
        m_current=m_players.begin();
}

void Turn::nextPhase()
{
   if(m_phase==1)
       m_phase = 2;
   else if(m_phase==2)
       m_phase = 3;
   else if(m_phase>=3)
   {
       m_phase = 1;
       m_current++;
       if(m_current == m_players.end())
           m_current=m_players.begin();
   }
}

int Turn::getPhase()
{
    return m_phase;
}

std::list<Player*> Turn::players()
{
  return m_players;
}

void Turn::removePlayer(Player* player){
    std::list<Player*>::iterator i;
    for(i=m_players.begin(); *i!=player; i++);
    m_players.erase(i);
}

Player* Turn::currentPlayer(void){
    return *m_current;
}

Player* Turn::firstPlayer(void){
    return *(m_players.begin());
}


void Turn::addPlayer(Player* player){
    if(m_players.size()==6){
        return;
    }
    m_players.push_back(player);
    if(m_players.size() == 0)
        m_current=m_players.begin();
}


Turn::Turn(std::list<Player*> players)
    :m_players(players), m_current(m_players.begin()), m_phase(1)
{}

Turn::~Turn(){}
