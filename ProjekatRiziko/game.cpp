#include "game.h"
#include "ui_game.h"
#include "world.h"
#include "continent.h"
#include "territory.h"
#include "functions.h"
#include "gamesetup.h"
#include "turn.h"
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QRect>
#include <QResizeEvent>
#include <QGraphicsLayout>
#include <iostream>
#include <QPainter>
#include <QColor>
#include <QLabel>
#include <QString>
#include <QInputDialog>
#include <QDialog>
#include <QDir>

Game::Game(QWidget *parent, std::list<Player*> players) :
    QWidget(parent),
    ui(new Ui::Game),
    fuqingBugSolution(false)
{
    m_startup = true;
    m_firstTurn = true;
    Turn* turn = new Turn(players);
    m_world = new World(turn);
    m_world->init(players);
    previousClicked=0;

    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), parent, SLOT(exitGame()));


    QRectF okvir(QRect(-524, -200, 1326, 627));
    QGraphicsScene* scene = new QGraphicsScene(okvir, this);

    std::vector<Territory*> allT(m_world->allTerritories());
    std::vector<Territory*>::iterator i;


    //bojenje teritorija prema ownerima (pocetnim)
    for(i=allT.begin();i!=allT.end(); i++)
    {
        scene->addItem((*i)->getPolygon());
        QString myColor = (*i)->owner()->color().c_str();              
        QColor c(myColor);
        (*i)->getPolygon()->setBrush(c);
    }

    ui->view->setScene(scene);

    ui->view->resize(this->width(), this->height());

    ui->mainLabel->setStyleSheet("background-color: white");
    ui->mainLabel->setText("Na pocetku, dodelite tenkove");

    ui->labelKockaImage->setScaledContents(1);

    ui->pushButton_2->setDisabled(true);

    for(i=allT.begin(); i!=allT.end(); i++)
    {
        switch((*i)->id()){
            case 1:    (*i)->setLabel(ui->labelGreatBritain);
            break;
            case 2:    (*i)->setLabel(ui->labelIceland);
            break;
            case 3:    (*i)->setLabel(ui->labelCentralEurope);
            break;
            case 4:    (*i)->setLabel(ui->labelScandinavia);
            break;
            case 5:    (*i)->setLabel(ui->labelSouthernEurope);
            break;
            case 6:    (*i)->setLabel(ui->labelUkraine);
            break;
            case 7:    (*i)->setLabel(ui->labelWesternEurope);
            break;
            case 8:    (*i)->setLabel(ui->labelGreenland);
            break;
            case 9:    (*i)->setLabel(ui->labelQuebec);
            break;
            case 10:    (*i)->setLabel(ui->labelEasternUnitedStates);
            break;
            case 11:    (*i)->setLabel(ui->labelCentralAmerica);
            break;
            case 12:    (*i)->setLabel(ui->labelWesternUnitedStates);
            break;
            case 13:    (*i)->setLabel(ui->labelAlberta);
            break;
            case 14:    (*i)->setLabel(ui->labelOntario);
            break;
            case 15:    (*i)->setLabel(ui->labelAlaska);
            break;
            case 16:    (*i)->setLabel(ui->labelNorthWestTerritory);
            break;
            case 17:    (*i)->setLabel(ui->labelVenezuela);
            break;
            case 18:    (*i)->setLabel(ui->labelPeru);
            break;
            case 19:    (*i)->setLabel(ui->labelBrazil);
            break;
            case 20:    (*i)->setLabel(ui->labelArgentina);
            break;
            case 21:    (*i)->setLabel(ui->labelEgypt);
            break;
            case 22:    (*i)->setLabel(ui->labelWesternAfrica);
            break;
            case 23:    (*i)->setLabel(ui->labelEasternAfrica);
            break;
            case 24:    (*i)->setLabel(ui->labelCongo);
            break;
            case 25:    (*i)->setLabel(ui->labelSouthernAfrica);
            break;
            case 26:    (*i)->setLabel(ui->labelMadagascar);
            break;
            case 27:    (*i)->setLabel(ui->labelMiddleEast);
            break;
            case 28:    (*i)->setLabel(ui->labelAfghanistan);
            break;
            case 29:    (*i)->setLabel(ui->labelUral);
            break;
            case 30:    (*i)->setLabel(ui->labelSiberia);
            break;
            case 31:    (*i)->setLabel(ui->labelYakutsk);
            break;
            case 32:    (*i)->setLabel(ui->labelIrkutsk);
            break;
            case 33:    (*i)->setLabel(ui->labelMongolia);
            break;
            case 34:    (*i)->setLabel(ui->labelKamchatka);
            break;
            case 35:    (*i)->setLabel(ui->labelJapan);
            break;
            case 36:    (*i)->setLabel(ui->labelChina);
            break;
            case 37:    (*i)->setLabel(ui->labelIndia);
            break;
            case 38:    (*i)->setLabel(ui->labelSiam);
            break;
            case 39:    (*i)->setLabel(ui->labelIndonesia);
            break;
            case 40:    (*i)->setLabel(ui->labelNewGuinea);
            break;
            case 41:    (*i)->setLabel(ui->labelEasternAustralia);
            break;
            case 42:    (*i)->setLabel(ui->labelWesternAustralia);
            break;
        }
    }
}

