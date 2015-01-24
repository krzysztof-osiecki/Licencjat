#include "functionblock.h"
#include "Serialization/xmlparser.h"
#include "QLabel"
#include <QPoint>
#include <QMenu>
#include <QLineEdit>
#include <QContextMenuEvent>
#include "Constants.h"
#include "Forms/newfunctionform.h"

FunctionBlock::FunctionBlock(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent), parametersModel(2)
{
    this->panelType = CustomToolbar::FUNCTION;
}

void FunctionBlock::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    myMenu.addAction("Edit function", this, SLOT(showEditWindow()));
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.addAction("Switch form", this, SLOT(switchForm()));
    myMenu.exec(globalPos);
}


void FunctionBlock::showEditWindow()
{
    NewFunctionForm *frame = new NewFunctionForm(this);
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

QString FunctionBlock::getSourceCode()
{
    QString result = this->getHeader();
    result+= "{";
    foreach(BasePanel* child, this->children)
    {
        result+=child->getSourceCode();
    }
    result += "}";
    return result;
}


QString FunctionBlock::getHeader()
{
    QString parameters = this->getParameters();
    return this->type + " " + this->name + "(" + parameters + ")\n";
}

QString FunctionBlock::getParameters()
{
    QString result;
    foreach(VariableModel var, this->parametersModel.variables)
    {
        result.append(var.type);
        result.append(" ");
        result.append(var.name);
        result.append(" , ");
    }

    return result.mid(0, result.size()-2);
}

QString FunctionBlock::getXml(bool withDesc)
{
    QString result = BLOCK_START_TAG;
    result += BLOCK_TYPE_START_TAG;
    result += "functionblock";
    result += BLOCK_TYPE_END_TAG;
    result += FUNCTION_NAME_START_TAG;
    result += this->name;
    result += FUNCTION_NAME_END_TAG;
    result += TYPE_START_TAG;
    result += this->type;
    result += TYPE_END_TAG;
    result += this->parametersModel.getXml();
    result += CHILDREN_START_TAG;
    for(BasePanel* child : this->children)
    {
        result+=child->getXml();
    }
    result += CHILDREN_END_TAG;
    result += BLOCK_END_TAG;
    return result;
}
