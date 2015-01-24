#ifndef ATTRIBUTESTABLEMODEL_H
#define ATTRIBUTESTABLEMODEL_H

#include "attributemodel.h"
#include <vector>
#include <QAbstractTableModel>

class AttributesTableModel : public QAbstractTableModel
{
public:
    AttributesTableModel(int columnCount = 3, QObject * parent = 0) : QAbstractTableModel(parent), columnCountNumber(columnCount) {}
    QList<AttributeModel> attributes;
    int rowCount(const QModelIndex &) const { return attributes.count(); }
    int columnCount(const QModelIndex &) const { return columnCountNumber; }
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void append(const AttributeModel & variable);
    void remove(int rowNumber);
    AttributeModel variableAt(int index);
    QString getXml();
private:
    int columnCountNumber;
};

#endif // ATTRIBUTESTABLEMODEL_H
