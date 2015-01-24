#include "attributestablemodel.h"
#include "attributemodel.h"
#include "Serialization/xmlparser.h"
#include "Constants.h"

QVariant AttributesTableModel::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();
    const AttributeModel & variable = attributes[index.row()];
    switch (index.column()) {
    case 0: return variable.name;
    case 1: return variable.placeholder;
    case 2: return variable.description;
    default: return QVariant();
    };
}

QVariant AttributesTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal) return QVariant();
    if (role != Qt::DisplayRole) return QVariant();
    switch (section) {
    case 0: return "Name";
    case 1: return "Placeholder";
    case 2: return "Description";
    default: return QVariant();
    }
}

void AttributesTableModel::append(const AttributeModel & variable) {
    beginInsertRows(QModelIndex(), attributes.count(), attributes.count());
    attributes.append(variable);
    endInsertRows();
}


void AttributesTableModel::remove(int rowNumber) {
    beginRemoveRows(QModelIndex(), rowNumber, rowNumber);
    attributes.removeAt(rowNumber);
    endRemoveRows();
}

AttributeModel AttributesTableModel::variableAt(int index)
{
    return attributes[index];
}

QString AttributesTableModel::getXml()
{
    QString result = ATTRIBUTES_TABLE_MODEL_START_TAG;
    for(AttributeModel var : this->attributes)
    {
        result += var.getXml();
    }
    result += ATTRIBUTES_TABLE_MODEL_END_TAG;
    return result;
}
