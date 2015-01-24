#include "xmlparser.h"
#include "pugixml.hpp"
#include "Panels/basepanel.h"
#include "Panels/functionblock.h"
#include "Panels/functionpanel.h"
#include "Panels/ifblock.h"
#include "Panels/ifelseblockpanel.h"
#include "Panels/ifelseblockpart.h"
#include "Panels/textblock.h"
#include "Panels/textpanel.h"
#include "Panels/whileblock.h"
#include "Panels/dynamicblock.h"
#include "Panels/containerpanel.h"
#include "Serialization/sourcecodebuilder.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "Constants.h"
#define tca(qString) qString.toStdString().c_str()

void XmlParser::ParseAndSaveXml(BasePanel* root, QString name)
{
    QString result = root->getXml();
    QFile codeFile(name);
    if(codeFile.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        QTextStream writeToFile(&codeFile);
        writeToFile << result << endl;
        codeFile.close();
    }
}

void XmlParser::ParseAndSaveXml(BasePanel* root, BasePanel* function, QString name)
{
    QString result = root->getXml();
    result += function->getXml();
    result += BasePanel::variableModel.getXml();
    QFile codeFile(name);
    if(codeFile.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        QTextStream writeToFile(&codeFile);
        writeToFile << result << endl;
        codeFile.close();
    }
}

DynamicBlock* XmlParser::CreateBlockFromXml(QString xml, BasePanel* root)
{
    pugi::xml_document doc;
    const char *xmlChar = tca(xml);
    doc.load_string(xmlChar);
    DynamicBlock *block = new DynamicBlock(true, root);
    block->panelType = CustomToolbar::DYNAMIC;
    block->componentName = doc.first_child().child_value(tca(COMPONENT_NAME_TAG_NAME));
    block->description =  doc.first_child().child_value(tca(COMPONENT_DESCRIPTION_TAG_NAME));
    block->shortForm->title = block->componentName;
    block->shortForm->description = block->description;
    block->shortForm->executeTitleAndDescChange();
    pugi::xml_node node = doc.first_child().first_child();
    while(node)
    {
        QString name = node.name();
        if(name == BLOCK_TAG_NAME)
        {
            AddBlockFromNode(node, block);
        }
        else if(name == ATTRIBUTES_TABLE_MODEL_TAG_NAME)
        {
            pugi::xml_node attributeNode = node.first_child();
            while(attributeNode)
            {
                QString d = attributeNode.child_value(tca(DESCRIPION_TAG_NAME));
                QString n = attributeNode.child_value(tca(ATTRIBUTE_NAME_TAG_NAME));
                QString p = attributeNode.child_value(tca(PLACEHOLDER_TAG_NAME));
                QString t = attributeNode.child_value(tca(VARIABLE_TYPE_TAG_NAME));
                AttributeModel attribute = AttributeModel(n, d, p, t);
                block->attributesModel.append(attribute);
                attributeNode = attributeNode.next_sibling();
            }
        }
        node = node.next_sibling();
    }
    return block;
}

