#include "whileblock.h"
#include "Forms/whileconditionframe.h"
#include "Serialization/xmlparser.h"
#include "Constants.h"
#include <QPoint>
#include <QMenu>
#include <QContextMenuEvent>

WhileBlock::WhileBlock(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
        this->setTitle("Loop");
        this->panelType = CustomToolbar::WHILE;
}

QString WhileBlock::getSourceCode()
{
    QString result = this->prepareCondition();
    result += QString("{ \n");

    for(unsigned int i = 0; i < this->children.size(); i++)
    {
        result+=this->children[i]->getSourceCode();
    }

    result += QString("} \n");
    return result;
}

QString WhileBlock::prepareCondition()
{
    return condition;
}

void WhileBlock::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    myMenu.addAction("Set Condition", this, SLOT(showConditionFrame()));
    myMenu.addAction("Switch form", this, SLOT(switchForm()));
    myMenu.addAction("Export as component", this, SLOT(exportAsComponent()));
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.exec(globalPos);
}

void WhileBlock::showConditionFrame()
{
    WhileConditionFrame *frame = new WhileConditionFrame(this);
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

QString WhileBlock::getXml(bool withDesc)
{
    QString result = BLOCK_START_TAG;
    result += BLOCK_TYPE_START_TAG;
    result += "whileblock";
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
