#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startingwindow.h"
#include "gamesetup.h"
#include "options.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    stackedWidget = new QStackedWidget();
    music = new QMediaPlayer();
    effect = new QSoundEffect();


    QPixmap bg(":/imgs/riskStart2.jpeg");
    QPalette p(palette());
    p.setBrush(QPalette::Background, bg);
    setAutoFillBackground(true);
    setPalette(p);


    playMusic();

    StartingWindow *start = new StartingWindow(this);
    GameSetup *setup = new GameSetup(this, this);
    Options* options = new Options(this);

    stackedWidget->insertWidget(0, start);
    stackedWidget->insertWidget(1, setup);
    stackedWidget->insertWidget(2, options);

    this->setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::goToSetup(){
    playSoundEffect();
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::toStartingWindow(){
    playSoundEffect();
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::toOptions()
{
    playSoundEffect();
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::playMusic(){

    music->setMedia(QUrl::fromLocalFile("/home/kiza/Радна површина/ProjekatRiziko/sounds/mainTheme.wav"));
    music->setVolume(50);
    music->play();

}

void MainWindow::playSoundEffect(){

    effect->setSource(QUrl::fromLocalFile(":/sounds/Click.wav"));
    effect->setVolume(0.95);
    effect->play();
}

void MainWindow::exitP(){
    exit(1);
}

void MainWindow::soundOff(bool a){

    effect->setMuted(a);
    effect->play();
}

void MainWindow::changeVolume(int volume)
{
    music->setVolume(volume);
}

void MainWindow::toGame(std::list<Player*> players){
    Game* game = new Game(this, players);
    stackedWidget->insertWidget(3, game);
    stackedWidget->setCurrentIndex(3);
    this->showFullScreen();
}

void MainWindow::exitGame(){
    goToSetup();
    this->showNormal();
}

void MainWindow::fullScreen(bool a){
    effect->play();
    if(a){
        this->showFullScreen();
        QPixmap bg(":/imgs/riskStart2.jpeg");
        bg = bg.scaled(size(), Qt::IgnoreAspectRatio);
        QPalette p(palette());
        p.setBrush(QPalette::Background, bg);
        setAutoFillBackground(true);
        setPalette(p);
    }
    else
        this->showNormal();
}

void MainWindow::resizeEvent(QResizeEvent *evt)
{
    QPixmap bkgnd(":/imgs/riskStart2.jpeg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);

    setPalette(p);

}
