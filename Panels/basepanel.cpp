#include "basepanel.h"
#include "ifblock.h"
#include "ifelseblockpanel.h"
#include "ifelseblockpart.h"
#include "basepanellayout.h"
#include "whileblock.h"
#include "containerpanel.h"
#include "textpanel.h"
#include "shortpanel.h"
#include "Forms/renameframe.h"
#include "Forms/usagedefinitionform.h"
#include "Toolbar/customtoolbar.h"
#include "Toolbar/dynamictoolbar.h"
#include "Serialization/sourcecodebuilder.h"
#include "Serialization/xmlparser.h"
#include "Constants.h"
#include <QMouseEvent>
#include <QDir>
#include <QTextStream>
#include <QApplication>
#include <QMenu>
#include <QLayout>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QGroupBox>

BasePanel* BasePanel::mainPanel = NULL;
BasePanel* BasePanel::functionPanel = NULL;
VariablesTableModel BasePanel::variableModel;
int BasePanel::uniqueIdValue = 0;

BasePanel::BasePanel(bool isFullPanel, BasePanel *parent) : QGroupBox()
{
    QDesktopWidget widget;
    this->parentPanel = parent;
    this->setAlignment(Qt::AlignLeft);
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    this->setMinimumHeight(150);
    this->setMinimumWidth(2*mainScreenSize.width()/13);
    BasePanelLayout *layout = new BasePanelLayout;
    layout->setAlignment(Qt::AlignHCenter);
    layout->setSpacing(40);
    layout->setContentsMargins(160,80,160,80);
    layout->setSizeConstraint(layout->SetFixedSize);
    this->setLayout(layout);
    this->setAlignment(Qt::AlignHCenter);
    this->layout()->setAlignment(Qt::AlignCenter);
    if(isFullPanel)
    {
        this->shortForm = new ShortPanel(false, parent);
        this->shortForm->fullForm = this;
        this->fullForm = this;
    }
    else
    {
        this->shortForm  = (ShortPanel*) this;
    }
}

void BasePanel::executeTitleAndDescChange()
{
    return;
}

void BasePanel::saveAsComponent()
{
    QString result = COMPONENT_START_TAG;
    result += COMPONENT_NAME_START_TAG;
    result += this->componentName;
    result += COMPONENT_NAME_END_TAG;
    result += COMPONENT_DESCRIPTION_START_TAG;
    result += this->description;
    result += COMPONENT_DESCRIPTION_END_TAG;
    result += this->getXml(false);
    result += this->usageFormXml;
    result += COMPONENT_END_TAG;
    QDir dir;
    dir.mkpath(QApplication::applicationDirPath()+QString("/components/"));
    QString location = QApplication::applicationDirPath() + QString("/components/") + this->componentName + QString(".cmp");
    QFile codeFile(location);
    if(codeFile.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        QTextStream writeToFile(&codeFile);
        writeToFile << result << endl;
        codeFile.close();
    }
}

void BasePanel::SetSize(int width, int height)
{
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);
    this->setMinimumWidth(width);
    this->setMaximumWidth(width);
}

void BasePanel::SetHeight(int height)
{
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);
}

void BasePanel::SetWidth(int width)
{
    this->setMinimumWidth(width);
    this->setMaximumWidth(width);
}

void BasePanel::deleteAction()
{
    if(this->parentPanel == NULL){
        QMessageBox::information(this, "Information", "You cannot delete this panel.");
        return;
    }
    this->deleteWithChildren();
}

