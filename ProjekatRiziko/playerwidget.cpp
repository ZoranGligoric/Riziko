#include "playerwidget.h"
#include "ui_playerwidget.h"
#include "gamesetup.h"

PlayerWidget::PlayerWidget(QWidget *parent, Player *player) :
    QWidget(parent),
    ui(new Ui::PlayerWidget),
    m_player(player)
{
    QPalette p(palette());
    QColor black = Qt::black;
    black.setAlpha(68);
    p.setColor(QPalette::Background,black);
    setAutoFillBackground(true);
    this->setPalette(p);
    ui->setupUi(this);
    ui->color->setText(QString::fromStdString(player->color()));
    ui->name->setText(QString::fromStdString(player->name()));

}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}
