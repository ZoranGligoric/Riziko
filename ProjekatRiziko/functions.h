#ifndef FUNCTIONS
#define FUNCTIONS

#include <vector>
#include <list>
#include "territory.h"
#include "player.h"


bool connected(Territory* start, Territory* end);
bool areNeighbours(Territory* start, Territory* end);
bool contains(Territory* ter, std::list<Territory*> path);
bool contains(Territory* element, std::vector<Territory*> vct);
std::vector<Territory*> bfs2(Territory* start, Territory* end, std::vector<Territory*> discovered, std::vector<Territory*> previous, std::vector<Territory*> visited);
std::vector<Territory*> bfs(Territory* start, Territory* end);
std::list <Territory*> allConected(Territory* start);
std::string toString(int x);

#endif // FUNCTIONS
