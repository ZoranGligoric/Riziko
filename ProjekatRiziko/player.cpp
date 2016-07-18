#include "player.h"

std::string Player::name(void){
    return m_name;
}

std::string Player::color(void){
    return m_color;
}

int Player::territories(void){
    return m_territoriesCount;
}

void Player::addColor(std::string color){
    m_color = color;
}

std::string Player::getColor(){
    return m_color;
}

void Player::addTerritory(void){
    m_territoriesCount += 1;
}

void Player::addTerritories(int x){
    m_territoriesCount += x;
}

void Player::addTanks(int x){
    m_unplaced += x;
}

void Player::removeTanks(int x){
    m_unplaced -= x;
}

int Player::unplaced(){
    return m_unplaced;
}


Player::Player(std::string name, std::string color)
    :m_color(color)
{
    if(name=="")
        m_name = "Undefined";
    else
        m_name = name;
    m_territoriesCount=0;
    m_unplaced=0;
    m_id=0;
}

Player::Player(std::string color)
    :m_color(color)
{
    m_territoriesCount=0;
    m_unplaced=0;
    m_name="Undefined";
    m_id=0;
}

Player::Player(std::string name, std::string color, int id)
    :m_name(name), m_color(color), m_id(id)
{
    m_unplaced=0;
}

Player::Player(void)
{}

Player::~Player()
{}
