#include "gamesetup.h"
#include "ui_gamesetup.h"
#include "world.h"
#include <string>
#include <iostream>
#include "playerwidget.h"
#include "world.h"

GameSetup::GameSetup(QWidget *parent, MainWindow *par) :
    QWidget(parent),
    ui(new Ui::GameSetup)
{
    m_parent = par;
    effect1 = new QSoundEffect();

    ui->setupUi(this);
    ui->remove->hide();
    ui->pushButton_2->setDisabled(true);

    connect(ui->pushButton_3, SIGNAL(clicked()), parent, SLOT(toStartingWindow()));
    connect(ui->remove, SIGNAL(clicked()), this, SLOT (removePlayer()));
}

GameSetup::~GameSetup()
{
    delete ui;
}

void GameSetup::removePlayer(){
    playSoundEffect();
    m_players.pop_back();
    (*(m_last.rbegin()))->deleteLater();
    m_last.pop_back();
    if(m_players.empty()){
        ui->remove->hide();
    }
    if(m_players.size()<2){
        ui->pushButton_2->setDisabled(true);
    }
    i--;
}


void GameSetup::on_pushButton_2_clicked()
{
    ui->pushButton_2->setDisabled(true);
    std::cout << "1" << std::endl;
    m_parent->toGame(m_players);
    std::cout << "2" << std::endl;
}

void GameSetup::on_pushButton_clicked()
{
    playSoundEffect();

    ui->pushButton->setDisabled(true);
    if(m_players.empty()){
        ui->remove->show();
    }
    if(m_players.size()==1){
        ui->pushButton_2->setDisabled(false);
    }
    Player *player = new Player(ui->lineEdit->text().toStdString(), colors[i]);
    i++;
    m_players.push_back(player);
    PlayerWidget *tmp = new PlayerWidget(this, player);
    m_last.push_back(tmp);
    ui->players->insertWidget(0, tmp);

}

void GameSetup::on_lineEdit_textChanged()
{
    if(i>7)
        ui->pushButton->setDisabled(true);
    else
        ui->pushButton->setDisabled(false);
}

void GameSetup::playSoundEffect()
{

    effect1->setSource(QUrl::fromLocalFile(":/sounds/Click.wav"));
    effect1->setVolume(0.95);
    effect1->play();
}

void GameSetup::on_pushButton_3_clicked()
{

}

void GameSetup::soundOff1(bool a)
{
    effect1->setMuted(a);
}
