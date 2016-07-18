#ifndef TERRITORY_H
#define TERRITORY_H

#include <vector>
#include <iostream>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <QLabel>
#include <list>
#include <QGraphicsPolygonItem>
#include "player.h"


class Territory{
public:
    std::vector<int> attackerDice;

    std::vector<int> defenderDice;

    void addTanks(int count);

    void removeTanks(int count);

    int attackTerritory(Territory* victim);

    void changeOwner(Player* owner);

    void setLabel(QLabel* lab);

    QLabel* label();

    std::string name(void);

    Player* owner(void);

    int id(void);



    int tanks(void);

    QGraphicsPolygonItem* getPolygon()
    {
        return m_polygon;
    }

    void setPolygon(QGraphicsPolygonItem* polygon)
    {
        m_polygon=polygon;
    }

    void addNeighbour(Territory* neighbour);

    std::list <Territory*> allConected();

    std::vector<Territory*> shortestPath(Territory* end);


    void setOwner(Player* owner);

    std::vector<Territory*> neighbours(void);

    Territory(int tanks, const std::string name, Player* owner);

    Territory(int tanks, const std::string name);

    Territory(int tanks, const std::string name, int id, QGraphicsPolygonItem *polygon);

    Territory(const std::string name, QGraphicsPolygonItem* polygon);

    Territory(void);

    ~Territory(void);

private:
    int m_tanks;
    std::string m_name;
    Player* m_owner;
    int m_id;
    std::vector<Territory*> m_neighbours;
    QGraphicsPolygonItem *m_polygon;
    QLabel* m_label;
};

#endif // TERRITORY_H
