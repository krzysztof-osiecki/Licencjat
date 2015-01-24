#include "textpanel.h"
#include "Serialization/xmlparser.h"
#include "textblock.h"
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QMenu>
#include "Constants.h"

TextPanel::TextPanel(bool isFullPanel, BasePanel *parent) : BasePanel(isFullPanel, parent)
{
    this->panelType = CustomToolbar::TEXT;
    this->setTitle("Your code.");
    TextBlock *textBlock = new TextBlock;
    this->textBlock = textBlock;
    this->layout()->addWidget(textBlock);
}

void TextPanel::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::RightButton)
    {
        return;
    }
    CustomToolbar::CommandType command = CustomToolbar::selectedCommand;
    switch(command)
    {
    case CustomToolbar::DELETE:
    {
        this->deleteWithChildren();
        break;
    }
    default:
    {
        break;
    }
    }
}

void TextPanel::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint globalPos = this->mapToGlobal(event->pos());
    QMenu myMenu;
    myMenu.addAction("Switch form", this, SLOT(switchForm()));
    myMenu.addAction("Export as component", this, SLOT(exportAsComponent()));
    myMenu.addAction("Delete", this, SLOT(deleteAction()));
    myMenu.exec(globalPos);
}

TextBlock* TextPanel::GetTextBlock()
{
    return this->textBlock;
}

QString TextPanel::getSourceCode()
{
    return this->textBlock->toPlainText();
}

QString TextPanel::getXml(bool withDesc)
{
    QString result = BLOCK_START_TAG;
    result += BLOCK_TYPE_START_TAG;
    result += "textpanel";
    result += BLOCK_TYPE_END_TAG;
    result += TEXT_START_TAG;
    result += "<![CDATA[" + this->textBlock->toPlainText() + "]]>";
    result += TEXT_END_TAG;
    result += BLOCK_END_TAG;
    return result;
}
