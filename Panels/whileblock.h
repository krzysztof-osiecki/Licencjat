#ifndef WHILEPANEL_H
#define WHILEPANEL_H
#include "basepanel.h"

class WhileBlock : public BasePanel
{
    Q_OBJECT
public:
    explicit WhileBlock(bool isFullPanel, BasePanel *parent);
    QString getSourceCode();
    QString getXml(bool withDesc = true);
private:
    QString prepareCondition();
    void contextMenuEvent(QContextMenuEvent *event);
signals:

public slots:
    void showConditionFrame();
};

#endif // WHILEPANEL_H
