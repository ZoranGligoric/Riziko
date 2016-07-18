#include "world.h"
#include "game.h"
#include <iostream>
#include <cstring>
#include <QGraphicsPolygonItem>


/*
 *  m_continents[0] - Europe
 *  m_continents[1] - N.America
 *  m_continents[2] - S.America
 *  m_continents[3] - Africa
 *  m_continents[4] - Asia
 *  m_continents[5] - Australia
 */


void World::gainedTanks(Player *p)
{
    int total=0;

    total+=floor(p->territories()/3);

    if(europe()->checkOwning()==p)
                total+=5;
    if(asia()->checkOwning()==p)
                total+=7;
    if(africa()->checkOwning()==p)
                total+=3;
    if(northAmerica()->checkOwning()==p)
                total+=5;
    if(southAmerica()->checkOwning()==p)
                total+=2;
    if(australia()->checkOwning()==p)
                total+=2;

    p->addTanks(total);
}


Continent* World::europe(){
    if(m_continents.size() == 6)
        return m_continents[0];
    else
        return 0;
}

Continent* World::northAmerica(){
    if(m_continents.size() == 6)
        return m_continents[1];
    else
        return 0;
}
Continent* World::southAmerica(){
    if(m_continents.size() == 6)
        return m_continents[2];
    else
        return 0;
}
Continent* World::africa(){
    if(m_continents.size() == 6)
        return m_continents[3];
    else
        return 0;
}
Continent* World::asia(){
    if(m_continents.size() == 6)
        return m_continents[4];
    else
        return 0;
}
Continent* World::australia(){
    if(m_continents.size() == 6)
        return m_continents[0];
    else
        return 0;
}

Turn* World::turn(){
    return m_turn;
}


Territory* World::territory(std::string name){
    std::vector<Continent*>::iterator i;
    Territory* resoult;
    for(i=m_continents.begin(); i!=m_continents.end(); i++){
        if( (resoult = (*i)->territory(name)) != 0)
            return resoult;
    }
    return 0;
}


Territory* World::territory(int id){
    std::vector<Continent*>::iterator i;
    Territory* resoult;
    for(i=m_continents.begin(); i!=m_continents.end(); i++){
        if( (resoult = (*i)->territory(id)) != 0)
            return resoult;
    }
    return 0;
}

std::vector<Territory*> World::allTerritories()
{
    std::vector<Continent*>::iterator i;
    std::vector<Territory*>::iterator j;
    std::vector<Territory*> result;
    std::vector<Territory*> tmp;

    for(i=m_continents.begin(); i!=m_continents.end(); i++)
    {
        tmp = (*i)->territories();

        for(j=tmp.begin(); j!=tmp.end(); j++)
            result.push_back(*j);

    }

    return result;
}


void World::init(std::list<Player*> players){



    std::vector<Territory*> regions = this->allTerritories();

    std::vector<Territory*>::iterator i;
    std::list<Player*>::iterator j;

    int k=0;

    for(j=players.begin(); j!=players.end(); j++){
        m_players.push_back(*j);
        (*j)->addColor(colors[k]);
        k++;
    }

    int max = (int)((float)regions.size() / (float)players.size()); //koliko svaki igrac treba da dobije teritorija
    int n = players.size();
    int broj[n];//broji koliko je svaki igrac dobio teritorija
    std::memset( broj, 0, n*sizeof(int) );
    int ukupnoMax=0;

    srand(time(0)); //potrebno da bi random uvek uzimao drugacije brojeve

    //u ovoj petlji se dodeljuju owneri teritorijama
    for(i=regions.begin(); i!=regions.end(); i++)
    {
        j=players.begin();

        //proverava da li su svi na 'max' teritorija, ako jesu ima ostatka i raspodeljuje ga od pocetka liste svakome po jedan
        if(n-ukupnoMax == 0){
            for(j=players.begin(); i!=regions.end(); i++, j++){
                (*i)->changeOwner(*j);
                std::cout << (*i)->name() << ": " << (*j)->name() << std::endl;
                (*j)->addTerritory();
            }
            break;
        }


        int nmb = rand() % (n-ukupnoMax); //random broj koji odredjuje igraca koji nije dobio max

        //dodeljivanje teritorije, nakon cega ukoliko igrac ima max teritorija ide na kraj liste koji se ne moze dobiti u 'nmb'
        advance(j, nmb);
        (*i)->changeOwner(*j);
        (*j)->addTerritory();
        broj[nmb]++;
        if(broj[nmb]>=max){
            ukupnoMax++;
            players.splice( players.end(), players, j );
            for(;nmb<n-1; nmb++){
                int tmp = broj[nmb+1];
                broj[nmb+1] = broj[nmb];
                broj[nmb] = tmp;
            }
        }
        std::cout << (*i)->name() << ": " << (*j)->name() << std::endl;
    }
    std::cout << std::endl;

    int tanksCount = 20 + (6 - players.size()) * 5;

    for(j=players.begin(); j!=players.end(); j++){
        std::cout << (*j)->name() << " : " << (*j)->territories() << " territories, ";
        int tmp = tanksCount - (*j)->territories();
        (*j)->addTanks(tmp);
        std::cout << (*j)->unplaced() << " unplaced tanks." << std::endl;
    }

}




