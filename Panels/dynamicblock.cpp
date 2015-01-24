#include "dynamicblock.h"
#include "basepanel.h"
#include "shortcomponent.h"
#include "Forms/usageform.h"
#include "Serialization/xmlparser.h"
#include "Constants.h"
#include <QMenu>

DynamicBlock::DynamicBlock(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent), attributesModel()
{
    ShortComponent* dynamicShortForm = new ShortComponent(false, this->parentPanel);
    dynamicShortForm->dynamicFullForm = this;
    dynamicShortForm->fullForm = this;
    this->shortForm = dynamicShortForm;
}

void DynamicBlock::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    if(!this->attributesModel.attributes.isEmpty())
    {
        myMenu.addAction("Change attributes values", this, SLOT(showAttributesForm()));
    }
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.exec(globalPos);
}

void DynamicBlock::showAttributesForm()
{
    UsageForm *frame = new UsageForm(this);
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

QString DynamicBlock::getSourceCode()
{
    QString result = this->children.at(0)->getSourceCode();
    return this->applyAttributes(result);
}

QString DynamicBlock::getXml(bool withDesc)
{
    QString result = BLOCK_START_TAG;
    result += BLOCK_TYPE_START_TAG;
    result += BLOCK_TYPE_DYNAMIC;
    result += BLOCK_TYPE_END_TAG;
    if(withDesc)
    {
        result += COMPONENT_NAME_START_TAG;
        result += this->componentName;
        result += COMPONENT_NAME_END_TAG;
        result += COMPONENT_DESCRIPTION_START_TAG;
        result += this->description;
        result += COMPONENT_DESCRIPTION_END_TAG;
    }
    result += CHILDREN_START_TAG;
    for(BasePanel* child : this->children)
    {
        result += child->getXml();
    }
    result += CHILDREN_END_TAG;
    result += BLOCK_END_TAG;
    result = this->applyAttributes(result);
    return result;
}

QString DynamicBlock::applyAttributes(QString string)
{
    for(AttributeModel attribute : this->attributesModel.attributes)
    {
        string.replace(attribute.placeholder, attribute.value);
    }
    return string;
}
