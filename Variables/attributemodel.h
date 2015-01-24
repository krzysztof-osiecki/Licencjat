#ifndef ATTRIBUTEMODEL_H
#define ATTRIBUTEMODEL_H

#include <QString>
#include <QVariant>

class AttributeModel
{
public:
    AttributeModel(QString name, QString description, QString placeholder, QString variableType);
    QString name;
    QString description;
    QString placeholder;
    QString value;
    QString variableType;
    QString getXml();
};

#endif // ATTRIBUTEMODEL_H
