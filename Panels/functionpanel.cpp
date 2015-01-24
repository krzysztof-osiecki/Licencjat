#include <QMessageBox>
#include <QMouseEvent>
#include <QMenu>
#include <QPoint>
#include <QContextMenuEvent>
#include "functionpanel.h"
#include "Toolbar/customtoolbar.h"
#include "Serialization/xmlparser.h"
#include "functionblock.h"
#include "Constants.h"

FunctionPanel::FunctionPanel(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
}

void FunctionPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
    {
        return;
    }

    CustomToolbar::CommandType command = CustomToolbar::selectedCommand;
    switch(command)
    {
    case CustomToolbar::NONE:
    {
        return;
    }
    case CustomToolbar::FUNCTION:
    {
        FunctionBlock *newPanel = new FunctionBlock(true, this);
        newPanel->panelType = CustomToolbar::FUNCTION;
        newPanel->showEditWindow();
        BasePanelLayout *layout = (BasePanelLayout*) this->layout();
        int i = 0;
        while (i < layout->count() && layout->itemAt(i)->widget()->y()<event->y())
        {
            i++;
        }
        layout->setSizeConstraint(layout->SetFixedSize);
        layout->insertWidget(i, newPanel);
        this->children.insert(children.begin()+i, newPanel);
        layout->setAlignment(newPanel, Qt::AlignHCenter);
        break;
    }
    case CustomToolbar::DELETE:
    {
        QMessageBox::information(this, "Information", "You cannot delete this panel.");
        break;
    }
    default:
    {
        QMessageBox::information(this, "Information", "Only function blocks can be placed inside Function Panel.");
        break;
    }
    }

}

QString FunctionPanel::getHeaders()
{
    QString result;
    foreach(BasePanel* child, this->children)
    {
        result+=child->getHeader()+";\n";
    }
    return result;
}

QString FunctionPanel::getSourceCode()
{
    QString result;
    foreach(BasePanel* child, this->children)
    {
        result+=child->getSourceCode()+"\n";
    }
    return result;
}

QString FunctionPanel::getXml(bool withDesc)
{
    QString result = FUNCTIONS_START_TAG;
    for(BasePanel* child : this->children)
    {
        result+=child->getXml();
    }
    result += FUNCTIONS_END_TAG;
    return result;
}

