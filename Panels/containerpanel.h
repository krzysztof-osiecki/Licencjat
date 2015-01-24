#ifndef CONTAINERPANEL_H
#define CONTAINERPANEL_H

#include <QWidget>
#include "basepanel.h"

class ContainerPanel : public BasePanel
{
    Q_OBJECT
public:
    explicit ContainerPanel(bool isFullPanel, BasePanel *parent);
    QString getXml(bool withDesc = false);
    QString getSourceCode();
signals:

public slots:
    void contextMenuEvent(QContextMenuEvent *event);

};

#endif // CONTAINERPANEL_H
