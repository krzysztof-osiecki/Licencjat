#ifndef VARIABLESFRAME_H
#define VARIABLESFRAME_H

#include <QFrame>

namespace Ui {
class VariablesFrame;
}

class VariablesFrame : public QFrame
{
    Q_OBJECT

public:
    explicit VariablesFrame(QWidget *parent = 0);
    ~VariablesFrame();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::VariablesFrame *ui;
};

#endif // VARIABLESFRAME_H
