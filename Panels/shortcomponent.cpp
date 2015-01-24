#include "shortcomponent.h"
#include "basepanel.h"
#include "Forms/usageform.h"
#include <QMenu>

ShortComponent::ShortComponent(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
    this->componentName = title;
    this->setTitle(title);
    QLabel *descLabel = new QLabel;
    this->parentPanel = parent;
    this->descLabel= descLabel;
    this->layout()->addWidget(descLabel);
}

void ShortComponent::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    if(!this->dynamicFullForm->attributesModel.attributes.isEmpty())
    {
        myMenu.addAction("Change attributes values", this, SLOT(showAttributesForm()));
    }
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.exec(globalPos);
}

void ShortComponent::showAttributesForm()
{
    UsageForm *frame = new UsageForm(this->dynamicFullForm);
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

void ShortComponent::executeTitleAndDescChange()
{
    this->setTitle(this->title);
    this->descLabel->setText(this->description);
}
