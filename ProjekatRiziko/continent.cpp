#include "continent.h"

Continent::Continent()
{
}

Continent::Continent(std::vector<Territory*> x){
    m_territories = x;
}
void Continent::addTerritory(Territory* x){
    m_territories.push_back(x);
}

Player* Continent::checkOwning(void){
    std::vector<Territory*>::iterator i = m_territories.begin();

    Player* candidate = (*i)->owner();

    for(i = m_territories.begin(); i!=m_territories.end(); i++){
        if( (*i)->owner() != candidate)
            return 0;
    }
    return candidate;
}

std::vector<Territory*> Continent::territories()
{
    return m_territories;
}

Territory* Continent::territory(std::string name){
    std::vector<Territory*>::iterator i;
    for(i=m_territories.begin(); i!= m_territories.end(); i++)
        if((*i)->name() == name)
            return *i;

    return 0;
}

Territory* Continent::territory(int id){
    std::vector<Territory*>::iterator i;
    for(i=m_territories.begin(); i!= m_territories.end(); i++)
        if((*i)->id() == id)
            return *i;

    return 0;
}

Continent::~Continent(){}
