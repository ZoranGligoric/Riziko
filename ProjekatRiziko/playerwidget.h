#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <string>
#include <QString>
#include "player.h"
namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = 0,Player *player = 0);
    ~PlayerWidget();

private:
    Ui::PlayerWidget *ui;
    Player* m_player;
};

#endif // PLAYERWIDGET_H
