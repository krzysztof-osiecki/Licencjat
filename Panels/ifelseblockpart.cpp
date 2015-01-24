#include "ifelseblockpart.h"
#include "basepanel.h"
#include "Toolbar/customtoolbar.h"
#include "Serialization/xmlparser.h"
#include <QMessageBox>
#include <QMouseEvent>
#include "Constants.h"

IfElseBlockPart::IfElseBlockPart(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
}

void IfElseBlockPart::mousePressEvent(QMouseEvent * event)
{
    if(event->buttons() == Qt::RightButton)
    {
        return;
    }

    CustomToolbar::CommandType command = CustomToolbar::selectedCommand;
    if(command == CustomToolbar::DELETE)
    {
        QMessageBox::information(this, "Information", "If-else block parts cannot be deleted individualy.\nTry to delete whole block.");
        return;
    }
    else
    {
        BasePanel::mousePressEvent(event);
    }

    return;
}

QString IfElseBlockPart::getSourceCode()
{
    QString result;
    switch(this->panelType)
    {
    case CustomToolbar::IF:
    {
        result += QString("if(");
        result += this->prepareCondition();
        result += QString(") \n");
        result += QString("{ \n");
        for(unsigned int i = 0; i < this->children.size(); i++)
        {
            result+=this->children[i]->getSourceCode();
        }
        result += QString("} \n");
        return result;
    }
    case CustomToolbar::ELSE:
    {
        result += QString("else");
        result += QString("{ \n");
        for(unsigned int i = 0; i < this->children.size(); i++)
        {
            result+=this->children[i]->getSourceCode();
        }
        result += QString("} \n");
        return result;
    }
    default:
    {
        QMessageBox::information(this, "Information", "Error during parsing in if-else block part");
    }
    }
    return "";
}

QString IfElseBlockPart::prepareCondition()
{
    return this->condition;
}

QString IfElseBlockPart::getXml(bool withDesc)
{
    QString result = BLOCK_START_TAG;
    if(this->panelType == CustomToolbar::IF)
    {
        result += BLOCK_TYPE_START_TAG;
        result += "ifpart";
        result += BLOCK_TYPE_END_TAG;
        result += CONDITION_START_TAG;
        result += this->condition;
        result += CONDITION_END_TAG;
    }
    else
    {
        result += BLOCK_TYPE_START_TAG;
        result += "elsepart";
        result += BLOCK_TYPE_END_TAG;
    }
    result += CHILDREN_START_TAG;
    for(BasePanel* child : this->children)
    {
        result+=child->getXml();
    }
    result += CHILDREN_END_TAG;
    result += BLOCK_END_TAG;
    return result;
}
