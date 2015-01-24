#ifndef VARIABLEMODEL_H
#define VARIABLEMODEL_H

#include <QString>
#include <QVariant>

class VariableModel
{
public:
    VariableModel(QString type, QString name, QString value="");
    QString type;
    QString name;
    QString value;
    QString getXml();
};

#endif // VARIABLEMODEL_H
