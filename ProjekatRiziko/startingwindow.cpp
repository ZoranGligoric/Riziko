#include "startingwindow.h"
#include "ui_startingwindow.h"

StartingWindow::StartingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartingWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("QPushButton { background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:0.497608 rgba(129, 129, 129, 0), stop:0.995215 rgba(0, 0, 0, 255)); border:none; color:white}");
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),parent, SLOT(goToSetup()));
    connect(ui->pushButton_2, SIGNAL(clicked()), parent, SLOT(toOptions()));
    connect(ui->pushButton_3, SIGNAL(clicked()), parent, SLOT(exitP()));
}

StartingWindow::~StartingWindow()
{
    delete ui;
}
