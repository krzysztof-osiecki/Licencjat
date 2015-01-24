#ifndef INCLUDESFRAME_H
#define INCLUDESFRAME_H

#include <QFrame>

namespace Ui {
class IncludesFrame;
}

class IncludesFrame : public QFrame
{
    Q_OBJECT

public:
    explicit IncludesFrame(QWidget *parent = 0);
    ~IncludesFrame();

private slots:
    void on_pushButton_clicked();

private:
    Ui::IncludesFrame *ui;
};

#endif // INCLUDESFRAME_H
