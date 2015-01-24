#ifndef DYNAMICBLOCK_H
#define DYNAMICBLOCK_H

#include "basepanel.h"
#include "shortpanel.h"
#include "Variables/attributestablemodel.h"

class DynamicBlock : public BasePanel
{
    Q_OBJECT
public:
    explicit DynamicBlock(bool isFullPanel, BasePanel *parent);
    AttributesTableModel attributesModel;
    QString getXml(bool withDesc = false);
    QString getSourceCode();
private:
    QString applyAttributes(QString string);
signals:

public slots:
    void contextMenuEvent(QContextMenuEvent *event);
    void showAttributesForm();
};

#endif // DYNAMICBLOCK_H
