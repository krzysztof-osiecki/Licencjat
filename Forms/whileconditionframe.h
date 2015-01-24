#ifndef WHILECONDITIONFRAME_H
#define WHILECONDITIONFRAME_H

#include "Panels/basepanel.h"
#include <QFrame>

namespace Ui {
class WhileConditionFrame;
}

class WhileConditionFrame : public QFrame
{
    Q_OBJECT

public:
    explicit WhileConditionFrame(BasePanel *parentPanel, QWidget *parent = NULL);
    ~WhileConditionFrame();
    BasePanel* connectedPanel;

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::WhileConditionFrame *ui;
};

#endif // WHILECONDITIONFRAME_H
