#include "options.h"
#include "ui_options.h"
#include "mainwindow.h"
#include "gamesetup.h"
#include <QMediaPlayer>

Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), parent, SLOT(toStartingWindow()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), parent, SLOT(changeVolume(int)));
    connect(ui->radioButton, SIGNAL(toggled(bool)), parent, SLOT(soundOff(bool)));
    connect(ui->checkBox, SIGNAL(toggled(bool)), parent, SLOT(fullScreen(bool)));
}

Options::~Options()
{
    delete ui;
}

void Options::on_horizontalSlider_sliderMoved(int)
{

}

void Options::on_radioButton_clicked()
{

}

void Options::on_pushButton_clicked()
{

}


void Options::on_radioButton_toggled(bool)
{

}

void Options::on_horizontalSlider_valueChanged(int)
{

}

void Options::on_checkBox_toggled(bool)
{

}
