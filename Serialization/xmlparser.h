#ifndef XMLPARSER_H
#define XMLPARSER_H
#include "pugixml.hpp"
#include "Panels/basepanel.h"
#include "Panels/dynamicblock.h"

class XmlParser
{
public:
    void ParseAndSaveXml(BasePanel* root, QString name = "");
    void ParseAndSaveXml(BasePanel* root, BasePanel* function, QString name = "");
    void CreatePanelStructureFromXml(QString xml);
    void HandleChildrenNode(pugi::xml_node childrenNode, BasePanel* root );
    void AddBlockFromNode(pugi::xml_node blockNode, BasePanel* root );
    void PrepareContainerPanel(pugi::xml_node blockNode, BasePanel* root);
    void PrepareFunctionBlock(pugi::xml_node blockNode, BasePanel* root);
    void PrepareFunctionPanel(pugi::xml_node blockNode, BasePanel* root);
    void PrepareIfBlock(pugi::xml_node blockNode, BasePanel* root);
    void PrepareIfElseBlockPanel(pugi::xml_node blockNode, BasePanel* root);
    void PrepareIfPart(pugi::xml_node blockNode, BasePanel* root);
    void PrepareElsePart(pugi::xml_node blockNode, BasePanel* root);
    void PrepareTextPanel(pugi::xml_node blockNode, BasePanel* root);
    void PrepareWhileBlock(pugi::xml_node blockNode, BasePanel* root);
    void PrepareDynamicBlock(pugi::xml_node blockNode, BasePanel* root);
    DynamicBlock* CreateBlockFromXml(QString xml, BasePanel* root);

};

#endif // XMLPARSER_H
