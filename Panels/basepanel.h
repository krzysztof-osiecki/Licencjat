#ifndef BASEPANEL_H
#define BASEPANEL_H

#include "basepanellayout.h"
#include "basescrollarea.h"
#include "Toolbar/customtoolbar.h"
#include "Variables/variablestablemodel.h"
#include <string>
#include <QWidget>
#include <QFrame>
#include <vector>
#include <QLabel>
#include <QGroupBox>
#include <QContextMenuEvent>

class BasePanel : public QGroupBox
{
    Q_OBJECT
public:
    explicit BasePanel(bool isFullPanel, BasePanel *parent);
    void SetSize(int width, int height);
    void SetWidth(int width);
    void SetHeight(int height);
    QString componentName;
    QString title;
    QString description;
    QString condition;
    QString usageFormXml;
    QString variableType;
    QLabel *descLabel;
    BasePanel* parentPanel = NULL;
    BasePanel* shortForm;
    BasePanel* fullForm;
    std::vector<BasePanel* > children;
    CustomToolbar::CommandType panelType;
    static BasePanel* mainPanel;
    static BasePanel* functionPanel;
    static VariablesTableModel variableModel;
    static int uniqueId(){uniqueIdValue++; return uniqueIdValue;}
    virtual void deleteWithChildren();
    virtual QString getSourceCode();
    virtual QString getHeader();
    virtual QString getHeaders();
    virtual QString getXml(bool withDesc = true);
    virtual void executeTitleAndDescChange();
    virtual void saveAsComponent();
private:
    static int uniqueIdValue;
    friend void BaseScrollArea::ExecuteClick(QMouseEvent * event);
    void PrepareContainerBlock(QMouseEvent *event);
    void PrepareDynamicBlock(QMouseEvent *event);
    void PrepareIfElseBlock(QMouseEvent *event);
    void PrepareIfPart(BasePanel *root);
    void PrepareElsePart(BasePanel *root);
    void PrepareIfBlock(QMouseEvent *event);
    void PrepareWhileBlock(QMouseEvent *event);
    void PrepareTextBlock(QMouseEvent *event);
protected:
    void mousePressEvent(QMouseEvent *);
signals:

public slots:
    virtual void deleteAction();
    virtual void switchForm();
    virtual void renameAction();
    virtual void exportAsComponent();

};

#endif // BASEPANEL_H
