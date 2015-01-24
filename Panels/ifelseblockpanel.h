#ifndef BLOCKPANEL_H
#define BLOCKPANEL_H

#include "basepanel.h"

class IfElseBlockPanel : public BasePanel
{
    Q_OBJECT
public:
    explicit IfElseBlockPanel(bool isFullPanel, BasePanel *parent);
    QString getSourceCode();
    QString getXml(bool withDesc = true);
protected:
    virtual void mousePressEvent ( QMouseEvent * event );
    void contextMenuEvent(QContextMenuEvent *event);
signals:

public slots:
    void showConditionFrame();
};

#endif // BLOCKPANEL_H
