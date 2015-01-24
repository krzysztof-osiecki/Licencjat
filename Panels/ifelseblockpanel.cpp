#include "ifelseblockpanel.h"
#include "basepanel.h"
#include "Toolbar/customtoolbar.h"
#include "Forms/ifconditionframe.h"
#include "Serialization/xmlparser.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QPoint>
#include <QMenu>
#include <QContextMenuEvent>
#include "Constants.h"

IfElseBlockPanel::IfElseBlockPanel(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
    this->setTitle("If-Else Block");
}

void IfElseBlockPanel::mousePressEvent ( QMouseEvent * event )
{
    if(event->buttons() == Qt::RightButton)
    {
        return;
    }

    CustomToolbar::CommandType command = CustomToolbar::selectedCommand;
    if(command == CustomToolbar::NONE)
    {
        return;
    }
    if(command == CustomToolbar::DELETE)
    {
        this->deleteWithChildren();
    }
    else
    {
        QMessageBox::information(this, "Information", "If-Else block cannot support more blocks. \nPut your new block inside if or else block.");
    }
}

QString IfElseBlockPanel::getSourceCode()
{
    QString result;
    for(unsigned int i = 0; i < this->children.size(); i++)
    {
        result+=this->children[i]->getSourceCode();
    }
    return result;
}

void IfElseBlockPanel::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    myMenu.addAction("Set Condition", this, SLOT(showConditionFrame()));
    myMenu.addAction("Export as component", this, SLOT(exportAsComponent()));
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.addAction("Switch form", this, SLOT(switchForm()));
    myMenu.exec(globalPos);
}

void IfElseBlockPanel::showConditionFrame()
{
    IfConditionFrame *frame = new IfConditionFrame(this->children[0]);
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

QString IfElseBlockPanel::getXml(bool withDesc)
{
    QString result = BLOCK_START_TAG;
    result += BLOCK_TYPE_START_TAG;
    result += "ifelseblock";
    result += BLOCK_TYPE_END_TAG;
    result += CHILDREN_START_TAG;
    for(BasePanel* child : this->children)
    {
        result+=child->getXml();
    }
    result += CHILDREN_END_TAG;
    result += BLOCK_END_TAG;
    return result;
}