void BasePanel::renameAction()
{
    RenameFrame *frame = new RenameFrame(this);
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

void BasePanel::exportAsComponent()
{
    UsageDefinitionForm *frame = new UsageDefinitionForm(this);
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

void BasePanel::switchForm()
{
    for(int i = 0; i<this->parentPanel->layout()->count(); i++)
    {
        BasePanel *child = (BasePanel*) this->parentPanel->layout()->itemAt(i)->widget();
        if(child == this)
        {
            BasePanelLayout *layout =(BasePanelLayout*) this->parentPanel->layout();
            layout->removeWidget(child);
            if(this->shortForm == child)
            {
                layout->insertWidget(i, this->fullForm);
                this->shortForm->hide();
                this->fullForm->show();
            }
            else
            {
                layout->insertWidget(i, this->shortForm);
                this->shortForm->show();
                this->fullForm->hide();
            }
        }
    }
}

void BasePanel::mousePressEvent ( QMouseEvent * event )
{
    CustomToolbar::CommandType command = CustomToolbar::selectedCommand;
    if(event->buttons() == Qt::RightButton || (this == this->shortForm && command != CustomToolbar::DELETE))
    {
        return;
    }
    switch(command)
    {
    case CustomToolbar::FUNCTION:
    {
        QMessageBox::information(this, "Information", "Functions can only be placed in function panel.");
        break;
    }
    case CustomToolbar::NONE:
    {
        break;
    }
    case CustomToolbar::DELETE:
    {
        if(this->parentPanel == NULL){
            QMessageBox::information(this, "Information", "You cannot delete this panel.");
            break;
        }
        this->deleteWithChildren();
        break;
    }
    case CustomToolbar::IFELSE:
    {
        PrepareIfElseBlock(event);
        break;
    }
    case CustomToolbar::IF:
    {
        PrepareIfBlock(event);
        break;
    }
    case CustomToolbar::WHILE:
    {
        PrepareWhileBlock(event);
        break;
    }
    case CustomToolbar::TEXT:
    {
        PrepareTextBlock(event);
        break;
    }
    case CustomToolbar::DYNAMIC:
    {
        PrepareDynamicBlock(event);
        break;
    }
    case CustomToolbar::CONTAINER:
    {
        PrepareContainerBlock(event);
        break;
    }
    default:
    {
        break;
    }
    }
}

void BasePanel::PrepareContainerBlock(QMouseEvent *event)
{
    ContainerPanel *newPanel = new ContainerPanel(true, this);
    newPanel->panelType = CustomToolbar::CONTAINER;
    BasePanelLayout *layout = (BasePanelLayout*) this->layout();
    int i = 0;
    while (i < layout->count() && layout->itemAt(i)->widget()->y()<event->y())
    {
        i++;
    }
    layout->setSizeConstraint(layout->SetFixedSize);
    layout->insertWidget(i, newPanel);
    this->children.insert(children.begin()+i, newPanel);
    layout->setAlignment(newPanel, Qt::AlignHCenter);;
}

void BasePanel::PrepareDynamicBlock(QMouseEvent *event)
{
    XmlParser parser;
    DynamicBlock *block = parser.CreateBlockFromXml(DynamicToolbar::xmls.at(DynamicToolbar::selectedIndex), this);
    block->panelType = CustomToolbar::DYNAMIC;
    BasePanelLayout *layout = (BasePanelLayout*) this->layout();
    int i = 0;
    while (i < layout->count() && layout->itemAt(i)->widget()->y()<event->y())
    {
        i++;
    }
    layout->setSizeConstraint(layout->SetFixedSize);
    layout->insertWidget(i, block->shortForm);
    this->children.insert(children.begin()+i, block);
    layout->setAlignment(block, Qt::AlignHCenter);
    if(!block->attributesModel.attributes.isEmpty())
    {
        block->showAttributesForm();
    }
}

void BasePanel::PrepareIfElseBlock(QMouseEvent *event)
{
    IfElseBlockPanel *ifElseBlock = new IfElseBlockPanel(true, this);
    ifElseBlock->layout()->setSizeConstraint(ifElseBlock->layout()->SetFixedSize);

    BasePanelLayout *layout = (BasePanelLayout*) this->layout();
    int i = 0;
    while (i < layout->count() && layout->itemAt(i)->widget()->y()<event->y())
    {
        i++;
    }
    layout->setSizeConstraint(layout->SetFixedSize);
    layout->insertWidget(i, ifElseBlock);
    this->children.insert(this->children.begin()+i, ifElseBlock);
    layout->setAlignment(ifElseBlock, Qt::AlignHCenter);

    PrepareIfPart(ifElseBlock);
    PrepareElsePart(ifElseBlock);

    ifElseBlock->showConditionFrame();
}

void BasePanel::PrepareIfPart(BasePanel *root)
{
    IfElseBlockPart *ifPanel = new IfElseBlockPart(true, root);
    ifPanel->setTitle("if");
    ifPanel->panelType = CustomToolbar::IF;
    root->layout()->addWidget(ifPanel);
    root->children.insert(root->children.begin(), ifPanel);
    root->layout()->setAlignment(ifPanel, Qt::AlignHCenter);
}

void BasePanel::PrepareElsePart(BasePanel *root)
{
    IfElseBlockPart *elsePanel = new IfElseBlockPart(true, root);
    elsePanel->setTitle("else");
    elsePanel->panelType = CustomToolbar::ELSE;
    root->layout()->addWidget(elsePanel);
    root->children.insert(root->children.end(), elsePanel);
    root->layout()->setAlignment(elsePanel, Qt::AlignHCenter);

}

void BasePanel::PrepareIfBlock(QMouseEvent *event)
{
    IfBlock *newPanel = new IfBlock(true, this);
    newPanel->panelType = CustomToolbar::IF;
    BasePanelLayout *layout = (BasePanelLayout*) this->layout();
    int i = 0;
    while (i < layout->count() && layout->itemAt(i)->widget()->y()<event->y())
    {
        i++;
    }
    layout->setSizeConstraint(layout->SetFixedSize);
    layout->insertWidget(i, newPanel);
    this->children.insert(children.begin()+i, newPanel);
    layout->setAlignment(newPanel, Qt::AlignHCenter);
    newPanel->showConditionFrame();
}

void BasePanel::PrepareWhileBlock(QMouseEvent *event)
{
    WhileBlock *newPanel = new WhileBlock(true, this);
    newPanel->panelType = CustomToolbar::WHILE;
    BasePanelLayout *layout = (BasePanelLayout*) this->layout();
    int i = 0;
    while (i < layout->count() && layout->itemAt(i)->widget()->y()<event->y())
    {
        i++;
    }
    layout->setSizeConstraint(layout->SetFixedSize);
    layout->insertWidget(i, newPanel);
    this->children.insert(children.begin()+i, newPanel);
    layout->setAlignment(newPanel, Qt::AlignHCenter);
    newPanel->showConditionFrame();
}

void BasePanel::PrepareTextBlock(QMouseEvent *event)
{
    TextPanel *newPanel = new TextPanel(true, this);
    newPanel->panelType = CustomToolbar::TEXT;
    BasePanelLayout *layout = (BasePanelLayout*) this->layout();
    int i = 0;
    while (i < layout->count() && layout->itemAt(i)->widget()->y()<event->y())
    {
        i++;
    }
    layout->setSizeConstraint(layout->SetFixedSize);
    layout->insertWidget(i, newPanel);
    this->children.insert(children.begin()+i, newPanel);
    layout->setAlignment(newPanel, Qt::AlignHCenter);
}

void BasePanel::deleteWithChildren()
{
    if(this->parentPanel != NULL)
    {
        this->parentPanel->layout()->removeWidget(this);
        this->parentPanel->layout()->removeWidget(this->shortForm);
        this->parentPanel->layout()->removeWidget(this->fullForm);

        for(unsigned int i = 0; i< this->parentPanel->children.size(); i++)
        {
            BasePanel* child = this->parentPanel->children[i];
            if(child == this || child == this->shortForm || child == this->fullForm)
            {
                this->parentPanel->children.erase(this->parentPanel->children.begin()+i);
                break;
            }
        }
        int childrenSize = this->children.size();

        for(int i = 0; i < childrenSize; i++)
        {
            this->children[0]->deleteWithChildren();
        }

        delete this;
    }
}

QString BasePanel::getSourceCode()
{
    QString result =
            QString("int main() \n")
            + QString("{ \n");
    foreach (BasePanel *child, this->children)
    {
        result+=child->getSourceCode();
    }
    result += QString("cin.ignore();");
    result += QString("return 0; \n");
    result += QString("} \n");
    return result;
}

QString BasePanel::getHeader()
{
    return"";
}

QString BasePanel::getHeaders()
{
    return"";
}

QString BasePanel::getXml(bool withDesc)
{
    QString result = MAIN_PANEL_START_TAG;
    result += IMPORTS_START_TAG;
    result += "<![CDATA[" + SourceCodeBuilder::imports + "]]>";
    result += IMPORTS_END_TAG;
    for(BasePanel* child : this->children)
    {
        result += child->getXml();
    }
    result += MAIN_PANEL_END_TAG;
    return result;
}
