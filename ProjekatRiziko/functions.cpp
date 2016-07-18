#include "territory.h"
#include "player.h"
#include "turn.h"
#include <sstream>

bool connected(Territory* start, Territory* end)
{
    if(start->owner()!=end->owner())
    {
        return false;
    }
    else
    {

        if(start==end)
            return true;

        std::list<Territory*> queue;

        queue.push_back(start);


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

                    if(*i == end)
                        return true;

                    if(start->owner()!=(*i)->owner())
                    {
                     visited[distance(neighbours.begin(), i)]=1;
                     continue;
                    }

                    visited[distance(neighbours.begin(), i)]=1;
                    queue.push_back(*i);

                }

        }

    return false;
    }
    return false;
}

bool areNeighbours(Territory* start, Territory* end)
{
    std::vector<Territory *> neighbours=start->neighbours();
    std::vector<Territory *>::iterator i=neighbours.begin();
    for(; i!=neighbours.end();i++)
    {
        if(end==*i)
            return true;
    }

    return false;
}

bool contains(Territory* ter, std::list<Territory*> path)
{
    std::list<Territory*>::iterator i=path.begin();
    for(; i!=path.end(); i++)
        if(ter==*i)
            return true;
    return false;
}

bool contains(Territory* element, std::vector<Territory*> vct){
    std::vector<Territory*>::iterator i;
    for(i=vct.begin(); i!= vct.end(); i++){
        if(*i==element)
            return true;
    }
    return false;
}


std::vector<Territory*> bfs2(Territory* start, Territory* end, std::vector<Territory*> discovered, std::vector<Territory*> previous, std::vector<Territory*> visited){
    std::vector<Territory*>::iterator i, j;
    visited.push_back(start);
    if(start == end){
        //izlaz iz rekurzije

        std::vector<Territory*> path;
        path.push_back(start);
        Territory* cilj = start;
        while(1){
            if(cilj==*(discovered.begin()))
                return path;
            for(i=discovered.begin(), j=previous.begin(); *i!=cilj; i++, j++);
            path.push_back(*j);
            cilj = *j;
        }
    }
    std::vector<Territory*> tmp = start->neighbours();


    //DODAVANJE NOVIH PRONADJENIH CVOROVA (od istog owner-a)
    for(i=tmp.begin(); i!=tmp.end(); i++){
        if(!contains(*i, discovered) && (start->owner() == (*i)->owner()) ){
            discovered.push_back(*i);
            previous.push_back(start);
        }
    }

    //TRAZENJE PRVOG PRONADJENOG CVORA KOJI JOS NIJE POSECEN
    //cout << "Looking for new vertex " << endl;
    for(i=discovered.begin(); i!=discovered.end(); i++){
        if(!contains(*i, visited) && (start->owner() == (*i)->owner()) ){
            break;
        }
    }

    if(i!=discovered.end()){
        return bfs2(*i, end, discovered, previous, visited);
    }

    //Cisto zbog warning
    std::vector<Territory*> war;
    return war;

}


std::vector<Territory*> bfs(Territory* start, Territory* end){
    std::vector<Territory*> path;
    std::vector<Territory*> discovered;
    std::vector<Territory*> previous;
    std::vector<Territory*> visited;

    std::vector<Territory*> tmp = start->neighbours();
    std::vector<Territory*>::iterator i, j, k;


    visited.push_back(start);
    discovered.push_back(start);
    previous.push_back(start);

    for(i=tmp.begin(); i!=tmp.end(); i++){
        if((*i)->owner()==start->owner()){
            discovered.push_back(*i);
            previous.push_back(start);
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

std::string toString(int x)
{
    std::stringstream ss;
    ss << x;
    std::string s;
    ss >> s;
    return s;
}