void Game::realAddTanks(Territory *t){
    if(t->owner()->unplaced() == 0)
        return;
    t->addTanks(1);
    t->owner()->removeTanks(1);
    t->label()->setText(QString::number(t->tanks()));


    // Update-ovanje labele sa nepostavljenim tenkovima
    std::string name = m_world->turn()->currentPlayer()->name();
    int unplaced = m_world->turn()->currentPlayer()->unplaced();
    QString s = name.c_str();
    s.append(" has ");
    s.append(QString::number(unplaced));
    s.append(" unplaced tanks.");
    ui->labelUnplaced->setText(s);
}


void Game::addTanks(Territory* t)
{
    ui->mainLabel->setText("Postavite tenkice ");

    std::cout<< t->owner()->name() << std::endl;

    if(t->owner()->unplaced()>0)
    {
        t->addTanks(1);
        t->label()->setText((toString(t->tanks())).c_str());
        std::cout<<(*(m_world->m_players.begin()))->name()<<std::endl;
        t->owner()->removeTanks(1);
        return;
    }
}


void Game::resizeEvent(QResizeEvent *e){
    if(fuqingBugSolution){
        ui->view->resize(e->size().width(), e->size().height());
        ui->view->fitInView(ui->view->sceneRect(), Qt::KeepAspectRatio);

    }
    else fuqingBugSolution=true;
}

void Game::mousePressEvent(QMouseEvent *){

    std::vector<Territory*>::iterator i;
    std::vector<Territory*> allT = m_world->allTerritories();


    for(i=allT.begin(); i!=allT.end(); i++){
        if(ui->view->scene()->focusItem() == (*i)->getPolygon()){
            clicked = *i;
            break;
         }
    }
    if(i == allT.end())
        clicked = NULL;

    if(clicked != NULL)
        std::cout << "kliknuta je teritorija: " << clicked->name() << std::endl;



    if(m_startup && clicked!=NULL)
    {
        addTanks(clicked);
        checkEnding();
    }
    else if(m_world->turn()->getPhase() == 1 && clicked!=NULL){
        realAddTanks(clicked);
    }
    else if(m_world->turn()->getPhase() == 2 )
    {
        if(clicked == NULL){
            highlightOwned(m_world->turn()->currentPlayer());
            previousClicked=NULL;
        }
        else if(previousClicked == NULL){
            previousClicked = clicked;
            highlightPossibleAttacks(clicked);
        }
        else{
            //ATTACK METOD CE SKINUTI OSVETLJENJE
            attack(previousClicked, clicked);
        }
    }
    else if(m_world->turn()->getPhase() == 3){
        if(clicked==NULL){
            highlightOwned(m_world->turn()->currentPlayer());
            previousClicked = NULL;
        }
        else if(previousClicked == NULL){
            previousClicked = clicked;
            highlightConnected(clicked);
        }
        else{
            moveTanks(previousClicked, clicked);
            highlightMovable(m_world->turn()->currentPlayer());
        }
    }
}


void Game::highlightPossibleAttacks(Territory *ter1){
    std::vector<Territory*>::iterator i;
    std::vector<Territory*> allT = m_world->allTerritories();
    for(i = allT.begin(); i != allT.end(); i++){
        (*i)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, false);
        (*i)->getPolygon()->setOpacity(0.5);
    }
    std::vector<Territory*> focusableT = ter1->neighbours();
    for(i = focusableT.begin(); i!=focusableT.end(); i++){
        if(ter1->owner() != (*i)->owner()){
            (*i)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, true);
            (*i)->getPolygon()->setOpacity(1);
        }
    }
}


