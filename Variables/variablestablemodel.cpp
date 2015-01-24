#include "variablestablemodel.h"
#include "variablemodel.h"
#include "Serialization/xmlparser.h"
#include "Constants.h"

QVariant VariablesTableModel::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();
    const VariableModel & variable = variables[index.row()];
    switch (index.column()) {
    case 0: return variable.type;
    case 1: return variable.name;
    case 2: return variable.value;
    default: return QVariant();
    };
}

QVariant VariablesTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal) return QVariant();
    if (role != Qt::DisplayRole) return QVariant();
    switch (section) {
    case 0: return "Type";
    case 1: return "Name";
    case 2: return "Value";
    default: return QVariant();
    }
}

void VariablesTableModel::append(const VariableModel & variable) {
    beginInsertRows(QModelIndex(), variables.count(), variables.count());
    variables.append(variable);
    endInsertRows();
}

void VariablesTableModel::remove(int rowNumber) {
    beginRemoveRows(QModelIndex(), rowNumber, rowNumber);
    variables.removeAt(rowNumber);
    endRemoveRows();
}

VariableModel VariablesTableModel::variableAt(int index)
{
    return variables.at(index);
}

QString VariablesTableModel::getXml()
{
    QString result = VARIABLES_TABLE_MODEL_START_TAG;
    for(VariableModel var : this->variables)
    {
        result += var.getXml();
    }
    result += VARIABLES_TABLE_MODEL_END_TAG;
    return result;
}
