#include "territory.h"
#include "functions.h"
#include "game.h"
#include "ui_game.h"
#include <QLabel>
#include <QString>


void Territory::setLabel(QLabel* lab)
{
    m_label=lab;
}

QLabel* Territory::label(){
    return m_label;
}



void Territory::addTanks(int count){
    m_tanks += count;
}

void Territory::removeTanks(int count){
    m_tanks -= count;
}

int Territory::attackTerritory(Territory* victim){
    int result = 0;
    int i;
    if(m_tanks < 2){
        std::cout << "You don't have enough tanks on " << m_name << " to attack!" << std::endl;
    }
    else if(find(m_neighbours.begin(), m_neighbours.end(), victim) == m_neighbours.end()){
        std::cout << "Cannot attack that Territory!" << std::endl;
    }
    else{
        //NAPAD
        std::cout << m_name << "(" << m_tanks << ")" << " is attacking " << victim->name() << "(" << victim->tanks() << ")" << "....." << std::endl;
        int attackerCount, defenderCount;
        if(m_tanks>=4)
            attackerCount=3;
        else if(m_tanks==3)
        {
            attackerCount = 2;
        }
        else if(m_tanks==2)
         {
            attackerCount = 1;
        }

        if(victim->tanks()>=3)
            defenderCount=3;
        else if(victim->tanks()==2)
           { defenderCount=2;
            }
        else
           { defenderCount=1;
            }
        std::vector<int> attackerDices;
        std::vector<int> defenderDices;
        srand(time(NULL));

        for(i=0; i<attackerCount; i++){
            int num = rand() % 6 + 1;
            attackerDices.push_back(num);
        }

        std::sort(attackerDices.begin(), attackerDices.end(), std::greater<int>());
        std::cout << "Attacker Rolls:";
        for(i=0; i<attackerCount; i++){
            std::cout << " " << attackerDices[i];
            result *= 10;
            result += attackerDices[i];
        }

        while(i<3){
            result *= 10;
            i++;
        }

        std::cout << std::endl;

        for(i=0; i<defenderCount; i++){
            int num = rand() % 6 + 1;
            defenderDices.push_back(num);
        }


        std::sort(defenderDices.begin(), defenderDices.end(), std::greater<int>());
        std::cout << "Defender Rolls:";
        for(i=0; i<defenderCount; i++){
            std::cout << " " << defenderDices[i];
            result *= 10;
            result += defenderDices[i];
        }

        while(i<3){
            result *= 10;
            i++;
        }

        std::cout << std::endl;


        int attackerLoss=0;
        int defenderLoss=0;

        for(int i=0; i<attackerCount && i<defenderCount; i++){
            if((attackerDices[i] - defenderDices[i]) > 0)
                defenderLoss++;
            else attackerLoss++;
        }

        victim->removeTanks(defenderLoss);
        removeTanks(attackerLoss);

        std::cout << m_name << " lost " << attackerLoss << " and now has " << m_tanks << " tank(s)." << std::endl;
        std::cout << victim->name() << " lost " << defenderLoss << " and now has " << victim->tanks() << " tank(s)." << std::endl;

        m_label->setText(QString::number(m_tanks));
        victim->label()->setText(QString::number(victim->tanks()));

        if(victim->tanks()==0){
            std::cout << "Congratulations! You have conquered " << victim->name() << "!" << std::endl;
        }

        this->attackerDice=attackerDices;
        victim->defenderDice=defenderDices;
   }


    return result;
}

std::list <Territory*> Territory::allConected()
{
    std::list <Territory* > queue;

    queue.push_back(this);

    std::list<Territory*>::iterator iter1;

    for(iter1=queue.begin(); iter1!=queue.end(); iter1++)
    {

            std::vector<Territory*> neighbours=(*iter1)->neighbours();

            bool* visited=new bool[neighbours.size()];

            std::vector<Territory*>::iterator i;

            for(i = neighbours.begin(); i != neighbours.end(); i++)
                    visited[distance(neighbours.begin(), i)]=false;

            for(i = neighbours.begin(); i != neighbours.end(); i++)
            {
                if(*iter1==*i)
                    continue;

                if(visited[distance(neighbours.begin(), i)]==true)
                    continue;

                if(this->owner()!=(*i)->owner())
                {
                 visited[distance(neighbours.begin(), i)]=1;
                 continue;
                }

                 visited[distance(neighbours.begin(), i)]=1;

                 if(!contains(*i, queue))
                    queue.push_back(*i);

            }
    }

    return queue;
}


std::vector<Territory*> Territory::shortestPath(Territory* end){
    std::vector<Territory*> path;
    std::vector<Territory*> discovered;
    std::vector<Territory*> previous;
    std::vector<Territory*> visited;

    std::vector<Territory*> tmp = this->neighbours();
    std::vector<Territory*>::iterator i, j, k;

    visited.push_back(this);
    discovered.push_back(this);
    previous.push_back(this);

    for(i=tmp.begin(); i!=tmp.end(); i++){
        if((*i)->owner()==this->owner()){
            discovered.push_back(*i);
            previous.push_back(this);
        }
    }

    if(discovered.size()==1)
        return path;

    bool found = false;
    for(i=discovered.begin(), j=previous.begin(); i!=discovered.end(); i++, j++){
        if(*i == end){
            found = true;
            break;
        }
        std::vector<Territory*> tmp2 = (*i)->neighbours();
        for(k=tmp2.begin(); k!=tmp2.end(); k++){
            if(!contains(*k, discovered) && ( (*i)->owner() == (*k)->owner()) ){
                discovered.push_back(*k);
                previous.push_back(*i);
            }
        }
    }

    /*Provera da li je pronadjen put*/
    if(!found)
        return path;

    path.push_back(*i);
    Territory* x = *j;
    for(; i!=discovered.begin(); i--, j--){
        if(*i==x){
            path.push_back(*i);
            x=*j;
        }
    }
    path.push_back(*i);
    return path;
}


void Territory::changeOwner(Player* owner){
    m_owner = owner;
}

std::string Territory::name(void){
    return m_name;
}

Player* Territory::owner(void){
    return m_owner;
}

int Territory::tanks(void){
    return m_tanks;
}

int Territory::id(void){
    return m_id;
}

void Territory::addNeighbour(Territory* neighbour){
    m_neighbours.push_back(neighbour);
}

void Territory::setOwner(Player* owner){
    m_owner = owner;
}

std::vector<Territory*> Territory::neighbours(void)
{
    return m_neighbours;
}

Territory::Territory(int tanks, const std::string name, Player* owner)
    :m_tanks(tanks), m_name(name), m_owner(owner), m_label(NULL)
{}

Territory::Territory(int tanks, const std::string name)
    :m_tanks(tanks), m_name(name), m_label(NULL)
{
    m_id=0;
}

Territory::Territory(int tanks, const std::string name, int id, QGraphicsPolygonItem* polygon)
    :m_tanks(tanks), m_name(name), m_id(id), m_polygon(polygon), m_label(NULL)
{}

Territory::Territory(void)
    :m_tanks(0), m_name("Default"), m_id(0), m_label(NULL)
{}

Territory::~Territory(void){

}
