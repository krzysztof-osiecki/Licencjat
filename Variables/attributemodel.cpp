#include "attributemodel.h"
#include "Serialization/xmlparser.h"
#include "Constants.h"

AttributeModel::AttributeModel(QString name, QString description, QString placeholder, QString variableType):name(name), description(description), placeholder(placeholder), variableType(variableType)
{
}

QString AttributeModel::getXml()
{
    QString result = ATTRIBUTE_START_TAG;
    result += ATTRIBUTE_NAME_START_TAG;
    result += this->name;
    result += ATTRIBUTE_NAME_END_TAG;
    result += PLACEHOLDER_START_TAG;
    result += this->placeholder;
    result += PLACEHOLDER_END_TAG;
    result += DESCRIPION_START_TAG;
    result += this->description;
    result += DESCRIPION_END_TAG;
    result += VARIABLE_TYPE_START_TAG;
    result += this->variableType;
    result += VARIABLE_TYPE_END_TAG;
    result += ATTRIBUTE_END_TAG;
    return result;
}
