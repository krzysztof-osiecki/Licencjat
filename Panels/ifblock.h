#ifndef IFPANEL_H
#define IFPANEL_H
#include "basepanel.h"

class IfBlock : public BasePanel
{
    Q_OBJECT
public:
    explicit IfBlock(bool isFullPanel, BasePanel *parent);
    QString getSourceCode();
    QString getXml(bool withDesc = true);
private:
    void contextMenuEvent(QContextMenuEvent *event);
    QString prepareCondition();
signals:

public slots:
    void showConditionFrame();
};

#endif // IFPANEL_H
