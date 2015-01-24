#ifndef NEWFUNCTIONFORM_H
#define NEWFUNCTIONFORM_H

#include <QFrame>
#include "Panels/functionblock.h"

namespace Ui {
class NewFunctionForm;
}

class NewFunctionForm : public QFrame
{
    Q_OBJECT

public:
    explicit NewFunctionForm(FunctionBlock* parentPanel, QWidget *parent = 0);
    ~NewFunctionForm();
    FunctionBlock* parentPanel;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::NewFunctionForm *ui;
};

#endif // NEWFUNCTIONFORM_H
