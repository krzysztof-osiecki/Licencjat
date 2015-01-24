#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

//XML TAGS
const QString IMPORTS_START_TAG = "<imports>";
const QString IMPORTS_END_TAG = "</imports>";
const QString MAIN_PANEL_START_TAG = "<main_panel>";
const QString MAIN_PANEL_END_TAG = "</main_panel>";
const QString FUNCTIONS_START_TAG = "<function_panel>";
const QString FUNCTIONS_END_TAG = "</function_panel>";
const QString BLOCK_START_TAG = "<block>";
const QString BLOCK_END_TAG = "</block>";
const QString BLOCK_TYPE_START_TAG = "<block_type>";
const QString BLOCK_TYPE_END_TAG = "</block_type>";
const QString CHILDREN_START_TAG = "<children>";
const QString CHILDREN_END_TAG = "</children>";
const QString CONDITION_START_TAG = "<condition>";
const QString CONDITION_END_TAG = "</condition>";
const QString TEXT_START_TAG = "<text>";
const QString TEXT_END_TAG = "</text>";
const QString FUNCTION_NAME_START_TAG = "<function_name>";
const QString FUNCTION_NAME_END_TAG = "</function_name>";
const QString COMPONENT_NAME_START_TAG = "<component_name>";
const QString COMPONENT_NAME_END_TAG = "</component_name>";
const QString COMPONENT_DESCRIPTION_START_TAG = "<component_description>";
const QString COMPONENT_DESCRIPTION_END_TAG = "</component_description>";
const QString ATTRIBUTE_NAME_START_TAG = "<attribute_name>";
const QString ATTRIBUTE_NAME_END_TAG = "</attribute_name>";
const QString PLACEHOLDER_START_TAG = "<placeholder>";
const QString PLACEHOLDER_END_TAG = "</placeholder>";
const QString DESCRIPION_START_TAG = "<description>";
const QString DESCRIPION_END_TAG = "</description>";
const QString TYPE_START_TAG = "<type>";
const QString TYPE_END_TAG = "</type>";
const QString VARIABLE_NAME_START_TAG = "<variable_name>";
const QString VARIABLE_NAME_END_TAG = "</variable_name>";
const QString VARIABLE_TYPE_START_TAG = "<variable_type>";
const QString VARIABLE_TYPE_END_TAG = "</variable_type>";
const QString VARIABLE_VALUE_START_TAG = "<variable_value>";
const QString VARIABLE_VALUE_END_TAG = "</variable_value>";
const QString COMPONENT_START_TAG = "<component>";
const QString COMPONENT_END_TAG = "</component>";
const QString ATTRIBUTE_START_TAG = "<attribute>";
const QString ATTRIBUTE_END_TAG = "</attribute>";
const QString VARIABLE_START_TAG = "<variable>";
const QString VARIABLE_END_TAG = "</variable>";
const QString USAGE_FORM_START_TAG = "<usage_form>";
const QString USAGE_FORM_END_TAG = "</usage_form>";
const QString ATTRIBUTES_TABLE_MODEL_START_TAG = "<attributestablemodel>";
const QString ATTRIBUTES_TABLE_MODEL_END_TAG = "</attributestablemodel>";
const QString VARIABLES_TABLE_MODEL_START_TAG = "<variablestablemodel>";
const QString VARIABLES_TABLE_MODEL_END_TAG = "</variablestablemodel>";

//XML TAGS NAMES
const QString IMPORTS_TAG_NAME = "imports";
const QString BLOCK_TAG_NAME = "block";
const QString BLOCK_TYPE_TAG_NAME = "block_type";
const QString CHILDREN_TAG_NAME = "children";
const QString CONDITION_TAG_NAME = "condition";
const QString TEXT_TAG_NAME = "text";
const QString FUNCTION_NAME_TAG_NAME = "function_name";
const QString ATTRIBUTE_NAME_TAG_NAME = "attribute_name";
const QString COMPONENT_DESCRIPTION_TAG_NAME = "component_description";
const QString COMPONENT_NAME_TAG_NAME = "component_name";
const QString DESCRIPION_TAG_NAME = "description";
const QString PLACEHOLDER_TAG_NAME = "placeholder";
const QString COMPONENT_TAG_NAME = "component";
const QString USAGE_FORM_TAG_NAME = "usage_form";
const QString MAIN_PANEL_TAG_NAME = "main_panel";
const QString FUNCTION_PANEL_TAG_NAME = "function_panel";
const QString TYPE_TAG_NAME = "type";
const QString VARIABLE_TYPE_TAG_NAME = "variable_type";
const QString VARIABLE_NAME_TAG_NAME = "variable_name";
const QString VARIABLE_VALUE_TAG_NAME = "variable_value";
const QString ATTRIBUTES_TABLE_MODEL_TAG_NAME = "attributestablemodel";
const QString VARIABLES_TABLE_MODEL_TAG_NAME = "variablestablemodel";

//BLOCK TYPES
const QString BLOCK_TYPE_FUNCTION = "functionblock";
const QString BLOCK_TYPE_FUNCTION_PANEL = "functionpanel";
const QString BLOCK_TYPE_IF = "ifblock";
const QString BLOCK_TYPE_CONTAINER = "container";
const QString BLOCK_TYPE_IF_ELSE_BLOCK_PANEL = "ifelseblock";
const QString BLOCK_TYPE_IF_PART = "ifpart";
const QString BLOCK_TYPE_ELSE_PART = "elsepart";
const QString BLOCK_TYPE_TEXT_PANEL = "textpanel";
const QString BLOCK_TYPE_WHILE = "whileblock";
const QString BLOCK_TYPE_DYNAMIC = "dynamicblock";

//VARIABLE TYPES
const QString INTEGER_TYPE = "int";
const QString DOULE_TYPE = "double";
const QString BOOL_TYPE = "bool";
const QString CHAR_TYPE = "char";
const QString STRING_TYPE = "string";
const QString INTEGER_VECTOR_TYPE = "vector<int>";
const QString DOUBLE_VECTOR_TYPE = "vector<double>";
const QString BOOL_VECTOR_TYPE = "vector<bool>";
const QString CHAR_VECTOR_TYPE = "vector<char>";
const QString STRING_VECTOR_TYPE = "vector<string>";

//ATTRIBUTES SPECYFICS
const QString NONE_ATTRIBUTES = "none";
const QString ANY_ATTRIBUTES = "any";

#endif // CONSTANTS_H
