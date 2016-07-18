#ifndef CONTINENT_H
#define CONTINENT_H

#include "territory.h"
#include <vector>
#include "player.h"
#include <string>

class Continent
{
public:
    Continent();
    Continent(std::vector<Territory*> x);
    void addTerritory(Territory* x);
    Player* checkOwning(void);

    Territory* territory(std::string name);
    Territory* territory(int id);

    std::vector<Territory*> territories();

    ~Continent();

private:
    std::vector<Territory*> m_territories;

};


#endif // CONTINENT_H
