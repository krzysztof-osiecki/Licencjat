#ifndef VARIABLESTABLEMODEL_H
#define VARIABLESTABLEMODEL_H

#include "variablemodel.h"
#include <vector>
#include <QAbstractTableModel>

class VariablesTableModel : public QAbstractTableModel
{
public:
    VariablesTableModel(int columnCount = 3, QObject * parent = 0) : QAbstractTableModel(parent), columnCountNumber(columnCount) {}
    QList<VariableModel> variables;
    int rowCount(const QModelIndex &) const { return variables.count(); }
    int columnCount(const QModelIndex &) const { return columnCountNumber; }
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void append(const VariableModel & variable);
    void remove(int rowNumber);
    VariableModel variableAt(int index);
    QString getXml();
private:
    int columnCountNumber;
};


#endif // VARIABLESTABLEMODEL_H