void XmlParser::CreatePanelStructureFromXml(QString xml)
{
    BasePanel *root = new BasePanel(true, 0);
    BasePanel *functionRoot = new BasePanel(true, 0);
    pugi::xml_document doc;
    const char *xmlChar = tca(xml);
    doc.load_string(xmlChar);
    pugi::xml_node outerNode = doc.first_child();
    SourceCodeBuilder::imports = outerNode.child_value(tca(IMPORTS_TAG_NAME));
    QString name = outerNode.name();
    while(outerNode)
    {
        name = outerNode.name();
        if(name == MAIN_PANEL_TAG_NAME)
        {
            pugi::xml_node node = outerNode.first_child();
            while(node)
            {
                name = node.name();
                if(name == BLOCK_TAG_NAME)
                {
                    AddBlockFromNode(node, root);
                }
                node = node.next_sibling();
            }
            QLayoutItem *child;
            while ((child = BasePanel::mainPanel->layout()->takeAt(0)) != 0) {
                QWidget* stepchild;
                stepchild=child->widget();
                delete stepchild;
                delete child;
            }
            BasePanel::mainPanel->children.clear();
            for(BasePanel* child : root->children)
            {
                if(child->panelType == CustomToolbar::DYNAMIC)
                {
                    BasePanel::mainPanel->layout()->addWidget(child->shortForm);
                }
                else
                {
                    BasePanel::mainPanel->layout()->addWidget(child);
                }
                BasePanel::mainPanel->children.push_back(child);
            }
        }
        else if(name == FUNCTION_PANEL_TAG_NAME)
        {
            pugi::xml_node node = outerNode.first_child();
            while(node)
            {
                name = node.name();
                if(name == BLOCK_TAG_NAME)
                {
                    AddBlockFromNode(node, functionRoot);
                }
                node = node.next_sibling();
            }
            QLayoutItem *child;
            while ((child = BasePanel::functionPanel->layout()->takeAt(0)) != 0) {
                QWidget* stepchild;
                stepchild=child->widget();
                delete stepchild;
                delete child;
            }
            BasePanel::functionPanel->children.clear();
            for(BasePanel* child : functionRoot->children)
            {
                if(child->panelType == CustomToolbar::DYNAMIC)
                {
                    BasePanel::functionPanel->layout()->addWidget(child->shortForm);
                }
                else
                {
                    BasePanel::functionPanel->layout()->addWidget(child);
                }
                BasePanel::functionPanel->children.push_back(child);
            }

        }
        else if(name == VARIABLES_TABLE_MODEL_TAG_NAME)
        {
            pugi::xml_node variablesNode = outerNode.first_child();
            while(variablesNode)
            {
                QString t = variablesNode.child_value(tca(VARIABLE_TYPE_TAG_NAME));
                QString n = variablesNode.child_value(tca(VARIABLE_NAME_TAG_NAME));
                QString v = variablesNode.child_value(tca(VARIABLE_VALUE_TAG_NAME));
                VariableModel attribute = VariableModel(t, n, v);
                BasePanel::variableModel.append(attribute);
                variablesNode = variablesNode.next_sibling();
            }
        }
        outerNode = outerNode.next_sibling();
    }
}

