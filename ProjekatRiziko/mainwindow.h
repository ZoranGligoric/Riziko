#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QSoundEffect>
#include "world.h"
#include <list>
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void playMusic();
    void playSoundEffect();
    void toGame(std::list<Player*> players);
protected:
    void resizeEvent(QResizeEvent* evt);
private:
    QSoundEffect* effect;
    QMediaPlayer* music;
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
private slots:
    void goToSetup();
    void exitP();
    void toStartingWindow();\
    void toOptions();
    void soundOff(bool);
    void changeVolume(int);
    void fullScreen(bool);
    void exitGame();
};


#endif // MAINWINDOW_H
