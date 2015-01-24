#ifndef SHORTCOMPONENT_H
#define SHORTCOMPONENT_H

#include <QWidget>
#include "dynamicblock.h"
#include "basepanel.h"

class ShortComponent : public BasePanel
{
    Q_OBJECT
public:
    explicit ShortComponent(bool isFullPanel, BasePanel *parent);
    void executeTitleAndDescChange();
    DynamicBlock* dynamicFullForm;
signals:

public slots:
    void contextMenuEvent(QContextMenuEvent *event);
    void showAttributesForm();

};

#endif // SHORTCOMPONENT_H