void XmlParser::AddBlockFromNode(pugi::xml_node blockNode, BasePanel* root)
{
    QString blockType = blockNode.child_value(tca(BLOCK_TYPE_TAG_NAME));
    if(blockType == BLOCK_TYPE_FUNCTION)
    {
        PrepareFunctionBlock(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_FUNCTION_PANEL)
    {
        PrepareFunctionPanel(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_IF)
    {
        PrepareIfBlock(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_IF_ELSE_BLOCK_PANEL)
    {
        PrepareIfElseBlockPanel(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_IF_PART)
    {
        PrepareIfPart(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_ELSE_PART)
    {
        PrepareElsePart(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_TEXT_PANEL)
    {
        PrepareTextPanel(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_WHILE)
    {
        PrepareWhileBlock(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_DYNAMIC)
    {
        PrepareDynamicBlock(blockNode, root);
    }
    else if(blockType == BLOCK_TYPE_CONTAINER)
    {
        PrepareContainerPanel(blockNode, root);
    }
}

void XmlParser::PrepareContainerPanel(pugi::xml_node blockNode, BasePanel *root)
{
    ContainerPanel *block = new ContainerPanel(true, root);
    block->panelType = CustomToolbar::CONTAINER;
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::HandleChildrenNode(pugi::xml_node childrenNode, BasePanel* root )
{
    pugi::xml_node node = childrenNode.first_child();
    while(node)
    {
        AddBlockFromNode(node, root);
        node = node.next_sibling(tca(BLOCK_TAG_NAME));
    }
}

void XmlParser::PrepareFunctionBlock(pugi::xml_node blockNode, BasePanel* root)
{
    FunctionBlock *block = new FunctionBlock(true, root);
    block->name = blockNode.child_value(tca(FUNCTION_NAME_TAG_NAME));
    block->type = blockNode.child_value(tca(TYPE_TAG_NAME));
    pugi::xml_node variablesNode = blockNode.child(tca(VARIABLES_TABLE_MODEL_TAG_NAME)).first_child();
    while(variablesNode)
    {
        QString t = variablesNode.child_value(tca(VARIABLE_TYPE_TAG_NAME));
        QString n = variablesNode.child_value(tca(VARIABLE_NAME_TAG_NAME));
        QString v = variablesNode.child_value(tca(VARIABLE_VALUE_TAG_NAME));
        VariableModel attribute = VariableModel(t, n, v);
        block->parametersModel.append(attribute);
        variablesNode = variablesNode.next_sibling();
    }
    block->panelType = CustomToolbar::FUNCTION;
    block->setTitle(block->type + " " + block->name);
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::PrepareFunctionPanel(pugi::xml_node blockNode, BasePanel* root)
{
    FunctionPanel *block = new FunctionPanel(true, root);
    block->panelType = CustomToolbar::FUNCTION_PANEL;
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::PrepareIfBlock(pugi::xml_node blockNode, BasePanel* root)
{
    IfBlock *block = new IfBlock(true, root);
    block->condition = blockNode.child_value(tca(CONDITION_TAG_NAME));
    block->panelType = CustomToolbar::IF;
    block->setTitle("if("+ block->condition+")");
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::PrepareIfElseBlockPanel(pugi::xml_node blockNode, BasePanel* root)
{
    IfElseBlockPanel *block = new IfElseBlockPanel(true, root);
    block->panelType = CustomToolbar::IFELSE;
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::PrepareIfPart(pugi::xml_node blockNode, BasePanel* root)
{
    IfElseBlockPart *block = new IfElseBlockPart(true, root);
    block->condition = blockNode.child_value(tca(CONDITION_TAG_NAME));
    block->panelType = CustomToolbar::IF;
    block->setTitle("if("+ block->condition+")");
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::PrepareElsePart(pugi::xml_node blockNode, BasePanel* root)
{
    IfElseBlockPart *block = new IfElseBlockPart(true, root);
    block->panelType = CustomToolbar::ELSE;
    block->setTitle("if("+ block->condition+")");
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::PrepareTextPanel(pugi::xml_node blockNode, BasePanel* root)
{
    TextPanel *block = new TextPanel(true, root);
    block->GetTextBlock()->setText(blockNode.child_value(tca(TEXT_TAG_NAME)));
    block->panelType = CustomToolbar::TEXT;
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::PrepareWhileBlock(pugi::xml_node blockNode, BasePanel* root)
{
    WhileBlock *block = new WhileBlock(true, root);
    block->condition = blockNode.child_value(tca(CONDITION_TAG_NAME));
    block->panelType = CustomToolbar::WHILE;
    block->setTitle("loop("+ block->condition+")");
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block);
}

void XmlParser::PrepareDynamicBlock(pugi::xml_node blockNode, BasePanel* root)
{
    DynamicBlock *block = new DynamicBlock(true, root);
    block->componentName = blockNode.child_value(tca(COMPONENT_NAME_TAG_NAME));
    block->description =  blockNode.child_value(tca(COMPONENT_DESCRIPTION_TAG_NAME));
    block->shortForm->title = block->componentName;
    block->shortForm->description = block->description;
    block->shortForm->executeTitleAndDescChange();
    block->panelType = CustomToolbar::DYNAMIC;
    pugi::xml_node childrenNode = blockNode.child(tca(CHILDREN_TAG_NAME));
    HandleChildrenNode(childrenNode, block);
    root->children.push_back(block);
    root->layout()->addWidget(block->shortForm);
}


