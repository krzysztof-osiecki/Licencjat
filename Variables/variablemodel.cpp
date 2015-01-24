#include "variablemodel.h"
#include "Serialization/xmlparser.h"
#include "Constants.h"

VariableModel::VariableModel(QString type, QString name, QString value):type(type), name(name), value(value)
{
}

QString VariableModel::getXml()
{
    QString result = VARIABLE_START_TAG;
    result += VARIABLE_NAME_START_TAG;
    result += this->name;
    result += VARIABLE_NAME_END_TAG;
    result += VARIABLE_TYPE_START_TAG;
    result += this->type;
    result += VARIABLE_TYPE_END_TAG;
    result += VARIABLE_VALUE_START_TAG;
    result += this->value;
    result += VARIABLE_VALUE_END_TAG;
    result += VARIABLE_END_TAG;
    return result;
}