void Game::highlightOwned(Player *player){
    std::vector<Territory*> allT = m_world->allTerritories();
    std::vector<Territory*>::iterator i;
    for(i = allT.begin(); i != allT.end(); i++){
        if((*i)->owner() == player){
            (*i)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, true);
            (*i)->getPolygon()->setOpacity(1);
        }
        else{
            (*i)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, false);
            (*i)->getPolygon()->setOpacity(0.5);
        }
    }
}

void Game::highlightConnected(Territory *ter1){
    std::list<Territory*> territories = ter1->allConected();
    std::vector<Territory*> allT = m_world->allTerritories();
    std::vector<Territory*>::iterator i;
    std::list<Territory*>::iterator j;
    for(i = allT.begin(); i != allT.end(); i++){
            (*i)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, false);
            (*i)->getPolygon()->setOpacity(0.5);
        }

    for(j=territories.begin(); j!=territories.end(); j++){
        (*j)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, true);
        (*j)->getPolygon()->setOpacity(1);
    }

}

void Game::highlightMovable(Player* player){
    std::vector<Territory*> allT = m_world->allTerritories();
    std::vector<Territory*>::iterator i;
    for(i = allT.begin(); i != allT.end(); i++){
        if((*i)->owner() == player && (*i)->tanks()>1){
            (*i)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, true);
            (*i)->getPolygon()->setOpacity(1);
        }
        else{
            (*i)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, false);
            (*i)->getPolygon()->setOpacity(0.5);
        }
    }
}


void Game::attack(Territory* ter1, Territory* ter2){

    //Ispis labela ko napada i ko se brani
    if(ter1->tanks()>1){
         QString s1(ter1->name().c_str());
        s1.append(" is attacking.");
        ui->labelAttack->setText(s1);

        QString s2(ter2->name().c_str());
        s2.append(" is defending.");
        ui->labelDefend->setText(s2);
    }
    else {
        // Ispis u slucaju da nema dovoljno tenkova
        ui->labelAttack->setText("Not enough tanks to attack!");
        ui->labelDefend->setText("");
    }


    if(ter1 == ter2){
        //TERITORIJE SU ISTE (IGRAC SE PREDOMISLIO)
        previousClicked=NULL;
    }
    else{
        int tmp = ter1->attackTerritory(ter2);

        ui->labelKocka6->setText(QString::number(tmp%10));
        tmp/=10;

        ui->labelKocka5->setText(QString::number(tmp%10));
        tmp/=10;

        ui->labelKocka4->setText(QString::number(tmp%10));
        tmp/=10;

        ui->labelKocka3->setText(QString::number(tmp%10));
        tmp/=10;

        ui->labelKocka2->setText(QString::number(tmp%10));
        tmp/=10;

        ui->labelKocka1->setText(QString::number(tmp%10));
        tmp/=10;

        highlightOwned(m_world->turn()->currentPlayer());
        previousClicked=NULL;
    }

    if(ter2->tanks() == 0){
        bool ok;
        int x = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                             tr("tanks to transfer:"), 1, 1, ter1->tanks()-1, 1,
                                             &ok);
       ter1->removeTanks(x);
       ter1->label()->setText(QString::number(ter1->tanks()));
       ter2->addTanks(x);
       ter2->label()->setText(QString::number(ter2->tanks()));
       ter1->owner()->addTerritories(1);
       ter2->owner()->addTerritories(-1);
       if(ter2->owner()->territories()==0)
       {
           m_world->turn()->removePlayer(ter2->owner());
       }
       if(m_world->turn()->players().size()==1)
       {
           //winner
           QString winner= (ter1->owner()->name()).c_str();
           winner.append(" HAS WON!");
           ui->mainLabel->setText(winner);
           ui->pushButton_2->setDisabled(true);
           std::vector<Territory*> t = m_world->allTerritories();
           std::vector<Territory*>::iterator k;
           for(k = t.begin(); k != t.end(); k++){
               (*k)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, false);
               clicked=NULL;
               previousClicked=NULL;
           }
       }
       ter2->changeOwner(ter1->owner());
       QString myColor = m_world->turn()->currentPlayer()->color().c_str();

       QColor c(myColor);
       ter2->getPolygon()->setBrush(c);
       ter2->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable);
       ter2->getPolygon()->setOpacity(1);
    }

}


