#ifndef RENAMEFRAME_H
#define RENAMEFRAME_H

#include <QFrame>
#include "Panels/basepanel.h"

namespace Ui {
class RenameFrame;
}

class RenameFrame : public QFrame
{
    Q_OBJECT

public:
    explicit RenameFrame(BasePanel *parentPanel, QWidget *parent = NULL);
    ~RenameFrame();
    BasePanel* connectedPanel;

private slots:
    void on_pushButton_clicked();

private:
    Ui::RenameFrame *ui;
};

#endif // RENAMEFRAME_H
