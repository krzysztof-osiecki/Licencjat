#ifndef DYNAMICTOOLBAR_H
#define DYNAMICTOOLBAR_H

#include <QFrame>
#include <QGroupBox>

class DynamicToolbar : public QGroupBox
{
    Q_OBJECT
public:
    explicit DynamicToolbar(QWidget *parent = 0);
    static QStringList labels;
    static QStringList xmls;
    static int selectedIndex;
private:
    void clearToolbar();
signals:

public slots:
    void handleButton();
    void loadComponents();

};

#endif // DYNAMICTOOLBAR_H
