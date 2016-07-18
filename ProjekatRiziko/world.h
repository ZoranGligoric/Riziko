#ifndef WORLD_H
#define WORLD_H

#include "continent.h"
#include "territory.h"
#include <vector>
#include <string>
#include "turn.h"

class World
{
public:
    World(Turn* turn);
    void gainedTanks(Player *p);
    Continent* europe();
    Continent* northAmerica();
    Continent* southAmerica();
    Continent* africa();
    Continent* asia();
    Continent* australia();

    Territory* territory(std::string name);
    Territory* territory(int id);
    std::vector<Territory*> allTerritories();
    void init(std::list<Player*> players);


    Turn* turn();


    ~World();

    std::list<Player*> m_players;
    std::string colors [8] = {"blue", "red", "green", "yellow", "purple", "orange", "cyan", "magenta"};

private:
    std::vector<Continent*> m_continents;
    Turn* m_turn;
};

#endif // WORLD_H
