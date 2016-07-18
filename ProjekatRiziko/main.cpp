#include <QApplication>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <iterator>
#include <stack>
#include <math.h>
#include "player.h"
#include "territory.h"
#include "turn.h"
#include "functions.h"
#include "mainwindow.h"

#include"world.h"

#define MAX_SIZE 7
#define WORLD_SIZE 42
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.showNormal();

    QIcon icon(":/imgs/kocka.png");
    w.setWindowIcon(icon);

    return a.exec();
}
