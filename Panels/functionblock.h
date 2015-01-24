#ifndef FUNCTIONBLOCK_H
#define FUNCTIONBLOCK_H
#include "basepanel.h"

class FunctionBlock : public BasePanel
{
    Q_OBJECT
public:
    QString name;
    QString type;
    QList<VariableModel> parameters;
    explicit FunctionBlock(bool isFullPanel, BasePanel *parent);
    QString getParameters();
    QString getHeader();
    QString getSourceCode();
    QString getXml(bool withDesc = true);
    VariablesTableModel parametersModel;
protected:
    void contextMenuEvent(QContextMenuEvent *event);
signals:

public slots:
    void showEditWindow();
};

#endif // FUNCTIONBLOCK_H
