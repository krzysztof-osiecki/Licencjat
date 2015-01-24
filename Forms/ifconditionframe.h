#ifndef IFCONDITIONFRAME_H
#define IFCONDITIONFRAME_H

#include "Panels/basepanel.h"
#include <QFrame>

namespace Ui {
class IfConditionFrame;
}

class IfConditionFrame : public QFrame
{
    Q_OBJECT

public:
    explicit IfConditionFrame(BasePanel *parentPanel, QWidget *parent = NULL);
    ~IfConditionFrame();
    BasePanel* connectedPanel;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::IfConditionFrame *ui;
};

#endif // IFCONDITIONFRAME_H
