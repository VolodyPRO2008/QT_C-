#include "groupstablemodel.h"
#include "databasemanager.h"

GroupsTableModel::GroupsTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    refresh();
}

int GroupsTableModel::rowCount(const QModelIndex&) const
{
    return m_groups.size();
}

int GroupsTableModel::columnCount(const QModelIndex&) const
{
    return 3;
}

QVariant GroupsTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_groups.size() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const QStringList& group = m_groups[index.row()];
    if (index.column() == 0) return group[1];
    if (index.column() == 1) return group[2];
    if (index.column() == 2) return group[3];

    return QVariant();
}

QVariant GroupsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        QStringList headers = {"Название", "Курс", "Год"};
        if (section < headers.size()) return headers[section];
    }
    return QVariant();
}

void GroupsTableModel::refresh()
{
    beginResetModel();
    m_groups = DatabaseManager::instance().getAllGroups();
    endResetModel();
}