World::World(Turn *turn)
    :m_turn(turn)
{
    QGraphicsPolygonItem *p_greatBritain = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(40, -63) <<  QPointF(17, -60) <<  QPointF(17, -62) <<  QPointF(26, -65) <<  QPointF(19, -68) <<  QPointF(21, -73) <<
                 QPointF(23, -74) <<  QPointF(27, -75) <<  QPointF(26, -81) <<  QPointF(20, -81)
                 <<  QPointF(18, -80) <<  QPointF(18, -78) <<  QPointF(15, -75) <<  QPointF(15, -69) <<
                 QPointF(13, -68) <<  QPointF(9, -68)
                 << QPointF(2, -65) <<  QPointF(1, -69) <<  QPointF(4, -74) <<  QPointF(2, -77) <<  QPointF(7, -79) <<  QPointF(9, -82) <<
                 QPointF(17, -82) << QPointF(18, -80) << QPointF(20, -81) <<  QPointF(19, -86) <<
                 QPointF(19, -89) <<  QPointF(25, -94) <<  QPointF(25, -92) <<  QPointF(30, -91) <<  QPointF(26, -86) <<
                 QPointF(30, -85) <<  QPointF(38, -71) <<  QPointF(42, -72) <<  QPointF(43, -70) <<  QPointF(39, -66))

                                                                      );



        QGraphicsPolygonItem *p_westernEurope = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() << QPointF(-1, -3) <<  QPointF(1, -31) <<  QPointF(4, -32) <<  QPointF(27, -30) <<  QPointF(29, -38) <<  QPointF(30, -38) <<
                                                                                  QPointF(29, -42) <<  QPointF(28, -47) <<  QPointF(19, -50) <<  QPointF(19, -53) <<  QPointF(20, -54) <<
                                                                                  QPointF(26, -53) <<  QPointF(33, -57) <<  QPointF(37, -57) <<  QPointF(44, -64) <<  QPointF(46, -64) <<
                                                                                  QPointF(64, -54) <<  QPointF(57, -44) <<  QPointF(61, -40) <<  QPointF(61, -35) <<  QPointF(63, -31) <<
                                                                                  QPointF(59, -29) <<  QPointF(54, -29) <<  QPointF(46, -28) <<  QPointF(47, -23) <<  QPointF(42, -22) <<
                                                                                  QPointF(40, -20) <<  QPointF(33, -11) <<  QPointF(35, -8) <<  QPointF(29, -2) <<  QPointF(11, 2) <<
                                                                                  QPointF(10, 2) <<  QPointF(5, -2)

                                                                                 ));

        QGraphicsPolygonItem *p_centralEurope = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
                                                                                         QPointF(46, -64) <<  QPointF(57, -74) <<  QPointF(68, -77) <<  QPointF(66, -87) <<  QPointF(73, -91) <<  QPointF(75, -78) <<
                                                                                         QPointF(83, -79) <<  QPointF(89, -76) <<  QPointF(99, -80) <<  QPointF(103, -78) <<  QPointF(110, -82) <<
                                                                                         QPointF(115, -81) <<  QPointF(115, -78) <<  QPointF(120, -71) <<  QPointF(120, -67) <<  QPointF(122, -64) <<
                                                                                         QPointF(122, -61) <<  QPointF(117, -57) <<  QPointF(117, -50) <<  QPointF(113, -43) <<  QPointF(101, -41) <<
                                                                                         QPointF(95, -45) <<  QPointF(99, -50) <<  QPointF(98, -54) <<  QPointF(86, -54) <<  QPointF(80, -49) <<
                                                                                         QPointF(73, -46) <<  QPointF(69, -49) <<  QPointF(62, -49) <<  QPointF(64, -54) <<  QPointF(56, -56)

        ));

        QGraphicsPolygonItem *p_southernEurope = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() << QPointF(57, -44) <<  QPointF(62, -49) <<  QPointF(70, -49) <<  QPointF(73, -46) <<  QPointF(76, -50) <<  QPointF(86, -54) <<
                                                                                   QPointF(90, -55) <<  QPointF(98, -54) <<  QPointF(99, -49) <<  QPointF(96, -46) <<  QPointF(101, -42) <<
                                                                                   QPointF(114, -45) <<  QPointF(117, -50) <<  QPointF(135, -51) <<  QPointF(138, -47) <<  QPointF(142, -39) <<
                                                                                   QPointF(144, -38) <<  QPointF(140, -24) <<
                                                                                   QPointF(125, -15) <<  QPointF(122, -16) <<  QPointF(124, -9) <<  QPointF(125, -5) <<  QPointF(123, -3) <<  QPointF(121, 1) <<
                                                                                    QPointF(120, 0) <<  QPointF(118, 0) <<  QPointF(118, -2) <<  QPointF(115, -6) <<  QPointF(120, -8) <<
                                                                                    QPointF(119, -9) <<  QPointF(114, -9) <<  QPointF(110, -11) <<  QPointF(108, -15) <<  QPointF(108, -21)<<
                                                                                    QPointF(102, -27) <<  QPointF(85, -36) <<  QPointF(85, -40) <<  QPointF(80, -38) <<
                                                                                   QPointF(105, -16) <<  QPointF(97, -15) <<  QPointF(99, -9) <<  QPointF(94, -6) <<  QPointF(91, 0) <<  QPointF(82, -5) <<
                                                                                   QPointF(94, -6) <<  QPointF(94, -13) <<  QPointF(75, -27) <<  QPointF(70, -34) <<  QPointF(67, -35) <<
                                                                                   QPointF(63, -31) <<  QPointF(60, -38) <<  QPointF(60, -42) <<  QPointF(57, -44) <<  QPointF(62, -49)

                                                                                  ));


        QGraphicsPolygonItem *p_ukraine = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(145, -38) <<  QPointF(142, -38) <<  QPointF(138, -48) <<  QPointF(134, -51) <<  QPointF(132, -51) <<  QPointF(118, -50) <<
                 QPointF(117, -53) <<  QPointF(117, -56) <<  QPointF(121, -61) <<  QPointF(121, -65) <<  QPointF(120, -67) <<
                 QPointF(120, -74) <<  QPointF(116, -77) <<  QPointF(115, -78) <<  QPointF(110, -82) <<  QPointF(111, -83) <<
                 QPointF(111, -85) <<  QPointF(110, -86) <<  QPointF(110, -90) <<  QPointF(111, -92) <<  QPointF(116, -92) <<
                 QPointF(119, -90) <<  QPointF(121, -92) <<  QPointF(117, -97) <<  QPointF(118, -99) <<  QPointF(120, -100) <<
                 QPointF(131, -99) <<  QPointF(136, -102) <<  QPointF(131, -104) <<  QPointF(139, -111) <<  QPointF(139, -114) <<
                 QPointF(137, -114) <<  QPointF(134, -125) <<  QPointF(131, -130) <<  QPointF(132, -132) <<  QPointF(129, -136) <<
                 QPointF(134, -142) <<  QPointF(142, -138) <<  QPointF(144, -139) <<  QPointF(168, -132) <<  QPointF(169, -129) <<  QPointF(165, -127) <<
                 QPointF(149, -129) <<  QPointF(142, -129) <<  QPointF(158, -117) <<  QPointF(162, -119) <<  QPointF(157, -122) <<
                 QPointF(158, -123) <<  QPointF(166, -121) <<  QPointF(168, -123) <<  QPointF(167, -125) <<  QPointF(178, -129) <<
                 QPointF(176, -135) <<  QPointF(182, -134) <<  QPointF(185, -130) <<  QPointF(200, -137) <<  QPointF(224, -137) <<
                 QPointF(216, -140) <<  QPointF(218, -143) <<  QPointF(235, -139) <<  QPointF(239, -130) <<  QPointF(225, -119) <<
                 QPointF(225, -113) <<  QPointF(231, -107) <<  QPointF(235, -95) <<  QPointF(236, -86) <<  QPointF(241, -86) <<
                 QPointF(241, -82) <<  QPointF(237, -82) <<  QPointF(238, -79) <<  QPointF(242, -79) <<  QPointF(247, -80) <<
                 QPointF(245, -75) <<  QPointF(256, -64) <<  QPointF(250, -61) <<  QPointF(219, -67) <<  QPointF(214, -64) <<
                 QPointF(211, -59) <<  QPointF(208, -60) <<  QPointF(206, -52) <<  QPointF(218, -43) << QPointF(210, -34) <<
                 QPointF(214, -32) <<  QPointF(214, -29) <<  QPointF(226, -14) <<  QPointF(224, -13) <<  QPointF(223, -7) <<
                 QPointF(217, -13) <<  QPointF(212, -10) <<  QPointF(208, -10) <<  QPointF(197, -21) <<  QPointF(192, -23) <<
                 QPointF(191, -27) <<  QPointF(174, -37) <<  QPointF(178, -48) <<  QPointF(164, -42) <<  QPointF(166, -40) <<
                 QPointF(170, -40) <<  QPointF(162, -35) <<  QPointF(157, -39) <<  QPointF(159, -41) <<  QPointF(155, -42) <<
                 QPointF(153, -45)


        ));

    QGraphicsPolygonItem *p_iceland = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
             QPointF(-22, -115) <<  QPointF(-28, -119) <<  QPointF(-30, -118) <<  QPointF(-32, -119) <<  QPointF(-31, -123) <<  QPointF(-25, -124) <<
             QPointF(-23, -126) <<  QPointF(-18, -126) <<  QPointF(-16, -125) <<  QPointF(-7, -127) <<  QPointF(-3, -123) <<
             QPointF(-12, -117)
    ));

    QGraphicsPolygonItem *p_scandinavia = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(83, -83) <<  QPointF(80, -87) <<  QPointF(79, -92) <<  QPointF(74, -98) <<  QPointF(68, -94) <<  QPointF(63, -94) <<
         QPointF(59, -96) <<  QPointF(57, -99) <<  QPointF(57, -105) <<  QPointF(56, -106) <<  QPointF(59, -111) <<
         QPointF(64, -114) <<  QPointF(67, -114) <<  QPointF(80, -123) <<  QPointF(81, -127) <<  QPointF(89, -133) <<
         QPointF(90, -137) <<  QPointF(93, -138) <<  QPointF(101, -140) <<  QPointF(113, -145) <<  QPointF(119, -145) <<
         QPointF(120, -144) <<  QPointF(123, -145) <<  QPointF(134, -143) <<  QPointF(134, -141) <<  QPointF(129, -139) <<
         QPointF(130, -135) <<  QPointF(132, -132) <<  QPointF(134, -125) <<  QPointF(135, -119) <<  QPointF(140, -113) <<
         QPointF(139, -111) <<  QPointF(131, -104) <<  QPointF(117, -102) <<  QPointF(110, -106) <<  QPointF(109, -107) <<
         QPointF(109, -112) <<  QPointF(117, -123) <<  QPointF(115, -126) <<  QPointF(113, -126) <<  QPointF(104, -116) <<
         QPointF(96, -111) <<  QPointF(95, -109) <<  QPointF(102, -102) <<  QPointF(101, -98) <<  QPointF(95, -95) <<
         QPointF(92, -86) <<  QPointF(87, -83)
    ));

    QGraphicsPolygonItem *p_northAfrica = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
        QPointF(12, 4) <<  QPointF(18, 7) <<  QPointF(21, 7) <<  QPointF(25, 7) <<  QPointF(36, 1) <<  QPointF(44, -1) <<
         QPointF(64, -1) <<  QPointF(70, -3) <<  QPointF(72, -2) <<  QPointF(74, 3) <<  QPointF(76, 4) <<
         QPointF(76, 7) <<  QPointF(74, 11) <<  QPointF(77, 15) <<  QPointF(78, 18) <<  QPointF(72, 21) <<
         QPointF(72, 26) <<  QPointF(70, 40) <<  QPointF(71, 43) <<  QPointF(70, 45) <<  QPointF(71, 52) <<
         QPointF(80, 61) <<  QPointF(93, 63) <<  QPointF(95, 62) <<  QPointF(102, 63) <<  QPointF(129, 78) <<
         QPointF(129, 95) <<  QPointF(126, 95) <<  QPointF(122, 100) <<  QPointF(122, 109) <<  QPointF(126, 116) <<
         QPointF(104, 131) <<  QPointF(94, 132) <<  QPointF(90, 138) <<  QPointF(90, 142) <<  QPointF(97, 154) <<
         QPointF(95, 157) <<  QPointF(90, 157) <<  QPointF(71, 156) <<  QPointF(71, 151) <<  QPointF(64, 145) <<
         QPointF(54, 146) <<  QPointF(54, 142) <<  QPointF(46, 136) <<  QPointF(23, 144) <<  QPointF(20, 144) <<
         QPointF(15, 142) <<  QPointF(2, 146) << QPointF(-2, 146) <<  QPointF(-9, 144) <<  QPointF(-23, 131) <<  QPointF(-25, 125) <<  QPointF(-33, 113) <<  QPointF(-36, 112) <<
         QPointF(-39, 108) <<  QPointF(-37, 103) <<  QPointF(-40, 98) <<  QPointF(-40, 96) <<  QPointF(-34, 86) <<
         QPointF(-35, 76) <<  QPointF(-21, 41) <<  QPointF(-7, 30) <<  QPointF(-5, 21) <<  QPointF(7, 10) <<
         QPointF(9, 5)

    ));

    QGraphicsPolygonItem *p_egypt = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
        QPointF(78, 15) <<  QPointF(73, 21) <<  QPointF(72, 25) <<  QPointF(70, 29) <<  QPointF(72, 42) <<  QPointF(70, 45) <<
         QPointF(72, 54) <<  QPointF(80, 60) <<  QPointF(93, 64) <<  QPointF(95, 61) <<  QPointF(129, 77) <<
         QPointF(129, 75) <<  QPointF(132, 75) <<  QPointF(132, 66) <<  QPointF(167, 66) <<  QPointF(170, 67) <<
         QPointF(177, 62) <<  QPointF(162, 33) <<  QPointF(163, 32) <<  QPointF(171, 40) <<  QPointF(171, 35) <<
         QPointF(173, 35) <<  QPointF(168, 25) <<  QPointF(164, 25) <<  QPointF(155, 24) <<  QPointF(149, 26) <<
         QPointF(132, 23) <<  QPointF(122, 17) <<  QPointF(114, 17) <<  QPointF(112, 20) <<  QPointF(112, 24) <<
         QPointF(113, 24) <<  QPointF(109, 29) <<  QPointF(96, 25)
    ));

    QGraphicsPolygonItem *p_eastAfrica = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(177, 62) <<  QPointF(183, 69) <<  QPointF(183, 76) <<  QPointF(192, 88) <<  QPointF(193, 94) <<  QPointF(210, 111) <<
         QPointF(212, 117) <<  QPointF(219, 119) <<  QPointF(240, 112) <<  QPointF(242, 112) <<  QPointF(243, 122) <<
         QPointF(228, 151) <<  QPointF(207, 169) <<  QPointF(198, 179) <<  QPointF(193, 188) <<  QPointF(192, 197) <<
         QPointF(194, 203) <<  QPointF(199, 215) <<  QPointF(187, 219) <<  QPointF(181, 219) <<  QPointF(175, 218) <<
         QPointF(174, 226) <<  QPointF(178, 230) <<  QPointF(179, 237) <<  QPointF(176, 241) <<  QPointF(172, 240) <<
         QPointF(172, 236) <<  QPointF(173, 234) <<  QPointF(166, 230) <<  QPointF(167, 225) <<  QPointF(168, 219) <<
         QPointF(169, 217) <<  QPointF(167, 215) <<  QPointF(167, 210) <<  QPointF(158, 203) <<  QPointF(152, 193) <<
         QPointF(152, 187) <<  QPointF(157, 184) <<  QPointF(157, 178) <<  QPointF(159, 175) <<  QPointF(160, 171) <<
         QPointF(165, 170) <<  QPointF(173, 163) <<  QPointF(175, 158) <<  QPointF(174, 150) <<  QPointF(172, 148) <<
         QPointF(168, 148) <<  QPointF(159, 150) <<  QPointF(153, 145) <<  QPointF(152, 145) <<  QPointF(148, 147) <<
         QPointF(143, 143) <<  QPointF(143, 139) <<  QPointF(134, 129) <<  QPointF(130, 127) <<  QPointF(128, 118) <<
         QPointF(126, 115) <<  QPointF(122, 108) <<  QPointF(123, 100) <<  QPointF(126, 95) <<  QPointF(129, 95) <<
         QPointF(129, 75) <<  QPointF(132, 75) <<  QPointF(132, 66) <<  QPointF(167, 66) <<  QPointF(170, 67)

    ));

    QGraphicsPolygonItem *p_congo = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(71, 156) <<  QPointF(90, 156) <<  QPointF(90, 157) <<  QPointF(95, 156) <<  QPointF(97, 155) <<  QPointF(97, 153) <<
         QPointF(90, 142) <<  QPointF(90, 138) <<  QPointF(94, 133) <<  QPointF(104, 131) <<  QPointF(110, 126) <<
         QPointF(114, 124) <<  QPointF(125, 116) <<  QPointF(128, 118) <<  QPointF(131, 128) <<  QPointF(135, 130) <<
         QPointF(138, 136) <<  QPointF(143, 140) <<  QPointF(145, 146) <<  QPointF(147, 147) <<  QPointF(149, 147) <<
         QPointF(152, 145) <<  QPointF(153, 145) <<  QPointF(159, 150) <<  QPointF(160, 149) <<  QPointF(167, 149) <<
         QPointF(168, 149) <<  QPointF(172, 148) <<  QPointF(174, 151) <<  QPointF(176, 158) <<  QPointF(173, 163) <<
         QPointF(171, 165) <<  QPointF(165, 170) <<  QPointF(160, 172) <<  QPointF(159, 175) <<  QPointF(157, 177) <<
         QPointF(157, 183) <<  QPointF(152, 187) <<  QPointF(152, 193) <<  QPointF(158, 203) <<  QPointF(154, 203) <<
         QPointF(150, 206) <<  QPointF(148, 213) <<  QPointF(149, 219) <<  QPointF(155, 223) <<  QPointF(155, 225) <<
         QPointF(150, 226) <<  QPointF(145, 220) <<  QPointF(140, 220) <<  QPointF(136, 217) <<  QPointF(123, 216) <<
         QPointF(122, 211) <<  QPointF(121, 200) <<  QPointF(113, 198) <<  QPointF(111, 203) <<  QPointF(105, 203) <<
         QPointF(102, 200) <<  QPointF(99, 193) <<  QPointF(81, 193) <<  QPointF(79, 185) <<  QPointF(71, 177) <<
         QPointF(68, 173)
    ));

    QGraphicsPolygonItem *p_southAfrica = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(81, 193) <<  QPointF(99, 194) <<  QPointF(102, 200) <<  QPointF(104, 204) <<  QPointF(101, 202) <<  QPointF(114, 197) <<
         QPointF(121, 200) <<  QPointF(121, 210) <<  QPointF(123, 217) <<  QPointF(136, 218) <<  QPointF(141, 221) <<
         QPointF(145, 220) <<  QPointF(150, 227) <<  QPointF(153, 226) <<  QPointF(153, 225) <<  QPointF(155, 225) <<
         QPointF(156, 223) <<  QPointF(149, 219) <<  QPointF(149, 213) <<  QPointF(150, 210) <<  QPointF(151, 205) <<
         QPointF(154, 204) <<  QPointF(158, 204) <<  QPointF(167, 210) <<  QPointF(167, 216) <<  QPointF(168, 220) <<
         QPointF(168, 225) <<  QPointF(166, 230) <<  QPointF(173, 235) <<  QPointF(172, 240) <<  QPointF(176, 242) <<
         QPointF(179, 238) <<  QPointF(179, 233) <<  QPointF(178, 230) <<  QPointF(175, 226) <<  QPointF(175, 219) <<
         QPointF(175, 218) <<  QPointF(180, 219) <<  QPointF(187, 219) <<  QPointF(199, 215) <<  QPointF(198, 223) <<
         QPointF(200, 232) <<  QPointF(197, 238) <<  QPointF(193, 242) <<  QPointF(183, 247) <<  QPointF(181, 251) <<
         QPointF(174, 257) << QPointF(173, 260) <<  QPointF(173, 261) <<  QPointF(177, 268) <<  QPointF(176, 275) <<  QPointF(173, 278) <<  QPointF(165, 282) <<
         QPointF(163, 286) <<  QPointF(165, 293) <<  QPointF(162, 294) <<  QPointF(159, 297) <<  QPointF(158, 301) <<
         QPointF(151, 309) <<  QPointF(145, 315) <<  QPointF(133, 322) <<  QPointF(122, 320) <<  QPointF(114, 323) <<
         QPointF(110, 323) <<  QPointF(105, 318) <<  QPointF(105, 313) <<  QPointF(106, 310) <<  QPointF(101, 304) <<
         QPointF(100, 299) <<  QPointF(93, 290) <<  QPointF(92, 276) <<  QPointF(87, 260) <<  QPointF(80, 249) <<
         QPointF(79, 238) <<  QPointF(82, 231) <<  QPointF(84, 227) <<  QPointF(88, 218) <<  QPointF(85, 210) <<
         QPointF(86, 205) <<  QPointF(86, 202)

    ));

    QGraphicsPolygonItem *p_madagascar = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(234, 222) <<  QPointF(238, 230) <<  QPointF(238, 236) <<  QPointF(233, 251) <<  QPointF(230, 259) <<  QPointF(228, 264) <<
         QPointF(226, 274) <<  QPointF(223, 280) <<  QPointF(217, 282) <<  QPointF(214, 282) <<  QPointF(209, 280) <<
         QPointF(207, 272) <<  QPointF(207, 265) <<  QPointF(213, 257) <<  QPointF(212, 252) <<  QPointF(212, 244) <<
         QPointF(214, 239) <<  QPointF(222, 236) <<  QPointF(228, 231) <<  QPointF(231, 229)
    ));

    QGraphicsPolygonItem *p_venezuela = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-299, 159) <<  QPointF(-293, 152) <<  QPointF(-291, 145) <<  QPointF(-292, 137) <<  QPointF(-294, 132) <<  QPointF(-289, 127) <<
         QPointF(-284, 124) <<  QPointF(-281, 118) <<  QPointF(-277, 115) <<  QPointF(-273, 115) <<  QPointF(-268, 110) <<
         QPointF(-263, 110) <<  QPointF(-266, 115) <<  QPointF(-267, 124) <<  QPointF(-265, 124) <<  QPointF(-263, 121) <<
         QPointF(-265, 120) <<  QPointF(-265, 117) <<  QPointF(-259, 112) <<  QPointF(-257, 112) <<  QPointF(-252, 115) <<
         QPointF(-251, 117) <<  QPointF(-237, 120) <<  QPointF(-233, 119) <<  QPointF(-223, 124) <<  QPointF(-215, 129) <<
         QPointF(-213, 134) <<  QPointF(-206, 139) <<  QPointF(-200, 140) <<  QPointF(-195, 139) <<  QPointF(-189, 141) <<
         QPointF(-184, 147) <<  QPointF(-189, 156) <<  QPointF(-202, 155) <<  QPointF(-205, 157) <<  QPointF(-210, 157) <<
         QPointF(-217, 160) <<  QPointF(-221, 154) <<  QPointF(-219, 147) <<  QPointF(-222, 143) <<  QPointF(-232, 150) <<
         QPointF(-236, 147) <<  QPointF(-238, 148) <<  QPointF(-235, 156) <<  QPointF(-244, 163) <<  QPointF(-249, 157) <<
         QPointF(-251, 156) <<  QPointF(-253, 159) <<  QPointF(-257, 157) <<  QPointF(-260, 159) <<  QPointF(-258, 164) <<
         QPointF(-261, 166) <<  QPointF(-258, 173) <<  QPointF(-260, 186) <<  QPointF(-264, 183) <<  QPointF(-262, 179) <<
         QPointF(-266, 176) <<  QPointF(-272, 177) <<  QPointF(-278, 173) <<  QPointF(-281, 168) <<  QPointF(-289, 165)

    ));

    QGraphicsPolygonItem *p_peru = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-299, 160) <<  QPointF(-289, 165) <<  QPointF(-284, 166) <<  QPointF(-279, 169) <<  QPointF(-275, 175) <<  QPointF(-272, 177) <<
         QPointF(-266, 176) <<  QPointF(-262, 179) <<  QPointF(-264, 182) <<  QPointF(-263, 184) <<  QPointF(-272, 188) <<
         QPointF(-275, 198) <<  QPointF(-276, 200) <<  QPointF(-271, 208) <<  QPointF(-266, 211) <<  QPointF(-262, 210) <<  QPointF(-260, 215) <<
         QPointF(-256, 217) <<  QPointF(-243, 210) <<  QPointF(-238, 222) <<  QPointF(-228, 225) <<  QPointF(-220, 229) <<
         QPointF(-217, 237) <<  QPointF(-209, 240) <<  QPointF(-205, 245) <<  QPointF(-206, 253) <<  QPointF(-207, 255) <<
         QPointF(-204, 267) <<  QPointF(-188, 277) <<  QPointF(-190, 286) <<  QPointF(-192, 289) <<  QPointF(-199, 290) <<
         QPointF(-203, 289) <<  QPointF(-202, 281) <<  QPointF(-215, 274) <<  QPointF(-225, 264) <<  QPointF(-230, 267) <<
         QPointF(-239, 266) <<  QPointF(-243, 269) <<  QPointF(-249, 261) <<  QPointF(-251, 250) <<  QPointF(-255, 246) <<
         QPointF(-259, 250) <<  QPointF(-280, 236) <<  QPointF(-285, 224) <<  QPointF(-293, 216) <<  QPointF(-300, 198) <<
         QPointF(-304, 195) <<  QPointF(-308, 186) <<  QPointF(-302, 178) <<  QPointF(-306, 177) <<  QPointF(-307, 172)

    ));

    QGraphicsPolygonItem *p_argentina = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-259, 250) <<  QPointF(-255, 246) <<  QPointF(-251, 251) <<  QPointF(-248, 264) <<  QPointF(-243, 270) <<  QPointF(-239, 267) <<
         QPointF(-229, 267) <<  QPointF(-225, 265) <<  QPointF(-224, 267) <<  QPointF(-218, 272) <<  QPointF(-204, 279) <<
         QPointF(-202, 282) <<  QPointF(-204, 288) <<
         QPointF(-195, 290) <<  QPointF(-191, 288) <<  QPointF(-189, 284) <<  QPointF(-188, 280) <<  QPointF(-185, 286) <<  QPointF(-187, 291) <<
         QPointF(-191, 293) <<  QPointF(-195, 297) <<  QPointF(-196, 300) <<  QPointF(-194, 304) <<  QPointF(-184, 309) <<
         QPointF(-176, 316) <<  QPointF(-179, 322) <<  QPointF(-182, 324) <<  QPointF(-187, 324) <<  QPointF(-196, 320) <<
         QPointF(-197, 322) <<  QPointF(-192, 324) <<  QPointF(-189, 330) <<  QPointF(-188, 335) <<  QPointF(-190, 339) <<
          QPointF(-196, 342) <<  QPointF(-205, 342) <<  QPointF(-206, 344) <<  QPointF(-204, 349) <<  QPointF(-206, 353) <<
          QPointF(-214, 350) <<  QPointF(-215, 352) <<  QPointF(-208, 359) <<  QPointF(-211, 363) <<  QPointF(-210, 367) <<
          QPointF(-215, 373) <<  QPointF(-208, 380) <<  QPointF(-207, 385) <<  QPointF(-212, 396) <<  QPointF(-208, 401) <<
          QPointF(-212, 404) <<  QPointF(-209, 403) <<  QPointF(-206, 403) <<  QPointF(-195, 411) <<  QPointF(-188, 413) <<
          QPointF(-202, 415) <<  QPointF(-208, 413) <<  QPointF(-212, 410) <<  QPointF(-212, 404) <<  QPointF(-223, 402) <<
          QPointF(-228, 398) <<  QPointF(-234, 391) <<  QPointF(-238, 380) <<  QPointF(-243, 377) <<  QPointF(-243, 374) <<
          QPointF(-239, 373) <<  QPointF(-239, 367) <<  QPointF(-242, 363) <<  QPointF(-241, 358) <<  QPointF(-248, 351) <<
          QPointF(-249, 343) <<  QPointF(-251, 339) <<  QPointF(-251, 315) <<  QPointF(-255, 296) <<  QPointF(-254, 281) <<
          QPointF(-256, 274) <<  QPointF(-254, 264)

    ));

    QGraphicsPolygonItem *p_brazil = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-188, 281) <<  QPointF(-188, 277) <<  QPointF(-203, 267) <<  QPointF(-205, 260) <<  QPointF(-208, 255) <<  QPointF(-206, 253) <<
         QPointF(-204, 247) <<  QPointF(-209, 240) <<  QPointF(-216, 237) <<  QPointF(-219, 229) <<  QPointF(-231, 223) <<
         QPointF(-237, 222) <<  QPointF(-242, 210) <<  QPointF(-253, 214) <<  QPointF(-256, 217) <<  QPointF(-260, 215) <<
         QPointF(-262, 210) <<  QPointF(-267, 211) <<  QPointF(-269, 208) <<  QPointF(-271, 207) <<  QPointF(-275, 200) <<
         QPointF(-272, 189) <<  QPointF(-263, 184) <<  QPointF(-260, 186) <<  QPointF(-258, 172) <<  QPointF(-261, 166) <<
         QPointF(-257, 164) <<  QPointF(-260, 159) <<  QPointF(-255, 157) <<  QPointF(-252, 158) <<  QPointF(-249, 156) <<
         QPointF(-247, 161) <<  QPointF(-243, 163) <<  QPointF(-237, 160) <<  QPointF(-235, 156) <<  QPointF(-238, 148) <<
         QPointF(-233, 149) <<  QPointF(-222, 143) <<  QPointF(-219, 146) <<  QPointF(-221, 155) <<  QPointF(-217, 160) <<
         QPointF(-210, 158) <<  QPointF(-205, 158) <<  QPointF(-201, 155) <<  QPointF(-189, 156) <<  QPointF(-184, 147) <<
         QPointF(-179, 158) <<  QPointF(-178, 161) <<  QPointF(-187, 172) <<  QPointF(-186, 173) <<  QPointF(-178, 165) <<
         QPointF(-174, 166) <<  QPointF(-171, 170) <<  QPointF(-175, 174) <<  QPointF(-172, 174) <<  QPointF(-166, 169) <<
         QPointF(-154, 176) <<  QPointF(-156, 180) <<  QPointF(-152, 178) <<  QPointF(-133, 180) <<  QPointF(-131, 183) <<
         QPointF(-124, 188) <<  QPointF(-115, 190) <<  QPointF(-113, 200) <<  QPointF(-116, 208) <<  QPointF(-125, 223) <<
         QPointF(-130, 227) <<  QPointF(-129, 241) <<  QPointF(-132, 256) <<  QPointF(-136, 266) <<  QPointF(-140, 270) <<
         QPointF(-146, 271) <<  QPointF(-149, 270) <<  QPointF(-155, 274) <<  QPointF(-165, 281) <<  QPointF(-163, 287) <<
         QPointF(-165, 296) <<  QPointF(-168, 305) <<  QPointF(-175, 316) <<  QPointF(-184, 309) <<  QPointF(-193, 304) <<
         QPointF(-196, 299) <<  QPointF(-190, 293) <<  QPointF(-185, 285)
    ));

    QGraphicsPolygonItem *p_centralAmerica = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-295, 132) <<  QPointF(-290, 130) <<  QPointF(-289, 128) <<  QPointF(-294, 123) <<  QPointF(-300, 123) <<  QPointF(-306, 126) <<
         QPointF(-311, 124) <<  QPointF(-315, 119) <<  QPointF(-316, 117) <<  QPointF(-314, 100) <<  QPointF(-313, 96) <<
         QPointF(-314, 94) <<  QPointF(-318, 93) <<  QPointF(-324, 93) <<  QPointF(-325, 94) <<  QPointF(-334, 93) <<
         QPointF(-324, 69) <<
         //karibi

         QPointF(-314, 67) <<  QPointF(-314, 64) <<  QPointF(-307, 61) <<  QPointF(-295, 61) <<  QPointF(-279, 70) <<  QPointF(-276, 71) <<
         QPointF(-272, 74) <<

         QPointF(-269, 76) <<  QPointF(-257, 76) <<  QPointF(-254, 77) <<  QPointF(-250, 81) <<

         QPointF(-247, 82) <<  QPointF(-245, 81) <<  QPointF(-240, 81) <<  QPointF(-238, 83) <<  QPointF(-240, 85) <<  QPointF(-245, 85) <<
         QPointF(-247, 83)

         <<  QPointF(-250, 81) <<  QPointF(-262, 85) <<  QPointF(-266, 83) <<  QPointF(-269, 83) <<  QPointF(-270, 84) <<  QPointF(-273, 84) <<  QPointF(-276, 83)

         //jamajka

        << QPointF(-283, 84) <<  QPointF(-284, 85) <<  QPointF(-289, 85) <<  QPointF(-291, 84) <<  QPointF(-292, 81) <<  QPointF(-286, 82) <<
           QPointF(-283, 84)


         << QPointF(-276, 83) <<  QPointF(-276, 81) <<  QPointF(-268, 81) <<  QPointF(-267, 80) <<  QPointF(-269, 76)

         << QPointF(-272, 74) <<  QPointF(-276, 75) <<  QPointF(-280, 76) <<  QPointF(-285, 75) <<  QPointF(-290, 74) <<  QPointF(-288, 72) <<  QPointF(-299, 65) <<
         QPointF(-306, 64) <<  QPointF(-312, 67) <<  QPointF(-314, 67)


         << QPointF(-324, 69) <<  QPointF(-332, 68) <<  QPointF(-337, 70) <<  QPointF(-340, 77) <<  QPointF(-345, 81) <<  QPointF(-352, 82) <<  QPointF(-356, 83) <<
         QPointF(-360, 81) <<  QPointF(-364, 76) <<  QPointF(-366, 65) <<  QPointF(-367, 62) <<  QPointF(-362, 48) <<
         QPointF(-365, 48) <<  QPointF(-369, 41) <<  QPointF(-371, 35) <<  QPointF(-375, 31) <<  QPointF(-378, 31) <<
         QPointF(-382, 34) <<  QPointF(-386, 31) <<  QPointF(-387, 26) <<  QPointF(-392, 22) <<  QPointF(-397, 22) <<
         QPointF(-399, 24) <<  QPointF(-411, 24) <<  QPointF(-421, 19) <<  QPointF(-431, 19) <<  QPointF(-432, 28) <<
         QPointF(-427, 37) <<  QPointF(-429, 40) <<  QPointF(-428, 42) <<  QPointF(-422, 48) <<  QPointF(-423, 54) <<
         QPointF(-415, 61) <<  QPointF(-414, 59) <<  QPointF(-418, 53) <<  QPointF(-419, 42) <<  QPointF(-424, 34) <<
         QPointF(-426, 26) <<  QPointF(-424, 23) <<  QPointF(-419, 25) <<  QPointF(-418, 35) <<  QPointF(-411, 47) <<
         QPointF(-411, 50) <<  QPointF(-403, 59) <<  QPointF(-400, 66) <<  QPointF(-399, 69) <<  QPointF(-401, 73) <<
         QPointF(-401, 76) <<  QPointF(-392, 84) <<  QPointF(-368, 95) <<  QPointF(-367, 95) <<  QPointF(-360, 92) <<
         QPointF(-358, 93) <<  QPointF(-351, 97) <<  QPointF(-347, 102) <<  QPointF(-338, 106) <<  QPointF(-331, 106) <<
         QPointF(-329, 111) <<  QPointF(-325, 115) <<  QPointF(-326, 118) <<  QPointF(-321, 122) <<  QPointF(-316, 128) <<
         QPointF(-310, 129) <<  QPointF(-303, 132) <<  QPointF(-303, 128) <<  QPointF(-300, 126) <<  QPointF(-296, 126) <<
         QPointF(-292, 128)

    ));

    QGraphicsPolygonItem *p_easternUnitedStates = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-362, 48) <<  QPointF(-365, 48) <<  QPointF(-368, 44) <<  QPointF(-370, 35) <<  QPointF(-375, 31) <<  QPointF(-378, 31) <<
         QPointF(-382, 34) <<  QPointF(-383, 34) <<  QPointF(-386, 31) <<  QPointF(-387, 26) <<  QPointF(-392, 22) <<
         QPointF(-390, 21) <<  QPointF(-378, 21) <<  QPointF(-372, 0) <<  QPointF(-335, 1) <<  QPointF(-331, -10) <<
         QPointF(-334, -22) <<  QPointF(-335, -26) <<  QPointF(-329, -36) <<  QPointF(-330, -38) <<  QPointF(-328, -41) <<
         QPointF(-327, -55) <<  QPointF(-311, -55) <<  QPointF(-297, -50) <<  QPointF(-302, -47) <<  QPointF(-301, -44) <<
         QPointF(-293, -47) <<  QPointF(-290, -47) <<  QPointF(-286, -44) <<  QPointF(-283, -45) <<  QPointF(-280, -45) <<
         QPointF(-279, -42) <<  QPointF(-291, -39) <<  QPointF(-294, -35) <<  QPointF(-297, -27) <<  QPointF(-300, -25) <<
         QPointF(-298, -22) <<  QPointF(-293, -25) <<  QPointF(-289, -34) <<  QPointF(-285, -38) <<  QPointF(-282, -40) <<
         QPointF(-276, -39) <<  QPointF(-276, -37) <<  QPointF(-279, -35) <<  QPointF(-279, -32) <<  QPointF(-278, -31) <<
         QPointF(-279, -25) <<  QPointF(-280, -22) <<  QPointF(-276, -22) <<  QPointF(-269, -26) <<  QPointF(-263, -31) <<
         QPointF(-255, -31) <<  QPointF(-251, -34) <<  QPointF(-244, -38) <<  QPointF(-233, -38) <<  QPointF(-229, -39) <<
         QPointF(-223, -46) <<  QPointF(-217, -48) <<  QPointF(-215, -45) <<  QPointF(-217, -42) <<  QPointF(-216, -37) <<
         QPointF(-232, -29) <<  QPointF(-233, -24) <<  QPointF(-241, -22) <<  QPointF(-248, -20) <<  QPointF(-251, -14) <<
         QPointF(-264, -8) <<  QPointF(-265, -2) <<  QPointF(-264, 2) <<  QPointF(-266, 5) <<  QPointF(-273, 12) <<
         QPointF(-287, 19) <<  QPointF(-293, 27) <<  QPointF(-292, 42) <<  QPointF(-291, 47) <<  QPointF(-295, 52) <<
         QPointF(-298, 51) <<  QPointF(-301, 42) <<  QPointF(-300, 37) <<  QPointF(-300, 34) <<  QPointF(-304, 30) <<
         QPointF(-308, 31) <<  QPointF(-317, 27) <<  QPointF(-324, 29) <<  QPointF(-326, 34) <<  QPointF(-333, 33) <<
         QPointF(-339, 30) <<  QPointF(-345, 32) <<  QPointF(-358, 39)
    ));

    QGraphicsPolygonItem *p_westernUnitedStates = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-392, 22) <<  QPointF(-397, 22) <<  QPointF(-399, 24) <<  QPointF(-410, 24) <<  QPointF(-422, 18) <<  QPointF(-432, 18) <<
         QPointF(-433, 14) <<  QPointF(-439, 11) <<  QPointF(-441, 8) <<  QPointF(-442, -2) <<  QPointF(-443, -4) <<
         QPointF(-441, -5) <<  QPointF(-444, -8) <<  QPointF(-444, -12) <<  QPointF(-442, -14) <<  QPointF(-443, -17) <<
         QPointF(-438, -22) <<  QPointF(-435, -30) <<  QPointF(-426, -40) <<  QPointF(-424, -45) <<  QPointF(-422, -51) <<
         QPointF(-416, -51) <<  QPointF(-417, -49) <<  QPointF(-416, -47) <<  QPointF(-413, -50) <<  QPointF(-411, -55) <<
         QPointF(-327, -55) <<  QPointF(-328, -41) <<  QPointF(-330, -38) <<  QPointF(-331, -32) <<  QPointF(-335, -26) <<
         QPointF(-331, -12) <<  QPointF(-334, -1) <<  QPointF(-335, 0) <<  QPointF(-372, 0) <<  QPointF(-378, 21)

    ));

    QGraphicsPolygonItem *p_greenland = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-147, -172) <<  QPointF(-127, -174) <<  QPointF(-110, -182) <<  QPointF(-94, -183) <<  QPointF(-79, -181) <<  QPointF(-40, -186) <<
         QPointF(-34, -184) <<  QPointF(-22, -187) <<  QPointF(-8, -184) <<  QPointF(-3, -181) <<  QPointF(11, -181) <<
         QPointF(8, -178) <<  QPointF(-4, -177) <<  QPointF(-10, -171) <<  QPointF(-8, -168) <<  QPointF(-15, -158) <<
         QPointF(-27, -154) <<  QPointF(-33, -153) <<  QPointF(-22, -145) <<  QPointF(-27, -143) <<  QPointF(-35, -148) <<
         QPointF(-37, -147) <<  QPointF(-35, -144) <<  QPointF(-39, -143) <<  QPointF(-30, -142) <<  QPointF(-28, -140) <<
         QPointF(-51, -135) <<  QPointF(-56, -136) <<  QPointF(-69, -127) <<  QPointF(-86, -124) <<  QPointF(-93, -118) <<
         QPointF(-102, -106) <<  QPointF(-106, -103) <<  QPointF(-110, -103) <<  QPointF(-121, -110) <<  QPointF(-124, -116) <<
         QPointF(-122, -120) <<  QPointF(-122, -123) <<  QPointF(-124, -126) <<  QPointF(-121, -132) <<  QPointF(-111, -138) <<
         QPointF(-111, -146) <<  QPointF(-116, -150) <<  QPointF(-116, -151) <<  QPointF(-115, -153) <<  QPointF(-118, -159) <<
         QPointF(-123, -164) <<  QPointF(-134, -165) <<  QPointF(-135, -164) <<  QPointF(-147, -165)
    ));

    QGraphicsPolygonItem *p_quebec = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-250, -65) <<  QPointF(-244, -68) <<  QPointF(-241, -78) <<  QPointF(-237, -80) <<  QPointF(-227, -86) <<  QPointF(-224, -90) <<
         QPointF(-225, -98) <<  QPointF(-219, -101) <<  QPointF(-215, -109) <<  QPointF(-205, -111) <<  QPointF(-192, -104) <<
         QPointF(-193, -98) <<  QPointF(-190, -94) <<  QPointF(-176, -103) <<  QPointF(-176, -99) <<  QPointF(-174, -99) <<
         QPointF(-175, -95) <<  QPointF(-173, -90) <<  QPointF(-175, -88) <<  QPointF(-170, -79) <<  QPointF(-174, -77) <<
         QPointF(-169, -77) <<  QPointF(-163, -78) <<  QPointF(-160, -74) <<  QPointF(-162, -68) <<  QPointF(-176, -62) <<
         QPointF(-187, -60) <<  QPointF(-200, -61) <<  QPointF(-208, -58) <<  QPointF(-220, -52) <<  QPointF(-219, -51) <<
         QPointF(-208, -56) <<  QPointF(-199, -56) <<  QPointF(-205, -47) <<  QPointF(-200, -44) <<  QPointF(-196, -45) <<
         QPointF(-199, -40) <<  QPointF(-193, -42) <<  QPointF(-188, -47) <<  QPointF(-185, -43) <<  QPointF(-201, -36) <<
         QPointF(-212, -32) <<  QPointF(-214, -33) <<  QPointF(-207, -37) <<  QPointF(-204, -39) <<  QPointF(-205, -40) <<
         QPointF(-216, -37) <<  QPointF(-217, -42) <<  QPointF(-215, -45) <<  QPointF(-216, -48) <<  QPointF(-223, -45) <<
         QPointF(-229, -39) <<  QPointF(-233, -38) <<  QPointF(-244, -37) <<  QPointF(-258, -45) <<  QPointF(-258, -49)

    ));

    QGraphicsPolygonItem *p_ontario = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-277, -101) <<  QPointF(-280, -97) <<  QPointF(-277, -96) <<  QPointF(-275, -90) <<  QPointF(-263, -86) <<  QPointF(-259, -83) <<
         QPointF(-249, -80) <<  QPointF(-253, -71) <<  QPointF(-250, -65) <<  QPointF(-258, -48) <<  QPointF(-258, -45) <<
         QPointF(-244, -38) <<  QPointF(-253, -33) <<  QPointF(-257, -34) <<  QPointF(-264, -30) <<  QPointF(-269, -26) <<
         QPointF(-271, -28) <<  QPointF(-279, -24) <<  QPointF(-279, -27) <<  QPointF(-275, -31) <<  QPointF(-272, -32) <<
         QPointF(-270, -36) <<  QPointF(-266, -35) <<  QPointF(-264, -37) <<  QPointF(-269, -43) <<  QPointF(-272, -41) <<
         QPointF(-274, -41) <<  QPointF(-278, -45) <<  QPointF(-277, -47) <<  QPointF(-280, -53) <<  QPointF(-284, -54) <<
         QPointF(-295, -51) <<  QPointF(-304, -52) <<  QPointF(-311, -55) <<  QPointF(-333, -55) <<  QPointF(-304, -102)

    ));

    QGraphicsPolygonItem *p_alberta = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-304, -102) <<  QPointF(-334, -55) <<  QPointF(-411, -55) <<  QPointF(-413, -60) <<  QPointF(-420, -65) <<  QPointF(-421, -68) <<
         QPointF(-418, -71) <<  QPointF(-420, -73) <<  QPointF(-420, -76) <<  QPointF(-417, -81) <<  QPointF(-415, -81) <<
         QPointF(-412, -85) <<  QPointF(-414, -88) <<  QPointF(-412, -95) <<  QPointF(-416, -100) <<  QPointF(-423, -99) <<
         QPointF(-425, -102)
    ));

    QGraphicsPolygonItem *p_alaska = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-416, -81) <<  QPointF(-415, -81) <<  QPointF(-412, -85) <<  QPointF(-414, -89) <<  QPointF(-412, -94) <<  QPointF(-416, -100) <<
         QPointF(-423, -99) <<  QPointF(-427, -105) <<  QPointF(-383, -140) <<  QPointF(-421, -146) <<  QPointF(-441, -143) <<
         QPointF(-452, -139) <<  QPointF(-460, -138) <<  QPointF(-466, -135) <<  QPointF(-462, -130) <<  QPointF(-467, -127) <<
         QPointF(-477, -128) <<  QPointF(-481, -127) <<  QPointF(-487, -123) <<  QPointF(-479, -120) <<  QPointF(-478, -120) <<
         QPointF(-473, -122) <<  QPointF(-471, -121) <<  QPointF(-478, -116) <<  QPointF(-493, -114) <<  QPointF(-498, -111) <<
         QPointF(-499, -108) <<  QPointF(-498, -106) <<  QPointF(-499, -103) <<  QPointF(-505, -99) <<  QPointF(-499, -96) <<
         QPointF(-495, -98) <<  QPointF(-493, -97) <<  QPointF(-518, -85) <<  QPointF(-518, -84) <<  QPointF(-513, -84) <<
         QPointF(-490, -94) <<  QPointF(-483, -95) <<  QPointF(-471, -102) <<  QPointF(-468, -103) <<  QPointF(-463, -101) <<
         QPointF(-450, -106) <<  QPointF(-435, -102) <<  QPointF(-431, -102) <<  QPointF(-423, -96) <<  QPointF(-418, -94) <<
         QPointF(-416, -90) <<  QPointF(-418, -87)
    ));

    QGraphicsPolygonItem *p_northwestTerritory = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(-383, -140) <<  QPointF(-374, -138) <<  QPointF(-365, -138) <<  QPointF(-350, -142) <<  QPointF(-345, -141) <<  QPointF(-340, -143) <<
         QPointF(-334, -140) <<  QPointF(-325, -141) <<  QPointF(-313, -137) <<  QPointF(-308, -136) <<  QPointF(-311, -134) <<
         QPointF(-310, -133) <<  QPointF(-302, -133) <<  QPointF(-301, -134)

         << QPointF(-301, -136) <<  QPointF(-290, -135) <<  QPointF(-282, -139) <<  QPointF(-273, -137) <<  QPointF(-261, -142) <<  QPointF(-267, -146) <<
         QPointF(-263, -152) <<  QPointF(-264, -154) <<  QPointF(-267, -154) <<  QPointF(-272, -149) <<  QPointF(-274, -150) <<
         QPointF(-275, -154) <<  QPointF(-279, -151) <<  QPointF(-287, -153) <<  QPointF(-290, -156) <<  QPointF(-299, -159) <<
         QPointF(-307, -158) <<  QPointF(-313, -155) <<  QPointF(-323, -149) <<  QPointF(-319, -145) <<  QPointF(-315, -147) <<
         QPointF(-307, -149) <<  QPointF(-306, -150) <<  QPointF(-305, -148) <<  QPointF(-301, -147) <<  QPointF(-302, -146) <<
         QPointF(-307, -145) <<  QPointF(-306, -144) <<  QPointF(-295, -143) <<  QPointF(-297, -142) <<  QPointF(-309, -142) <<
         QPointF(-301, -136)

         << QPointF(-301, -134) <<  QPointF(-296, -134) <<  QPointF(-293, -128) <<  QPointF(-290, -133) <<  QPointF(-280, -136) <<  QPointF(-271, -133) <<  QPointF(-261, -134) <<
         QPointF(-256, -130) <<  QPointF(-252, -134)

         << QPointF(-252, -136) <<  QPointF(-247, -139) <<  QPointF(-250, -141) <<  QPointF(-253, -141) <<  QPointF(-258, -138) <<  QPointF(-255, -135) << QPointF(-252, -136)

         <<  QPointF(-252, -134) << QPointF(-243, -137) <<  QPointF(-242, -139) <<  QPointF(-246, -142) <<  QPointF(-237, -148) <<  QPointF(-239, -149) <<  QPointF(-235, -156) <<
         QPointF(-237, -157) <<  QPointF(-246, -155) <<  QPointF(-247, -152) <<  QPointF(-253, -153) <<  QPointF(-249, -149) <<
         QPointF(-248, -147) <<  QPointF(-246, -147) <<  QPointF(-239, -149) <<  QPointF(-237, -148) <<  QPointF(-233, -148) <<
         QPointF(-233, -150) <<  QPointF(-228, -152) <<  QPointF(-222, -152) <<  QPointF(-218, -155) <<  QPointF(-221, -157) <<
         QPointF(-232, -155) <<  QPointF(-234, -152) <<  QPointF(-233, -150) <<  QPointF(-233, -148) <<  QPointF(-232, -144) <<
         QPointF(-234, -141) <<  QPointF(-232, -138) <<  QPointF(-230, -139) <<  QPointF(-226, -137) <<  QPointF(-229, -133) <<
         QPointF(-227, -131) <<  QPointF(-221, -134) <<  QPointF(-215, -140) <<  QPointF(-209, -140) <<  QPointF(-206, -137) <<
         QPointF(-208, -134) <<  QPointF(-212, -129) <<  QPointF(-217, -127) <<  QPointF(-228, -127) <<  QPointF(-234, -124) <<
         QPointF(-239, -126) <<  QPointF(-241, -125) <<  QPointF(-237, -121) <<  QPointF(-252, -117) <<  QPointF(-254, -118) <<
         QPointF(-254, -115) <<  QPointF(-263, -110) <<  QPointF(-270, -107) <<  QPointF(-277, -102) <<  QPointF(-424, -102) <<
         QPointF(-427, -105)

    ));

    QGraphicsPolygonItem *p_westernAustralia = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(580, 339) <<  QPointF(577, 336) <<  QPointF(579, 332) <<  QPointF(577, 327) <<  QPointF(577, 323) <<  QPointF(573, 327) <<
         QPointF(572, 325) <<  QPointF(578, 318) <<  QPointF(575, 317) <<  QPointF(567, 314) <<  QPointF(563, 315) <<
         QPointF(556, 310) <<  QPointF(530, 314) <<  QPointF(521, 319) <<  QPointF(505, 321) <<  QPointF(495, 325) <<
         QPointF(487, 322) <<  QPointF(486, 320) <<  QPointF(489, 318) <<  QPointF(493, 310) <<  QPointF(491, 300) <<
         QPointF(492, 283) <<  QPointF(493, 280) <<  QPointF(492, 277) <<  QPointF(495, 266) <<  QPointF(507, 261) <<
         QPointF(517, 257) <<  QPointF(522, 258) <<  QPointF(527, 255) <<  QPointF(531, 251) <<  QPointF(535, 243) <<
         QPointF(539, 245) <<  QPointF(539, 240) <<  QPointF(544, 238) <<  QPointF(548, 232) <<  QPointF(555, 229) <<
         QPointF(562, 234) <<  QPointF(549, 283) <<  QPointF(599, 286)
    ));

    QGraphicsPolygonItem *p_easternAustralia = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(562, 234) <<  QPointF(564, 236) <<  QPointF(565, 231) <<  QPointF(569, 224) <<  QPointF(575, 223) <<  QPointF(581, 219) <<
         QPointF(595, 224) <<  QPointF(590, 231) <<  QPointF(591, 236) <<  QPointF(598, 240) <<  QPointF(604, 245) <<
         QPointF(606, 247) <<  QPointF(615, 237) <<  QPointF(619, 217) <<  QPointF(622, 217) <<  QPointF(625, 229) <<
         QPointF(630, 232) <<  QPointF(632, 245) <<  QPointF(630, 250) <<  QPointF(637, 256) <<  QPointF(643, 271) <<
         QPointF(651, 281) <<  QPointF(649, 298) <<  QPointF(643, 310) <<  QPointF(635, 316) <<  QPointF(627, 323) <<
         QPointF(623, 328) <<  QPointF(615, 336) <<  QPointF(614, 339) <<  QPointF(609, 338) <<  QPointF(602, 341) <<
         QPointF(598, 344) <<  QPointF(599, 352) <<  QPointF(600, 354) <<  QPointF(598, 358) <<  QPointF(589, 364) <<
         QPointF(584, 363) <<  QPointF(586, 357) <<  QPointF(586, 351) <<  QPointF(595, 353) <<  QPointF(599, 352) <<
         QPointF(598, 344) <<  QPointF(593, 340) <<  QPointF(589, 342) <<  QPointF(580, 339) <<  QPointF(599, 286) <<
         QPointF(549, 283)
    ));

    QGraphicsPolygonItem *p_middleEast = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(140, -24) <<  QPointF(144, -20) <<  QPointF(149, -21) <<  QPointF(153, -20) <<  QPointF(160, -24) <<  QPointF(172, -22) <<
         QPointF(177, -19) <<  QPointF(183, -18) <<  QPointF(189, -19) <<  QPointF(192, -23) <<  QPointF(197, -21) <<
         QPointF(199, -17) <<  QPointF(205, -12) <<  QPointF(208, -10) <<  QPointF(212, -10) <<  QPointF(216, -13) <<
         QPointF(222, -7) <<  QPointF(236, 2) <<  QPointF(243, -3) <<  QPointF(253, -7) <<  QPointF(270, -1) <<
         QPointF(274, 5) <<  QPointF(271, 11) <<  QPointF(275, 23) <<  QPointF(278, 26) <<  QPointF(277, 32) <<
         QPointF(284, 40) <<  QPointF(285, 44) <<  QPointF(281, 48) <<  QPointF(282, 52) <<  QPointF(279, 53) <<
         QPointF(266, 51) <<  QPointF(260, 44) <<  QPointF(250, 46) <<  QPointF(238, 40) <<  QPointF(235, 31) <<
         QPointF(230, 29) <<  QPointF(225, 33) <<  QPointF(231, 42) <<  QPointF(235, 52) <<  QPointF(237, 52) <<
         QPointF(238, 49) <<  QPointF(241, 49) <<  QPointF(242, 53) <<  QPointF(241, 55) <<  QPointF(245, 57) <<
         QPointF(251, 56) <<  QPointF(257, 50) <<  QPointF(259, 47) <<  QPointF(260, 53) <<  QPointF(268, 58) <<
         QPointF(275, 65) <<  QPointF(275, 68) <<  QPointF(269, 73) <<  QPointF(267, 79) <<  QPointF(260, 87) <<
         QPointF(257, 89) <<  QPointF(248, 91) <<  QPointF(244, 97) <<  QPointF(221, 108) <<  QPointF(213, 109) <<
         QPointF(209, 102) <<  QPointF(207, 91) <<  QPointF(202, 86) <<  QPointF(200, 81) <<  QPointF(193, 74) <<
         QPointF(190, 62) <<  QPointF(185, 57) <<  QPointF(184, 54) <<  QPointF(175, 45) <<  QPointF(173, 35) <<
         QPointF(168, 24) <<  QPointF(170, 25) <<  QPointF(174, 1) <<  QPointF(173, 0) <<  QPointF(164, 4) <<
         QPointF(160, 4) <<  QPointF(155, 1) <<  QPointF(153, 0) <<  QPointF(150, 2) <<  QPointF(143, 1) <<
         QPointF(140, -1) <<  QPointF(138, -6) <<  QPointF(138, -10) <<  QPointF(134, -12) <<  QPointF(134, -15) <<
         QPointF(139, -16) <<  QPointF(141, -14) <<  QPointF(144, -17) <<  QPointF(144, -20) <<  QPointF(135, -17) <<
         QPointF(135, -22) <<  QPointF(136, -24)
    ));

    QGraphicsPolygonItem *p_ural = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(234, -138) <<  QPointF(247, -136) <<  QPointF(249, -134) <<  QPointF(251, -137) <<  QPointF(242, -141) <<  QPointF(240, -145) <<
         QPointF(240, -147) <<  QPointF(246, -151) <<  QPointF(251, -151) <<  QPointF(255, -147) <<  QPointF(258, -142) <<
         QPointF(265, -134) <<  QPointF(262, -127) <<  QPointF(263, -126) <<  QPointF(269, -129) <<  QPointF(270, -134) <<
         QPointF(263, -140) <<  QPointF(260, -145) <<  QPointF(260, -148) <<  QPointF(266, -147) <<  QPointF(273, -149) <<
         QPointF(276, -145) <<  QPointF(280, -142) <<  QPointF(278, -140) <<  QPointF(281, -137) <<  QPointF(286, -138) <<
         QPointF(291, -134) <<  QPointF(295, -129) <<  QPointF(302, -124) <<  QPointF(304, -124) <<  QPointF(308, -121) <<
         QPointF(311, -121) <<  QPointF(315, -117) <<  QPointF(316, -114) <<  QPointF(315, -110) <<  QPointF(321, -107) <<
         QPointF(323, -102) <<  QPointF(338, -99) <<  QPointF(337, -94) <<  QPointF(342, -93) <<  QPointF(344, -90) <<
         QPointF(331, -86) <<  QPointF(338, -78) <<  QPointF(345, -72) <<  QPointF(344, -68) <<  QPointF(335, -62) <<
         QPointF(344, -58) <<  QPointF(349, -51) <<  QPointF(350, -47) <<  QPointF(345, -46) <<  QPointF(342, -44) <<
         QPointF(337, -49) <<  QPointF(325, -58) <<  QPointF(322, -63) <<  QPointF(320, -67) <<  QPointF(311, -71) <<
         QPointF(309, -75) <<  QPointF(303, -78) <<  QPointF(298, -74) <<  QPointF(286, -77) <<  QPointF(281, -82) <<
         QPointF(254, -76) <<  QPointF(252, -68) <<  QPointF(245, -75) <<  QPointF(248, -78) <<  QPointF(247, -80) <<
         QPointF(238, -79) <<  QPointF(236, -81) <<  QPointF(241, -83) <<  QPointF(241, -86) <<  QPointF(236, -86) <<
         QPointF(233, -89) <<  QPointF(235, -95) <<  QPointF(231, -99) <<  QPointF(231, -106) <<  QPointF(225, -113) <<
         QPointF(225, -119) <<  QPointF(239, -130)
    ));

    QGraphicsPolygonItem *p_siberia = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(273, -150) <<  QPointF(281, -155) <<  QPointF(288, -155) <<  QPointF(291, -157) <<  QPointF(289, -158) <<  QPointF(289, -160) <<
         QPointF(312, -164) <<  QPointF(315, -163) <<  QPointF(322, -169) <<  QPointF(329, -168) <<  QPointF(336, -165) <<
         QPointF(350, -166) <<  QPointF(360, -161) <<  QPointF(360, -159) <<  QPointF(350, -154) <<  QPointF(351, -152) <<
         QPointF(360, -155) <<  QPointF(371, -146) <<  QPointF(369, -142) <<  QPointF(364, -140) <<  QPointF(369, -134) <<
         QPointF(371, -130) <<  QPointF(376, -126) <<  QPointF(377, -123) <<  QPointF(385, -119) <<  QPointF(383, -115) <<
         QPointF(388, -110) <<  QPointF(386, -104) <<  QPointF(390, -102) <<  QPointF(393, -98) <<  QPointF(389, -97) <<
         QPointF(388, -98) <<  QPointF(382, -92) <<  QPointF(376, -93) <<  QPointF(374, -90) <<  QPointF(376, -86) <<
         QPointF(375, -78) <<  QPointF(377, -76) <<  QPointF(369, -73) <<  QPointF(367, -68) <<  QPointF(358, -70) <<
         QPointF(354, -65) <<  QPointF(358, -57) <<  QPointF(353, -56) <<  QPointF(349, -52) <<  QPointF(345, -57) <<
         QPointF(344, -58) <<  QPointF(335, -63) <<  QPointF(345, -71) <<  QPointF(339, -77) <<  QPointF(331, -86) <<
         QPointF(344, -89) <<  QPointF(342, -93) <<  QPointF(337, -94) <<  QPointF(338, -98) <<  QPointF(323, -102) <<
         QPointF(316, -110) <<  QPointF(316, -114) <<  QPointF(314, -116) <<  QPointF(311, -121) <<  QPointF(308, -120) <<
         QPointF(308, -121) <<  QPointF(304, -124) <<  QPointF(302, -124) <<  QPointF(292, -132) <<  QPointF(291, -134) <<
         QPointF(286, -138) <<  QPointF(281, -137) <<  QPointF(278, -140) <<  QPointF(280, -142) <<  QPointF(276, -145)

    ));

    QGraphicsPolygonItem *p_yakutsk = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(360, -154) <<  QPointF(363, -156) <<  QPointF(373, -153) <<  QPointF(379, -155) <<  QPointF(392, -152) <<  QPointF(401, -154) <<
         QPointF(409, -154) <<  QPointF(417, -151) <<  QPointF(428, -144) <<  QPointF(435, -147) <<  QPointF(446, -145) <<
         QPointF(452, -148) <<  QPointF(450, -150) <<  QPointF(456, -152) <<  QPointF(467, -151) <<  QPointF(472, -148) <<
         QPointF(475, -150) <<  QPointF(487, -145) <<  QPointF(508, -144) <<  QPointF(514, -145) <<  QPointF(522, -141) <<
         QPointF(531, -140) <<  QPointF(527, -135) <<  QPointF(534, -131) <<  QPointF(534, -129) <<  QPointF(523, -130) <<
         QPointF(523, -125) <<  QPointF(525, -122) <<  QPointF(516, -123) <<  QPointF(513, -121) <<  QPointF(510, -121) <<
         QPointF(507, -119) <<  QPointF(513, -113) <<  QPointF(500, -113) <<  QPointF(496, -108) <<  QPointF(499, -103) <<
         QPointF(497, -100) <<  QPointF(494, -101) <<  QPointF(491, -99) <<  QPointF(487, -99) <<  QPointF(484, -96) <<
         QPointF(484, -93) <<  QPointF(488, -88) <<  QPointF(488, -84) <<  QPointF(463, -85) <<  QPointF(454, -89) <<
         QPointF(450, -88) <<  QPointF(444, -91) <<  QPointF(439, -96) <<  QPointF(435, -101) <<  QPointF(429, -101) <<
         QPointF(424, -104) <<  QPointF(421, -104) <<  QPointF(418, -99) <<  QPointF(413, -100) <<  QPointF(405, -99) <<
         QPointF(404, -107) <<  QPointF(395, -113) <<  QPointF(388, -118) <<  QPointF(377, -123) <<  QPointF(376, -125) <<
         QPointF(371, -131) <<  QPointF(370, -133) <<  QPointF(364, -139) <<  QPointF(364, -140) <<  QPointF(369, -142) <<
         QPointF(371, -147)
    ));

    QGraphicsPolygonItem *p_irkutsk = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(385, -119) <<  QPointF(398, -110) <<  QPointF(404, -107) <<  QPointF(405, -99) <<  QPointF(414, -100) <<  QPointF(418, -99) <<
         QPointF(421, -104) <<  QPointF(425, -104) <<  QPointF(430, -99) <<  QPointF(431, -101) <<  QPointF(435, -100) <<
         QPointF(439, -96) <<  QPointF(444, -91) <<  QPointF(450, -88) <<  QPointF(453, -89) <<  QPointF(465, -86) <<
         QPointF(480, -83) << QPointF(490, -84) <<  QPointF(491, -83) <<  QPointF(497, -83) <<  QPointF(493, -77) <<  QPointF(500, -73) <<  QPointF(504, -73) <<
         QPointF(506, -75) <<  QPointF(510, -74) <<  QPointF(510, -70) <<  QPointF(504, -64) <<  QPointF(504, -63) <<
         QPointF(513, -55) <<  QPointF(511, -53) <<  QPointF(500, -56) <<  QPointF(490, -64) <<  QPointF(484, -71) <<
         QPointF(470, -75) <<  QPointF(462, -72) <<  QPointF(466, -67) <<  QPointF(465, -63) <<  QPointF(466, -60) <<
         QPointF(459, -56) <<  QPointF(449, -59) <<  QPointF(439, -56) <<  QPointF(417, -61) <<  QPointF(413, -60) <<
         QPointF(401, -64) <<  QPointF(392, -68) <<  QPointF(388, -65) <<  QPointF(391, -61) <<  QPointF(385, -59) <<
         QPointF(370, -63) <<  QPointF(363, -61) <<  QPointF(358, -57) <<  QPointF(354, -65) <<  QPointF(358, -69) <<
         QPointF(362, -67) <<  QPointF(366, -67) <<  QPointF(370, -74) <<  QPointF(377, -76) <<  QPointF(375, -78) <<
         QPointF(377, -81) <<  QPointF(375, -85) <<  QPointF(376, -87) <<  QPointF(374, -90) <<  QPointF(377, -93) <<
         QPointF(382, -92) <<  QPointF(388, -98) <<  QPointF(393, -97) <<  QPointF(390, -101) <<  QPointF(390, -102) <<
         QPointF(386, -104) <<  QPointF(386, -106) <<  QPointF(388, -109) <<  QPointF(383, -115)

    ));

    QGraphicsPolygonItem *p_afghanistan = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(251, -68) <<  QPointF(254, -73) <<  QPointF(253, -75) <<  QPointF(257, -77) <<  QPointF(260, -77) <<  QPointF(278, -82) <<
         QPointF(284, -80) <<  QPointF(287, -78) <<  QPointF(294, -77) <<  QPointF(298, -75) <<  QPointF(303, -78) <<
         QPointF(310, -72) <<  QPointF(320, -68) <<  QPointF(322, -63) <<  QPointF(324, -60) <<  QPointF(337, -50) <<
         QPointF(342, -44) <<  QPointF(341, -41) <<  QPointF(334, -36) <<  QPointF(339, -29) <<  QPointF(338, -25) <<
         QPointF(334, -21) <<  QPointF(324, -16) <<  QPointF(323, -17) <<  QPointF(316, -13) <<  QPointF(322, -9) <<
         QPointF(323, -3) <<  QPointF(313, -2) <<  QPointF(312, -5) <<  QPointF(307, -8) <<  QPointF(305, -5) <<
         QPointF(298, -1) <<  QPointF(291, -4) <<  QPointF(286, -2) <<  QPointF(284, 3) <<  QPointF(276, 6) <<
         QPointF(274, 5) <<  QPointF(272, 0) <<  QPointF(253, -7) <<  QPointF(243, -3) <<  QPointF(242, -9) <<
         QPointF(236, -17) <<  QPointF(238, -18) <<  QPointF(239, -17) <<  QPointF(243, -19) <<  QPointF(238, -25) <<
         QPointF(235, -23) <<  QPointF(233, -26) <<  QPointF(227, -28) <<  QPointF(224, -32) <<  QPointF(231, -39) <<
         QPointF(234, -38) <<  QPointF(235, -39) <<  QPointF(233, -41) <<  QPointF(226, -46) <<  QPointF(218, -43) <<
         QPointF(215, -46) <<  QPointF(206, -52) <<  QPointF(206, -57) <<  QPointF(209, -60) <<  QPointF(211, -59) <<
         QPointF(212, -62) <<  QPointF(220, -67) <<  QPointF(235, -62) <<  QPointF(242, -64) <<  QPointF(251, -61) <<
         QPointF(256, -64)
    ));

    QGraphicsPolygonItem *p_india = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(273, 5) <<  QPointF(276, 6) <<  QPointF(284, 3) <<  QPointF(286, -2) <<  QPointF(290, -4) <<  QPointF(298, -1) <<
         QPointF(304, -3) <<  QPointF(307, -8) <<  QPointF(312, -5) <<  QPointF(313, -2) <<  QPointF(321, -4) <<
         QPointF(336, 6) <<  QPointF(345, 7) <<  QPointF(347, 11) <<  QPointF(345, 14) <<  QPointF(346, 17) <<
         QPointF(344, 21) <<  QPointF(346, 24) <<  QPointF(356, 29) <<  QPointF(361, 29) <<  QPointF(371, 35) <<
         QPointF(375, 36) <<  QPointF(378, 35) <<  QPointF(385, 40) <<  QPointF(389, 39) <<  QPointF(391, 41) <<  QPointF(394, 38) <<
         QPointF(401, 42) <<  QPointF(405, 41) <<  QPointF(407, 37) <<  QPointF(414, 34) <<  QPointF(424, 39) <<
         QPointF(422, 42) <<  QPointF(416, 47) <<  QPointF(412, 61) <<  QPointF(412, 67) <<  QPointF(407, 70) <<
         QPointF(405, 66) <<  QPointF(402, 64) <<  QPointF(388, 68) <<  QPointF(387, 75) <<  QPointF(379, 79) <<
         QPointF(378, 84) <<  QPointF(372, 86) <<  QPointF(370, 91) <<  QPointF(365, 93) <<  QPointF(361, 97) <<
         QPointF(363, 106) <<  QPointF(361, 113) <<  QPointF(361, 119) <<  QPointF(363, 123) <<  QPointF(369, 129) <<
         QPointF(371, 135) <<  QPointF(369, 138) <<  QPointF(365, 139) <<  QPointF(363, 137) <<  QPointF(362, 127) <<
         QPointF(363, 123) <<  QPointF(361, 119) <<  QPointF(353, 129) <<  QPointF(347, 126) <<  QPointF(346, 120) <<
         QPointF(337, 102) <<  QPointF(331, 87) <<  QPointF(328, 76) <<  QPointF(329, 72) <<  QPointF(327, 66) <<
         QPointF(325, 68) <<  QPointF(326, 71) <<  QPointF(324, 72) <<  QPointF(319, 72) <<  QPointF(313, 66) <<
         QPointF(317, 64) <<  QPointF(316, 62) <<  QPointF(313, 63) <<  QPointF(305, 58) <<  QPointF(303, 53) <<
         QPointF(298, 51) <<  QPointF(292, 53) <<  QPointF(282, 52) <<  QPointF(281, 48) <<  QPointF(285, 43) <<
         QPointF(284, 40) <<  QPointF(278, 34) <<  QPointF(277, 29) <<  QPointF(278, 26) <<  QPointF(275, 24) <<
         QPointF(271, 12)

    ));

    QGraphicsPolygonItem *p_siam = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(407, 71) <<  QPointF(412, 67) <<  QPointF(411, 62) <<  QPointF(414, 55) <<  QPointF(415, 47) <<  QPointF(424, 39) <<
         QPointF(429, 43) <<  QPointF(431, 47) <<  QPointF(428, 54) <<  QPointF(430, 58) <<  QPointF(434, 60) <<
         QPointF(439, 69) <<  QPointF(446, 70) <<  QPointF(446, 66) <<  QPointF(448, 64) <<  QPointF(459, 61) <<
         QPointF(467, 67) <<  QPointF(471, 69) <<  QPointF(466, 74) <<  QPointF(464, 78) <<  QPointF(467, 84) <<
         QPointF(473, 88) <<  QPointF(477, 95) <<  QPointF(481, 102) <<  QPointF(483, 111) <<  QPointF(481, 117) <<
         QPointF(473, 120) <<  QPointF(471, 125) <<  QPointF(467, 127) <<  QPointF(465, 125) <<  QPointF(466, 123) <<
         QPointF(466, 121) <<  QPointF(464, 119) <<  QPointF(461, 120) <<  QPointF(457, 114) <<  QPointF(451, 110) <<
         QPointF(445, 105) <<  QPointF(443, 106) <<  QPointF(444, 112) <<  QPointF(442, 120) <<  QPointF(446, 128) <<
         QPointF(447, 132) <<  QPointF(455, 139) <<  QPointF(458, 141) <<  QPointF(461, 147) <<  QPointF(464, 160) <<
         QPointF(461, 160) <<  QPointF(454, 155) <<  QPointF(448, 146) <<  QPointF(446, 135) <<  QPointF(437, 129) <<
         QPointF(439, 120) <<  QPointF(438, 118) <<  QPointF(439, 111) <<  QPointF(435, 104) <<  QPointF(432, 91) <<
         QPointF(429, 90) <<  QPointF(424, 95) <<  QPointF(419, 92) <<  QPointF(419, 89) <<  QPointF(420, 88) <<
         QPointF(415, 77) <<  QPointF(408, 74)
    ));

    QGraphicsPolygonItem *p_mongolia = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(355, -55) <<  QPointF(363, -61) <<  QPointF(369, -63) <<  QPointF(384, -59) <<  QPointF(391, -61) <<  QPointF(388, -64) <<
         QPointF(392, -68) <<  QPointF(397, -66) <<  QPointF(400, -66) <<  QPointF(412, -60) <<  QPointF(418, -61) <<
         QPointF(436, -56) <<  QPointF(440, -56) <<  QPointF(447, -59) <<  QPointF(454, -58) <<  QPointF(459, -56) <<
         QPointF(466, -60) <<  QPointF(465, -64) <<  QPointF(466, -66) <<  QPointF(462, -72) <<  QPointF(472, -75) <<
         QPointF(483, -72) <<  QPointF(490, -64) <<  QPointF(495, -60) <<  QPointF(500, -56) <<  QPointF(511, -53) <<
         QPointF(516, -49) <<  QPointF(521, -48) <<  QPointF(527, -52) <<  QPointF(530, -49) <<  QPointF(529, -47) <<
         QPointF(532, -43) <<  QPointF(525, -36) <<  QPointF(529, -27) <<  QPointF(530, -25) <<  QPointF(528, -22) <<
         QPointF(530, -18) <<  QPointF(527, -14) <<  QPointF(524, -12) <<  QPointF(537, -2) <<  QPointF(541, 4) <<
         QPointF(541, 7) <<  QPointF(532, 11) <<  QPointF(527, 0) <<  QPointF(524, -3) <<  QPointF(518, -5) <<
         QPointF(516, -7) <<  QPointF(517, -10) <<  QPointF(511, -14) <<  QPointF(504, -10) <<  QPointF(501, -13) <<
         QPointF(501, -16) <<  QPointF(498, -18) <<  QPointF(494, -15) <<  QPointF(489, -18) <<  QPointF(484, -22) <<
         QPointF(481, -27) <<  QPointF(477, -26) <<  QPointF(476, -24) <<  QPointF(473, -23) <<  QPointF(472, -22) <<
         QPointF(468, -25) <<  QPointF(469, -17) <<  QPointF(463, -15) <<  QPointF(456, -13) <<  QPointF(453, -6) <<
         QPointF(449, -5) <<  QPointF(446, -7) <<  QPointF(443, -8) <<  QPointF(444, -10) <<  QPointF(442, -12) <<
         QPointF(440, -8) <<  QPointF(441, -6) <<  QPointF(437, -4) <<  QPointF(432, -6) <<  QPointF(433, -10) <<
         QPointF(431, -13) <<  QPointF(423, -10) <<  QPointF(415, -15) <<  QPointF(416, -19) <<  QPointF(409, -18) <<
         QPointF(402, -26) <<  QPointF(385, -37) <<  QPointF(379, -35) <<  QPointF(372, -41) <<  QPointF(367, -48) <<
         QPointF(359, -52)
    ));

    QGraphicsPolygonItem *p_china = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(495, -14) <<  QPointF(488, -9) <<  QPointF(498, -1) <<  QPointF(501, -5) <<  QPointF(510, -2) <<  QPointF(504, 2) <<
         QPointF(501, 10) <<  QPointF(506, 12) <<  QPointF(510, 20) <<  QPointF(516, 24) <<  QPointF(517, 28) <<
         QPointF(514, 30) <<  QPointF(520, 32) <<  QPointF(515, 53) <<  QPointF(520, 56) <<  QPointF(519, 60) <<
         QPointF(521, 65) <<  QPointF(525, 66) <<  QPointF(527, 57) <<  QPointF(526, 52) <<  QPointF(524, 53) <<
         QPointF(520, 56) <<  QPointF(515, 53) <<  QPointF(510, 60) <<  QPointF(497, 66) <<  QPointF(487, 68) <<
         QPointF(482, 74) <<  QPointF(480, 76) <<  QPointF(485, 77) <<  QPointF(483, 82) <<  QPointF(480, 84) <<
         QPointF(477, 82) <<  QPointF(477, 79) <<  QPointF(479, 76) <<  QPointF(480, 76) <<  QPointF(482, 74) <<
         QPointF(480, 73) <<  QPointF(478, 69) <<  QPointF(471, 69) <<  QPointF(467, 67) <<  QPointF(462, 61) <<
         QPointF(450, 64) <<  QPointF(447, 64) <<  QPointF(447, 70) <<  QPointF(439, 69) <<  QPointF(434, 60) <<
         QPointF(430, 58) <<  QPointF(428, 55) <<  QPointF(432, 47) <<  QPointF(429, 41) <<  QPointF(421, 38) <<
         QPointF(412, 34) <<  QPointF(407, 37) <<  QPointF(403, 41) <<  QPointF(401, 42) <<  QPointF(395, 38) <<
         QPointF(393, 38) <<  QPointF(391, 42) <<  QPointF(387, 39) <<  QPointF(386, 40) <<  QPointF(378, 35) <<
         QPointF(375, 36) <<  QPointF(362, 29) <<  QPointF(356, 30) <<  QPointF(346, 24) <<  QPointF(344, 21) <<
         QPointF(346, 17) <<  QPointF(345, 15) <<  QPointF(347, 11) <<  QPointF(345, 8) <<  QPointF(338, 6) <<
         QPointF(322, -3) <<  QPointF(323, -4) <<  QPointF(321, -9) <<  QPointF(316, -13) <<  QPointF(322, -17) <<
         QPointF(324, -16) <<  QPointF(334, -20) <<  QPointF(338, -25) <<  QPointF(339, -28) <<  QPointF(334, -36) <<
         QPointF(341, -40) <<  QPointF(342, -45) <<  QPointF(350, -46) <<  QPointF(349, -52) <<  QPointF(353, -56) <<
         QPointF(362, -49) <<  QPointF(368, -48) <<  QPointF(374, -38) <<  QPointF(379, -35) <<  QPointF(384, -37) <<
         QPointF(394, -32) <<  QPointF(402, -26) <<  QPointF(406, -20) <<  QPointF(409, -18) <<  QPointF(416, -19) <<
         QPointF(415, -16) <<  QPointF(423, -10) <<  QPointF(428, -12) <<  QPointF(431, -12) <<  QPointF(433, -10) <<
         QPointF(432, -8) <<  QPointF(436, -4) <<  QPointF(441, -6) <<  QPointF(441, -9) <<  QPointF(442, -12) <<
         QPointF(444, -9) <<  QPointF(443, -8) <<  QPointF(449, -5) <<  QPointF(453, -5) <<  QPointF(453, -8) <<
         QPointF(457, -12) <<  QPointF(467, -17) <<  QPointF(469, -18) <<  QPointF(467, -23) <<  QPointF(468, -24) <<
         QPointF(472, -22) <<  QPointF(476, -24) <<  QPointF(479, -27) <<  QPointF(486, -21)
    ));

    QGraphicsPolygonItem *p_japan = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(581, 7) <<  QPointF(571, 10) <<  QPointF(568, 16) <<  QPointF(564, 10) <<  QPointF(558, 11) <<  QPointF(559, 12) <<
         QPointF(562, 13) <<  QPointF(562, 16) <<  QPointF(559, 18) <<  QPointF(556, 16) <<  QPointF(557, 14) <<
         QPointF(559, 12) <<  QPointF(558, 11) <<  QPointF(551, 12) <<  QPointF(549, 13) <<  QPointF(554, 17) <<
         QPointF(555, 22) <<  QPointF(553, 25) <<  QPointF(551, 24) <<  QPointF(550, 20) <<  QPointF(546, 16) <<
         QPointF(548, 13) <<  QPointF(549, 13) <<  QPointF(551, 12) <<  QPointF(548, 10) <<  QPointF(555, 5) <<
         QPointF(560, 5) <<  QPointF(570, -2) <<  QPointF(574, -7) <<  QPointF(569, -18) <<  QPointF(570, -20) <<
         QPointF(569, -21) <<  QPointF(563, -27) <<  QPointF(566, -31) <<  QPointF(563, -39) <<  QPointF(568, -37) <<
         QPointF(570, -33) <<  QPointF(582, -29) <<  QPointF(579, -26) <<  QPointF(578, -24) <<  QPointF(569, -26) <<
         QPointF(569, -21) <<  QPointF(570, -20) <<  QPointF(578, -16) <<  QPointF(581, -9) <<  QPointF(580, -6) <<
         QPointF(583, 2)
    ));

    QGraphicsPolygonItem *p_kamchatka = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(530, -25) <<  QPointF(525, -36) <<  QPointF(532, -43) <<  QPointF(529, -47) <<  QPointF(530, -49) <<  QPointF(527, -52) <<
         QPointF(520, -48) <<  QPointF(515, -49) <<  QPointF(511, -53) <<  QPointF(513, -55) <<  QPointF(504, -64) <<
         QPointF(510, -70) <<  QPointF(510, -73) <<  QPointF(508, -75) <<  QPointF(506, -75) <<  QPointF(503, -73) <<
         QPointF(500, -73) <<  QPointF(493, -77) <<  QPointF(497, -81) <<  QPointF(497, -82) <<  QPointF(490, -83) <<
         QPointF(488, -86) <<  QPointF(488, -88) <<  QPointF(484, -93) <<  QPointF(484, -95) <<  QPointF(487, -99) <<
         QPointF(490, -99) <<  QPointF(494, -101) <<  QPointF(496, -99) <<  QPointF(499, -103) <<  QPointF(496, -109) <<
         QPointF(500, -113) <<  QPointF(508, -113) <<  QPointF(511, -112) <<  QPointF(512, -113) <<  QPointF(507, -119) <<
         QPointF(510, -121) <<  QPointF(513, -121) <<  QPointF(516, -123) <<  QPointF(519, -122) <<  QPointF(525, -122) <<
         QPointF(523, -125) <<  QPointF(523, -130) <<  QPointF(534, -129) <<  QPointF(534, -131) <<  QPointF(527, -135) <<
         QPointF(532, -140) <<  QPointF(536, -141) <<  QPointF(556, -137) <<  QPointF(558, -138) <<  QPointF(554, -142) <<
         QPointF(589, -137) <<  QPointF(598, -134) <<  QPointF(609, -132) <<  QPointF(617, -128) <<  QPointF(623, -130) <<
         QPointF(635, -122) <<  QPointF(631, -120) <<  QPointF(621, -122) <<  QPointF(620, -124) <<  QPointF(618, -123) <<
         QPointF(609, -126) <<  QPointF(607, -125) <<  QPointF(610, -121) <<  QPointF(601, -122) <<  QPointF(602, -121) <<
         QPointF(621, -113) <<  QPointF(618, -110) <<  QPointF(614, -111) <<  QPointF(608, -106) <<  QPointF(603, -102) <<
         QPointF(598, -105) <<  QPointF(593, -102) <<  QPointF(586, -101) <<  QPointF(584, -99) <<  QPointF(588, -92) <<
         QPointF(593, -91) <<  QPointF(597, -88) <<  QPointF(599, -82) <<  QPointF(601, -78) <<  QPointF(598, -77) <<
         QPointF(600, -73) <<  QPointF(599, -72) <<  QPointF(601, -66) <<  QPointF(596, -64) <<  QPointF(589, -71) <<
         QPointF(584, -75) <<  QPointF(580, -79) <<  QPointF(575, -84) <<  QPointF(572, -89) <<  QPointF(575, -96) <<
         QPointF(575, -99) <<  QPointF(578, -104) <<  QPointF(573, -112) <<  QPointF(570, -109) <<  QPointF(571, -107) <<
         QPointF(569, -105) <<  QPointF(562, -108) <<  QPointF(556, -109) <<  QPointF(553, -103) <<  QPointF(554, -99) <<
         QPointF(548, -97) <<  QPointF(540, -100) <<  QPointF(530, -98) <<  QPointF(524, -99) <<  QPointF(518, -98) <<
         QPointF(514, -94) <<  QPointF(511, -82) <<  QPointF(509, -81) <<  QPointF(517, -77) <<  QPointF(521, -76) <<
         QPointF(526, -78) <<  QPointF(535, -73) <<  QPointF(538, -74) <<  QPointF(542, -74) <<  QPointF(545, -71) <<
         QPointF(547, -67) <<  QPointF(551, -63) <<  QPointF(556, -60) <<  QPointF(560, -55) <<  QPointF(559, -54) <<
         QPointF(558, -55) <<  QPointF(556, -54) <<  QPointF(564, -45) <<  QPointF(565, -42) <<  QPointF(561, -42) <<
         QPointF(558, -45) <<  QPointF(552, -57) <<  QPointF(549, -61) <<  QPointF(540, -69) <<  QPointF(538, -74) <<
         QPointF(535, -73) <<  QPointF(538, -70) <<  QPointF(541, -63) <<  QPointF(545, -60) <<  QPointF(547, -53) <<
         QPointF(546, -48) <<  QPointF(547, -43) <<  QPointF(543, -32) <<  QPointF(538, -27) <<  QPointF(532, -29)

    ));

    QGraphicsPolygonItem *p_indonesia = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(504, 145) <<  QPointF(501, 151) <<  QPointF(494, 154) <<  QPointF(491, 160) <<  QPointF(488, 158) <<  QPointF(484, 163) <<
         QPointF(459, 162) <<  QPointF(460, 169) <<  QPointF(465, 175) <<  QPointF(471, 180) <<  QPointF(472, 186) <<
         QPointF(469, 192) <<  QPointF(466, 193) <<  QPointF(460, 190) <<  QPointF(453, 182) <<  QPointF(449, 171) <<
         QPointF(441, 161) <<  QPointF(439, 156) <<  QPointF(429, 146) <<  QPointF(427, 141) <<  QPointF(437, 144) <<
         QPointF(445, 154) <<  QPointF(459, 162) <<  QPointF(484, 163) <<  QPointF(489, 180) <<  QPointF(492, 196) <<
         QPointF(501, 200) <<  QPointF(510, 204) <<  QPointF(514, 206) <<  QPointF(516, 204) <<  QPointF(522, 204) <<
         QPointF(524, 206) <<  QPointF(525, 210) <<  QPointF(529, 209) <<  QPointF(531, 212) <<  QPointF(530, 213) <<
         QPointF(525, 210) <<  QPointF(524, 206) <<  QPointF(529, 205) <<  QPointF(531, 203) <<  QPointF(540, 206) <<
         QPointF(542, 212) <<  QPointF(548, 205) <<  QPointF(553, 204) <<  QPointF(559, 206) <<  QPointF(554, 208) <<
         QPointF(545, 213) <<  QPointF(542, 212) <<  QPointF(540, 206) <<  QPointF(532, 208) <<  QPointF(529, 205) <<
         QPointF(524, 206) <<  QPointF(517, 208) <<  QPointF(514, 206) <<  QPointF(510, 204) <<  QPointF(508, 206) <<
         QPointF(492, 204) <<  QPointF(484, 201) <<  QPointF(479, 202) <<  QPointF(469, 198) <<  QPointF(473, 194) <<
         QPointF(482, 196) <<  QPointF(486, 198) <<  QPointF(492, 196) <<  QPointF(489, 180) <<  QPointF(501, 182) <<
         QPointF(504, 181) <<  QPointF(510, 184) <<  QPointF(514, 182) <<  QPointF(520, 170) <<  QPointF(520, 165) <<
         QPointF(525, 161) << QPointF(525, 161) <<  QPointF(529, 164) <<  QPointF(534, 160) <<  QPointF(544, 162) <<  QPointF(551, 159) <<  QPointF(552, 160) <<
         QPointF(550, 165) <<  QPointF(545, 167) <<  QPointF(539, 164) <<  QPointF(533, 165) <<  QPointF(531, 169) <<
         QPointF(534, 172) <<  QPointF(544, 170) <<  QPointF(540, 173) <<  QPointF(538, 177) <<  QPointF(541, 183) <<
         QPointF(541, 188) <<  QPointF(536, 185) <<  QPointF(533, 179) <<  QPointF(530, 182) <<  QPointF(532, 190) <<
         QPointF(528, 192) <<  QPointF(526, 190) <<  QPointF(527, 186) <<  QPointF(524, 181) <<  QPointF(528, 175) <<
         QPointF(529, 164) <<  QPointF(525, 161) <<  QPointF(522, 157) <<  QPointF(520, 151) <<  QPointF(525, 143) <<
         QPointF(538, 132) <<  QPointF(540, 128) <<  QPointF(540, 126) <<  QPointF(538, 123) <<  QPointF(539, 120) <<
         QPointF(537, 119) <<  QPointF(534, 116) <<  QPointF(535, 113) <<  QPointF(533, 112) <<  QPointF(530, 111) <<
         QPointF(530, 106) <<  QPointF(531, 105) <<  QPointF(528, 100) <<  QPointF(524, 95) <<  QPointF(526, 89) <<
         QPointF(526, 85) <<  QPointF(529, 82) <<  QPointF(532, 86) <<  QPointF(535, 90) <<  QPointF(532, 98) <<
         QPointF(537, 103) <<  QPointF(540, 102) <<  QPointF(544, 104) <<  QPointF(543, 108) <<  QPointF(539, 106) <<
         QPointF(536, 107) <<  QPointF(531, 105) <<  QPointF(530, 106) <<  QPointF(534, 110) <<  QPointF(533, 112) <<
         QPointF(535, 113) << QPointF(540, 113) <<  QPointF(540, 111) <<  QPointF(542, 110) <<  QPointF(543, 111) <<  QPointF(545, 111) <<  QPointF(547, 110) <<
         QPointF(551, 113) <<  QPointF(553, 116) <<  QPointF(550, 117) <<  QPointF(546, 113) <<  QPointF(545, 111) <<
         QPointF(543, 111) <<  QPointF(542, 112) <<  QPointF(540, 111) <<  QPointF(540, 113) <<  QPointF(537, 119) <<
         QPointF(539, 120) <<  QPointF(543, 122) <<  QPointF(545, 121) <<  QPointF(544, 117) <<  QPointF(547, 116) <<
         QPointF(548, 121) <<  QPointF(547, 122) <<  QPointF(545, 121) <<  QPointF(543, 122) <<  QPointF(540, 126) <<
         QPointF(540, 128) <<  QPointF(545, 129) <<  QPointF(550, 127) <<  QPointF(552, 121) <<  QPointF(556, 129) <<
         QPointF(557, 136) <<  QPointF(556, 137) <<  QPointF(554, 135) <<  QPointF(552, 137) <<  QPointF(554, 140) <<
         QPointF(549, 141) <<  QPointF(547, 137) <<  QPointF(544, 132) <<  QPointF(540, 133) <<  QPointF(538, 132) <<
         QPointF(525, 143) <<  QPointF(519, 137) <<  QPointF(516, 136) <<  QPointF(517, 128) <<  QPointF(517, 126) <<
         QPointF(521, 121) <<  QPointF(526, 116) <<  QPointF(527, 120) <<  QPointF(524, 124) <<  QPointF(521, 127) <<
         QPointF(517, 128) <<  QPointF(516, 136) <<  QPointF(513, 139) <<  QPointF(511, 143)

    ));

    QGraphicsPolygonItem *p_newGuinea = new QGraphicsPolygonItem(QPolygonF( QVector<QPointF>() <<
         QPointF(658, 217) <<  QPointF(644, 213) <<  QPointF(641, 211) <<  QPointF(639, 207) <<  QPointF(636, 203) <<  QPointF(631, 201) <<
         QPointF(627, 203) <<  QPointF(626, 207) <<  QPointF(623, 209) <<  QPointF(616, 208) <<  QPointF(611, 203) <<
         QPointF(607, 204) <<  QPointF(603, 202) <<  QPointF(608, 198) <<  QPointF(605, 192) <<  QPointF(592, 185) <<
         QPointF(584, 184) <<  QPointF(582, 181) <<  QPointF(573, 181) <<  QPointF(569, 183) <<  QPointF(563, 182) <<
         QPointF(564, 179) <<  QPointF(573, 181) <<  QPointF(582, 181) <<  QPointF(583, 178) <<  QPointF(585, 177) <<
         QPointF(576, 172) <<  QPointF(565, 168) <<  QPointF(563, 168) <<  QPointF(560, 165) <<  QPointF(562, 162) <<
         QPointF(561, 160) <<  QPointF(564, 155) <<  QPointF(567, 156) <<  QPointF(564, 159) <<  QPointF(566, 165) <<
         QPointF(565, 168) <<  QPointF(576, 172) << QPointF(581, 169) <<  QPointF(585, 169) <<  QPointF(589, 175) <<  QPointF(590, 179) <<  QPointF(593, 182) <<  QPointF(596, 178) <<
         QPointF(605, 173) <<  QPointF(618, 178) <<  QPointF(630, 183) <<  QPointF(636, 187) <<  QPointF(642, 191) <<
         QPointF(644, 195) <<  QPointF(649, 194) <<  QPointF(659, 191) <<  QPointF(663, 186) <<  QPointF(664, 185) <<
         QPointF(661, 182) <<  QPointF(656, 179) <<  QPointF(657, 178) <<  QPointF(663, 180) <<  QPointF(667, 185) <<
         QPointF(667, 188) <<  QPointF(670, 191) <<  QPointF(673, 195) <<  QPointF(676, 198) <<  QPointF(677, 198) <<
         QPointF(678, 197) <<  QPointF(683, 201) <<  QPointF(685, 201) <<  QPointF(691, 206) <<  QPointF(693, 205) <<
         QPointF(696, 208) <<  QPointF(695, 212) <<  QPointF(695, 213) <<  QPointF(698, 215) <<  QPointF(697, 217) <<
         QPointF(694, 214) <<  QPointF(695, 213) <<  QPointF(695, 212) <<  QPointF(694, 211) <<  QPointF(693, 211) <<
         QPointF(691, 213) <<  QPointF(688, 210) <<  QPointF(689, 209) <<  QPointF(693, 211) <<  QPointF(694, 211) <<
         QPointF(693, 205) <<  QPointF(691, 206) <<  QPointF(690, 207) <<  QPointF(685, 203) <<
         QPointF(685, 201) <<  QPointF(683, 201) <<  QPointF(681, 202) <<  QPointF(681, 203) <<  QPointF(684, 206) <<  QPointF(684, 207) <<
         QPointF(681, 208) <<  QPointF(680, 206) <<  QPointF(679, 204) <<  QPointF(681, 203) <<  QPointF(681, 202) <<
         QPointF(677, 198) <<  QPointF(676, 198) <<  QPointF(674, 200) <<  QPointF(672, 198) <<  QPointF(670, 191) <<
         QPointF(667, 188) <<  QPointF(664, 185) <<  QPointF(663, 186) <<  QPointF(663, 192) <<  QPointF(658, 195) <<
         QPointF(655, 197) <<  QPointF(649, 194) <<  QPointF(644, 195) <<  QPointF(642, 199) <<  QPointF(646, 204) <<
         QPointF(651, 209) <<  QPointF(655, 212)

    ));

    p_westernEurope->setFlag(QGraphicsItem::ItemIsFocusable);
    p_greatBritain->setFlag(QGraphicsItem::ItemIsFocusable);
    p_centralEurope->setFlag(QGraphicsItem::ItemIsFocusable);
    p_southernEurope->setFlag(QGraphicsItem::ItemIsFocusable);
    p_ukraine->setFlag(QGraphicsItem::ItemIsFocusable);
    p_iceland->setFlag(QGraphicsItem::ItemIsFocusable);
    p_scandinavia->setFlag(QGraphicsItem::ItemIsFocusable);

    p_northAfrica->setFlag(QGraphicsItem::ItemIsFocusable);
    p_egypt->setFlag(QGraphicsItem::ItemIsFocusable);
    p_eastAfrica->setFlag(QGraphicsItem::ItemIsFocusable);
    p_congo->setFlag(QGraphicsItem::ItemIsFocusable);
    p_southAfrica->setFlag(QGraphicsItem::ItemIsFocusable);
    p_madagascar->setFlag(QGraphicsItem::ItemIsFocusable);

    p_venezuela->setFlag(QGraphicsItem::ItemIsFocusable);
    p_peru->setFlag(QGraphicsItem::ItemIsFocusable);
    p_argentina->setFlag(QGraphicsItem::ItemIsFocusable);
    p_brazil->setFlag(QGraphicsItem::ItemIsFocusable);

    p_centralAmerica->setFlag(QGraphicsItem::ItemIsFocusable);
    p_easternUnitedStates->setFlag(QGraphicsItem::ItemIsFocusable);
    p_westernUnitedStates->setFlag(QGraphicsItem::ItemIsFocusable);
    p_greenland->setFlag(QGraphicsItem::ItemIsFocusable);
    p_quebec->setFlag(QGraphicsItem::ItemIsFocusable);
    p_ontario->setFlag(QGraphicsItem::ItemIsFocusable);
    p_alberta->setFlag(QGraphicsItem::ItemIsFocusable);
    p_alaska->setFlag(QGraphicsItem::ItemIsFocusable);
    p_northwestTerritory->setFlag(QGraphicsItem::ItemIsFocusable);

    p_westernAustralia->setFlag(QGraphicsItem::ItemIsFocusable);
    p_easternAustralia->setFlag(QGraphicsItem::ItemIsFocusable);
    p_indonesia->setFlag(QGraphicsItem::ItemIsFocusable);
    p_newGuinea->setFlag(QGraphicsItem::ItemIsFocusable);

    p_middleEast->setFlag(QGraphicsItem::ItemIsFocusable);
    p_ural->setFlag(QGraphicsItem::ItemIsFocusable);
    p_siberia->setFlag(QGraphicsItem::ItemIsFocusable);
    p_yakutsk->setFlag(QGraphicsItem::ItemIsFocusable);
    p_irkutsk->setFlag(QGraphicsItem::ItemIsFocusable);
    p_afghanistan->setFlag(QGraphicsItem::ItemIsFocusable);
    p_india->setFlag(QGraphicsItem::ItemIsFocusable);
    p_siam->setFlag(QGraphicsItem::ItemIsFocusable);
    p_mongolia->setFlag(QGraphicsItem::ItemIsFocusable);
    p_china->setFlag(QGraphicsItem::ItemIsFocusable);
    p_japan->setFlag(QGraphicsItem::ItemIsFocusable);
    p_kamchatka->setFlag(QGraphicsItem::ItemIsFocusable);


    //EVROPA:
    Continent *europe = new Continent();

    Territory *greatBritain = new Territory(1, "Great Britain", 1, p_greatBritain);
    europe->addTerritory(greatBritain);

    Territory *iceland = new Territory(1, "Iceland", 2, p_iceland);
    europe->addTerritory(iceland);

    Territory *northernEurope = new Territory(1, "Northern Europe", 3, p_centralEurope);
    europe->addTerritory(northernEurope);

    Territory *scandinavia = new Territory(1, "Scandinavia", 4, p_scandinavia);
    europe->addTerritory(scandinavia);

    Territory *southernEurope = new Territory(1, "Southern Europe", 5, p_southernEurope);
    europe->addTerritory(southernEurope);

    Territory *ukraine = new Territory(1, "Ukraine", 6, p_ukraine);
    europe->addTerritory(ukraine);

    Territory *westernEurope = new Territory(1, "Western Europe", 7, p_westernEurope);
    europe->addTerritory(westernEurope);

    m_continents.push_back(europe);




    //S.AMERIKA:
    Continent *northAmerica = new Continent();

    Territory *greenland = new Territory(1, "Greenland", 8, p_greenland);
    northAmerica->addTerritory(greenland);

    Territory *quebec = new Territory(1, "Quebec", 9, p_quebec);
    northAmerica->addTerritory(quebec);

    Territory *easternUnitedStates = new Territory(1, "Eastern United States", 10, p_easternUnitedStates);
    northAmerica->addTerritory(easternUnitedStates);

    Territory *centralAmerica = new Territory(1, "Central America", 11, p_centralAmerica);
    northAmerica->addTerritory(centralAmerica);

    Territory *westernUnitedStates = new Territory(1, "Western United States", 12, p_westernUnitedStates);
    northAmerica->addTerritory(westernUnitedStates);

    Territory *alberta = new Territory(1, "Alberta", 13, p_alberta);
    northAmerica->addTerritory(alberta);

    Territory *ontario = new Territory(1, "Ontario", 14, p_ontario);
    northAmerica->addTerritory(ontario);

    Territory *alaska = new Territory(1, "Alaska", 15, p_alaska);
    northAmerica->addTerritory(alaska);

    Territory *northwestTerritory = new Territory(1, "Northwest Territory", 16, p_northwestTerritory);
    northAmerica->addTerritory(northwestTerritory);

    m_continents.push_back(northAmerica);




    //J.AMERIKA:
    Continent *southAmerica = new Continent();

    Territory *venezuela = new Territory(1, "Venezuela", 17, p_venezuela);
    southAmerica->addTerritory(venezuela);

    Territory *peru = new Territory(1, "Peru", 18, p_peru);
    southAmerica->addTerritory(peru);

    Territory *brazil = new Territory(1, "Brasil", 19, p_brazil);
    southAmerica->addTerritory(brazil);

    Territory *argentina = new Territory(1, "Argentina", 20, p_argentina);
    southAmerica->addTerritory(argentina);

    m_continents.push_back(southAmerica);

    //AFRIKA:
    Continent *africa = new Continent();

    Territory *egypt = new Territory(1, "Egypt", 21, p_egypt);
    africa->addTerritory(egypt);

    Territory *northAfrica = new Territory(1, "North Africa", 22, p_northAfrica);
    africa->addTerritory(northAfrica);

    Territory *eastAfrica = new Territory(1, "East Africa", 23, p_eastAfrica);
    africa->addTerritory(eastAfrica);

    Territory *congo = new Territory(1, "Congo", 24, p_congo);
    africa->addTerritory(congo);

    Territory *southAfrica = new Territory(1, "South Africa", 25, p_southAfrica);
    africa->addTerritory(southAfrica);

    Territory *madagascar = new Territory(1, "Madagascar", 26, p_madagascar);
    africa->addTerritory(madagascar);

    m_continents.push_back(africa);



    //AZIJA:
    Continent *asia = new Continent();

    Territory *middleEast = new Territory(1, "Middle East", 27, p_middleEast);
    asia->addTerritory(middleEast);

    Territory *afghanistan = new Territory(1, "Afghanistan", 28, p_afghanistan);
    asia->addTerritory(afghanistan);

    Territory *ural = new Territory(1, "Ural", 29, p_ural);
    asia->addTerritory(ural);

    Territory *siberia = new Territory(1, "Siberia", 30, p_siberia);
    asia->addTerritory(siberia);

    Territory *yakutsk = new Territory(1, "Yakutsk", 31, p_yakutsk);
    asia->addTerritory(yakutsk);

    Territory *irkutsk = new Territory(1, "Irkutsk", 32, p_irkutsk);
    asia->addTerritory(irkutsk);

    Territory *mongolia = new Territory(1, "Mongolia", 33, p_mongolia);
    asia->addTerritory(mongolia);

    Territory *kamchatka = new Territory(1, "Kamchatka", 34, p_kamchatka);
    asia->addTerritory(kamchatka);

    Territory *japan = new Territory(1, "Japan", 35, p_japan);
    asia->addTerritory(japan);

    Territory *china = new Territory(1, "China", 36, p_china);
    asia->addTerritory(china);

    Territory *india = new Territory(1, "India", 37, p_india);
    asia->addTerritory(india);

    Territory *siam = new Territory(1, "Siam", 38, p_siam);
    asia->addTerritory(siam);

    m_continents.push_back(asia);


    //AUSTRALIA:

    Continent *australia = new Continent();

    Territory *indonesia = new Territory(1, "Indonesia", 39, p_indonesia);
    australia->addTerritory(indonesia);

    Territory *newGuinea = new Territory(1, "New Guinea", 40, p_newGuinea);
    australia->addTerritory(newGuinea);

    Territory *easternAustralia = new Territory(1, "Eastern Australia", 41, p_easternAustralia);
    australia->addTerritory(easternAustralia);

    Territory *westernAustralia = new Territory(1, "Western Australia", 42, p_westernAustralia);
    australia->addTerritory(westernAustralia);

    m_continents.push_back(australia);




    //BOooOOoooOOOoooOM KONEKCIJE
    //EVROPA:
    greatBritain->addNeighbour(iceland);
    greatBritain->addNeighbour(scandinavia);
    greatBritain->addNeighbour(northernEurope);
    greatBritain->addNeighbour(westernEurope);

    iceland->addNeighbour(greatBritain);
    iceland->addNeighbour(scandinavia);
    iceland->addNeighbour(greenland);

    scandinavia->addNeighbour(ukraine);
    scandinavia->addNeighbour(iceland);
    scandinavia->addNeighbour(greatBritain);
    scandinavia->addNeighbour(northernEurope);

    ukraine->addNeighbour(scandinavia);
    ukraine->addNeighbour(northernEurope);
    ukraine->addNeighbour(southernEurope);
    ukraine->addNeighbour(ural);
    ukraine->addNeighbour(afghanistan);
    ukraine->addNeighbour(middleEast);

    southernEurope->addNeighbour(ukraine);
    southernEurope->addNeighbour(northernEurope);
    southernEurope->addNeighbour(westernEurope);
    southernEurope->addNeighbour(egypt);
    southernEurope->addNeighbour(northAfrica);

    westernEurope->addNeighbour(southernEurope);
    westernEurope->addNeighbour(northernEurope);
    westernEurope->addNeighbour(greatBritain);
    westernEurope->addNeighbour(northAfrica);

    northernEurope->addNeighbour(greatBritain);
    northernEurope->addNeighbour(scandinavia);
    northernEurope->addNeighbour(ukraine);
    northernEurope->addNeighbour(southernEurope);
    northernEurope->addNeighbour(westernEurope);



    //S.AMERIKA:
    alaska->addNeighbour(northwestTerritory);
    alaska->addNeighbour(alberta);
    alaska->addNeighbour(kamchatka);

    northwestTerritory->addNeighbour(alaska);
    northwestTerritory->addNeighbour(greenland);
    northwestTerritory->addNeighbour(alberta);
    northwestTerritory->addNeighbour(ontario);

    greenland->addNeighbour(quebec);
    greenland->addNeighbour(northwestTerritory);
    greenland->addNeighbour(ontario);
    greenland->addNeighbour(iceland);

    quebec->addNeighbour(greenland);
    quebec->addNeighbour(easternUnitedStates);
    quebec->addNeighbour(ontario);

    ontario->addNeighbour(quebec);
    ontario->addNeighbour(easternUnitedStates);
    ontario->addNeighbour(westernUnitedStates);
    ontario->addNeighbour(alberta);
    ontario->addNeighbour(northwestTerritory);
    ontario->addNeighbour(greenland);

    alberta->addNeighbour(ontario);
    alberta->addNeighbour(westernUnitedStates);
    alberta->addNeighbour(alaska);
    alberta->addNeighbour(northwestTerritory);

    westernUnitedStates->addNeighbour(ontario);
    westernUnitedStates->addNeighbour(easternUnitedStates);
    westernUnitedStates->addNeighbour(centralAmerica);
    westernUnitedStates->addNeighbour(alberta);

    easternUnitedStates->addNeighbour(ontario);
    easternUnitedStates->addNeighbour(quebec);
    easternUnitedStates->addNeighbour(centralAmerica);
    easternUnitedStates->addNeighbour(westernUnitedStates);

    centralAmerica->addNeighbour(westernUnitedStates);
    centralAmerica->addNeighbour(easternUnitedStates);
    centralAmerica->addNeighbour(venezuela);


    //J.AMERIKA
    venezuela->addNeighbour(centralAmerica);
    venezuela->addNeighbour(brazil);
    venezuela->addNeighbour(peru);

    peru->addNeighbour(venezuela);
    peru->addNeighbour(brazil);
    peru->addNeighbour(argentina);

    brazil->addNeighbour(northAfrica);
    brazil->addNeighbour(venezuela);
    brazil->addNeighbour(peru);
    brazil->addNeighbour(argentina);

    argentina->addNeighbour(brazil);
    argentina->addNeighbour(peru);



    //AFRIKA
    northAfrica->addNeighbour(brazil);
    northAfrica->addNeighbour(westernEurope);
    northAfrica->addNeighbour(southernEurope);
    northAfrica->addNeighbour(egypt);
    northAfrica->addNeighbour(eastAfrica);
    northAfrica->addNeighbour(congo);

    egypt->addNeighbour(southernEurope);
    egypt->addNeighbour(middleEast);
    egypt->addNeighbour(northAfrica);
    egypt->addNeighbour(eastAfrica);
    egypt->addNeighbour(congo);

    congo->addNeighbour(northAfrica);
    congo->addNeighbour(eastAfrica);
    congo->addNeighbour(southAfrica);

    eastAfrica->addNeighbour(egypt);
    eastAfrica->addNeighbour(northAfrica);
    eastAfrica->addNeighbour(congo);
    eastAfrica->addNeighbour(southAfrica);
    eastAfrica->addNeighbour(madagascar);
    eastAfrica->addNeighbour(middleEast);

    southAfrica->addNeighbour(congo);
    southAfrica->addNeighbour(eastAfrica);
    southAfrica->addNeighbour(madagascar);

    madagascar->addNeighbour(southAfrica);
    madagascar->addNeighbour(eastAfrica);



    //AUSTRALIA:
    indonesia->addNeighbour(siam);
    indonesia->addNeighbour(newGuinea);
    indonesia->addNeighbour(westernAustralia);

    newGuinea->addNeighbour(indonesia);
    newGuinea->addNeighbour(easternAustralia);
    newGuinea->addNeighbour(westernAustralia);

    easternAustralia->addNeighbour(newGuinea);
    easternAustralia->addNeighbour(westernAustralia);

    westernAustralia->addNeighbour(newGuinea);
    westernAustralia->addNeighbour(easternAustralia);
    westernAustralia->addNeighbour(indonesia);



    //AZIJA
    middleEast->addNeighbour(eastAfrica);
    middleEast->addNeighbour(southernEurope);
    middleEast->addNeighbour(ukraine);
    middleEast->addNeighbour(egypt);
    middleEast->addNeighbour(afghanistan);
    middleEast->addNeighbour(india);

    india->addNeighbour(middleEast);
    india->addNeighbour(afghanistan);
    india->addNeighbour(china);
    india->addNeighbour(siam);

    siam->addNeighbour(indonesia);
    siam->addNeighbour(india);
    siam->addNeighbour(china);

    china->addNeighbour(siam);
    china->addNeighbour(india);
    china->addNeighbour(afghanistan);
    china->addNeighbour(ural);
    china->addNeighbour(siberia);
    china->addNeighbour(mongolia);

    afghanistan->addNeighbour(ukraine);
    afghanistan->addNeighbour(ural);
    afghanistan->addNeighbour(china);
    afghanistan->addNeighbour(india);
    afghanistan->addNeighbour(middleEast);

    ural->addNeighbour(ukraine);
    ural->addNeighbour(siberia);
    ural->addNeighbour(china);
    ural->addNeighbour(afghanistan);

    siberia->addNeighbour(yakutsk);
    siberia->addNeighbour(irkutsk);
    siberia->addNeighbour(mongolia);
    siberia->addNeighbour(china);
    siberia->addNeighbour(ural);

    yakutsk->addNeighbour(kamchatka);
    yakutsk->addNeighbour(irkutsk);
    yakutsk->addNeighbour(siberia);

    irkutsk->addNeighbour(yakutsk);
    irkutsk->addNeighbour(kamchatka);
    irkutsk->addNeighbour(mongolia);
    irkutsk->addNeighbour(siberia);

    mongolia->addNeighbour(irkutsk);
    mongolia->addNeighbour(kamchatka);
    mongolia->addNeighbour(japan);
    mongolia->addNeighbour(china);
    mongolia->addNeighbour(siberia);

    japan->addNeighbour(kamchatka);
    japan->addNeighbour(mongolia);

    kamchatka->addNeighbour(japan);
    kamchatka->addNeighbour(mongolia);
    kamchatka->addNeighbour(irkutsk);
    kamchatka->addNeighbour(yakutsk);
    kamchatka->addNeighbour(alaska);

}

World::~World(){}
