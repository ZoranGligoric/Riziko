#ifndef GAMESETUP_H
#define GAMESETUP_H

#include <QWidget>
#include <list>
#include "player.h"
#include "playerwidget.h"
#include "options.h"
#include <QSoundEffect>
#include "mainwindow.h"

namespace Ui {
class GameSetup;
}

class GameSetup : public QWidget
{
    Q_OBJECT

public:
    explicit GameSetup(QWidget *parent = 0, MainWindow *par=0);
    ~GameSetup();

    void playSoundEffect();

private slots:
    void removePlayer();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_textChanged();

    void on_pushButton_3_clicked();

    void soundOff1(bool);

private:
    QSoundEffect* effect1;
    Ui::GameSetup *ui;
    std::list<Player*> m_players;
    std::list<PlayerWidget*> m_last;
    MainWindow* m_parent;
    int i=0;

    std::string colors [8] = {"Blue", "Red", "Green", "Yellow", "Purple", "Orange", "Cyan", "Pink"};

};

#endif // GAMESETUP_H
