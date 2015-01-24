#include "ifblock.h"
#include "Forms/ifconditionframe.h"
#include "Serialization/xmlparser.h"
#include "basepanellayout.h"
#include "Constants.h"
#include <QPoint>
#include <QMenu>
#include <QContextMenuEvent>

IfBlock::IfBlock(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
    this->setTitle("IF");
    this->panelType = CustomToolbar::IF;
}

QString IfBlock::getSourceCode()
{
    QString result = QString("if(");
    result += this->prepareCondition();
    result += QString(") \n")
            + QString("{ \n");

    foreach (BasePanel *child, this->children)
    {
        result+=child->getSourceCode();
    }

    result += QString("} \n");
    return result;
}

QString IfBlock::prepareCondition()
{
    return this->condition;
}

void IfBlock::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    myMenu.addAction("Set Condition", this, SLOT(showConditionFrame()));
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.addAction("Switch form", this, SLOT(switchForm()));
    myMenu.addAction("Export as component", this, SLOT(exportAsComponent()));
    myMenu.exec(globalPos);
}

void IfBlock::showConditionFrame()
{
    IfConditionFrame *frame = new IfConditionFrame(this);
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

QString IfBlock::getXml(bool withDesc)
{
    QString result = BLOCK_START_TAG;
    result += BLOCK_TYPE_START_TAG;
    result += BLOCK_TYPE_IF;
    result += BLOCK_TYPE_END_TAG;
    result += CONDITION_START_TAG;
    result += this->prepareCondition();
    result += CONDITION_END_TAG;
    result += CHILDREN_START_TAG;
    for(BasePanel* child : this->children)
    {
        result += child->getXml();
    }
    result += CHILDREN_END_TAG;
    result += BLOCK_END_TAG;
    return result;
}
