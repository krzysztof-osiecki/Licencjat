#include "shortpanel.h"
#include "Panels/basepanel.h"
#include <QMenu>
#include <QLabel>
#include <QContextMenuEvent>

ShortPanel::ShortPanel(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
    this->setTitle("SHORTIE");
    QLabel *descLabel = new QLabel;
    this->descLabel= descLabel;
    this->layout()->addWidget(descLabel);
}

void ShortPanel::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.addAction("Switch form", this, SLOT(switchForm()));
    myMenu.addAction("Rename", this, SLOT(renameAction()));
    myMenu.exec(globalPos);
}

void ShortPanel::executeTitleAndDescChange()
{
    this->setTitle(this->title);
    this->descLabel->setText(this->description);
}
