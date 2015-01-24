#ifndef BASESCROLAREA_H
#define BASESCROLAREA_H

#include <QScrollArea>
class BaseScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit BaseScrollArea(QWidget *parent = 0);
    void ExecuteClick(QMouseEvent * event);
    enum ScrollType {MAIN, FUNCTION};
    ScrollType type;
protected:
    void mousePressEvent ( QMouseEvent * event );
private:
signals:

public slots:

};

#endif // BASESCROLAREA_H
