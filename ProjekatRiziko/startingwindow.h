#ifndef STARTINGWINDOW_H
#define STARTINGWINDOW_H

#include <QWidget>

namespace Ui {
class StartingWindow;
}

class StartingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartingWindow(QWidget *parent = 0);
    ~StartingWindow();

private:
    Ui::StartingWindow *ui;
};

#endif // STARTINGWINDOW_H
