#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

//-----------------------------------------------------------------
int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_gridData.size();
}

//-----------------------------------------------------------------
int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return COLS;
}

//-----------------------------------------------------------------
QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && checkIndex(index))
            return m_gridData[index.row()][index.column()];
    if(role == Qt::BackgroundRole && checkIndex(index)){
        if(index.column() == 8 || index.column() == 9)
            return QVariant(QBrush(Qt::gray));
        const QAbstractItemModel *model = index.model();
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Debut Match")){
            if(index.column() == 6 || index.column() == 7)
                return QVariant(QBrush(Qt::gray));
        }
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Ligne Droite")){
            if(index.column() == 3 || index.column() == 4 || index.column() == 5 )
                return QVariant(QBrush(Qt::gray));
        }
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Rotation")){
            if(index.column() == 4 || index.column() == 5 )
                return QVariant(QBrush(Qt::gray));
        }
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Courbe")){
            if(index.column() == 5 )
                return QVariant(QBrush(Qt::gray));
        }
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Action")){
            if(index.column() == 4 || index.column() == 5 )
                return QVariant(QBrush(Qt::gray));
        }
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Recalage")){
            if(index.column() == 8 )
                return QVariant(QBrush(Qt::gray));
        }
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("XYT")){
            if(index.column() == 8 )
                return QVariant(QBrush(Qt::gray));
        }
    }
    return QVariant();
}

//-----------------------------------------------------------------

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();
        QString result;
        for (int row = 0; row < m_gridData.size(); row++) {
            for (int col= 0; col < COLS; col++)
                result += m_gridData[row][col] + ' ';
        }
        emit editCompleted(result);
        return true;
    }
    return false;
}

//-----------------------------------------------------------------

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;
    const QAbstractItemModel *model = index.model();
    if(index.column() == 8 || index.column() == 9)
        return flags;
    if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Debut Match")){
        if(index.column() == 6 || index.column() == 7)
             return flags;
    }
    if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Ligne Droite")){
        if(index.column() == 3 || index.column() == 4 || index.column() == 5 )
             return flags;
    }
    if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Rotation")){
        if(index.column() == 4 || index.column() == 5 )
             return flags;
    }
    if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Courbe")){
        if(index.column() == 5 )
             return flags;
    }
    if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Action")){
        if(index.column() == 4 || index.column() == 5 )
             return flags;
    }
    if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Recalage")){
        if(index.column() == 8 )
             return flags;
    }
    if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("XYT")){
        if(index.column() == 8 )
             return flags;
    }
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

//-----------------------------------------------------------------
bool MyModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    for (int i=0; i<count; i++) {
        QVector<QString> newData(COLS);
        m_gridData.insert(row, newData);
    }
    endInsertRows();
    return true;
}

//-----------------------------------------------------------------
bool MyModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row<0 || row >= m_gridData.size() || row+count > m_gridData.size())
        return false;
    beginRemoveRows(parent, row, row+count-1);
    for(int i=0; i<count; i++){
        m_gridData.remove(row);
    }
    endRemoveRows();
    return true;
}

//-----------------------------------------------------------------
bool MyModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if ((role==Qt::DisplayRole)&&(orientation==Qt::Horizontal)){
        header[section] = value.toString();
        emit headerDataChanged(Qt::Horizontal,0,COLS);
        return true;
    }
    return QAbstractTableModel::setHeaderData(section,orientation,value,role);
}

//-----------------------------------------------------------------
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role==Qt::DisplayRole)&&(orientation==Qt::Horizontal)) return header[section];
    return QAbstractTableModel::headerData(section,orientation,role);
}
