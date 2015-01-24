#include "containerpanel.h"
#include "Serialization/xmlparser.h"
#include <QMenu>
#include "Constants.h"

ContainerPanel::ContainerPanel(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
}

void ContainerPanel::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.addAction("Switch form", this, SLOT(switchForm()));
    myMenu.addAction("Export as component", this, SLOT(exportAsComponent()));
    myMenu.exec(globalPos);
}

QString ContainerPanel::getSourceCode()
{
    QString result = QString("{");
    foreach (BasePanel *child, this->children)
    {
        result+=child->getSourceCode();
    }

    result += QString("} \n");
    return result;
}

QString ContainerPanel::getXml(bool withDesc)
{
    QString result = BLOCK_START_TAG;
    result += BLOCK_TYPE_START_TAG;
    result += BLOCK_TYPE_CONTAINER;
    result += BLOCK_TYPE_END_TAG;
    result += CHILDREN_START_TAG;
    for(BasePanel* child : this->children)
    {
        result += child->getXml();
    }
    result += CHILDREN_END_TAG;
    result += BLOCK_END_TAG;
    return result;
}
