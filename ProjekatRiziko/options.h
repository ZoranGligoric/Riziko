#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>

namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_radioButton_clicked();

    void on_pushButton_clicked();

    void on_radioButton_toggled(bool checked);

    void on_horizontalSlider_valueChanged(int);

    void on_checkBox_toggled(bool);

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H
