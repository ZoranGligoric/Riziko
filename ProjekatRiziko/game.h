#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include "world.h"
#include <list>
#include "player.h"
#include "continent.h"
#include "territory.h"
#include <QThread>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0, std::list<Player*> players = std::list<Player*>());
    void resizeEvent(QResizeEvent *e);
    ~Game();
    void mousePressEvent(QMouseEvent *);
    void selected(Territory*);
    void selected2(Territory*);
    void highlight(std::vector<Territory*>, std::vector<Territory*>);
    void deselected();
    void addTanks(Territory*);
    void realAddTanks(Territory* t);

    void checkEnding();
    void attack(Territory* ter1, Territory* ter2);
    void moveTanks(Territory* ter1, Territory* ter2);

    void highlightPossibleAttacks(Territory* ter1);
    void highlightOwned(Player* player);
    void highlightConnected(Territory* ter1);
    void highlightMovable(Player* player);

    void attackPhase(Territory*attacker, Territory *defender);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    World *m_world;
    Ui::Game *ui;
    bool fuqingBugSolution;
    Territory* previousClicked;
    Territory* clicked;
    QGraphicsScene *scene;
    std::vector<Territory*> items;

    bool m_startup;
    bool m_firstTurn;

};

#endif // GAME_H