void Game::checkEnding()
{
    int sum=0;
    std::list<Player*>::iterator i;
    for(i=m_world->m_players.begin(); i!=m_world->m_players.end(); i++)
    {
        if((*i)->unplaced()==0)
            sum++;
    }
    if(sum==m_world->m_players.size())
    {
        ui->pushButton_2->setDisabled(false);
        //Prelazak u fazu napada za odredjenog igraca
        m_world->turn()->nextPhase();
        std::vector<Territory*> allT = m_world->allTerritories();
        std::vector<Territory*>::iterator j;
        m_startup = false;


        //podesavanja clickable teritorija
        for(j=allT.begin(); j != allT.end(); j++){
            if((*j)->owner() == m_world->turn()->currentPlayer()){
                (*j)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable);
                (*j)->getPolygon()->setOpacity(1);
            }
            else{
                (*j)->getPolygon()->setFlag(QGraphicsItem::ItemIsFocusable, false);
                (*j)->getPolygon()->setOpacity(0.5);
            }
        }

        //podesavanje statusne labele
        QString s(m_world->turn()->currentPlayer()->name().c_str());
        s.append(" is attacking!");
        ui->mainLabel->setText(s);
        QString myColor = m_world->turn()->currentPlayer()->color().c_str();
                QString styleSheet = "QLabel { background-color: white; color: %1;}";
                    ui->mainLabel->setStyleSheet( styleSheet.arg(myColor) );
        previousClicked = NULL;
    }
}


void Game::moveTanks(Territory* ter1, Territory* ter2){
    bool ok;
        int x = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                             tr("tanks to transfer:"), 0, 0, ter1->tanks()-1, 1,
                                             &ok);
    ter1->removeTanks(x);
    ter2->addTanks(x);

    ter1->label()->setText(QString::number(ter1->tanks()));
    ter2->label()->setText(QString::number(ter2->tanks()));

    previousClicked = NULL;
    highlightOwned(ter1->owner());

}


Game::~Game()
{
    delete ui;
}

void Game::on_pushButton_clicked()
{

}

//NEXT PHASE DUGME
void Game::on_pushButton_2_clicked()
{
    m_world->turn()->nextPhase();
    previousClicked = NULL;

    if(m_world->turn()->getPhase() == 1){
        if(m_firstTurn && m_world->turn()->currentPlayer() == m_world->turn()->firstPlayer()){
            m_firstTurn=false;
        }
        if(!m_firstTurn){
            m_world->gainedTanks(m_world->turn()->currentPlayer());
            std::cout << m_world->turn()->currentPlayer()->unplaced() << std::endl;
            highlightOwned(m_world->turn()->currentPlayer());
            QString s(m_world->turn()->currentPlayer()->name().c_str());
            s.append(" is placing tanks!");
            ui->mainLabel->setText(s);
            QString myColor = m_world->turn()->currentPlayer()->color().c_str();
                    QString styleSheet = "QLabel { background-color: white; color: %1;}";
                        ui->mainLabel->setStyleSheet( styleSheet.arg(myColor) );
        }
        else
            m_world->turn()->nextPhase();
    }


    // Ispis koliko trenutni igrac ima nepostavljenih tenkova
    std::string name = m_world->turn()->currentPlayer()->name();
    int unplaced = m_world->turn()->currentPlayer()->unplaced();
    QString s = name.c_str();
    s.append(" has ");
    s.append(QString::number(unplaced));
    s.append(" unplaced tanks.");
    ui->labelUnplaced->setText(s);


    if(m_world->turn()->getPhase() == 2){
        highlightOwned(m_world->turn()->currentPlayer());
        QString s(m_world->turn()->currentPlayer()->name().c_str());
        s.append(" is attacking!");
        ui->mainLabel->setText(s);
        QString myColor = m_world->turn()->currentPlayer()->color().c_str();
                QString styleSheet = "QLabel { background-color: white; color: %1;}";
                    ui->mainLabel->setStyleSheet( styleSheet.arg(myColor) );
    }

    if(m_world->turn()->getPhase() == 3){
        highlightMovable(m_world->turn()->currentPlayer());
        QString s(m_world->turn()->currentPlayer()->name().c_str());
        s.append(" is moving tanks!");
        ui->mainLabel->setText(s);

    }

}
