#ifndef SHORTPANEL_H
#define SHORTPANEL_H

#include "Panels/basepanel.h"

class ShortPanel : public BasePanel
{
    Q_OBJECT
public:
    explicit ShortPanel(bool isFullPanel, BasePanel *parent);
    void executeTitleAndDescChange();
signals:

public slots:
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // SHORTPANEL_H
