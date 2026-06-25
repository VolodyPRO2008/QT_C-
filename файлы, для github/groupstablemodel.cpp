#include "groupstablemodel.h"
#include "databasemanager.h"

GroupsTableModel::GroupsTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    refresh();
}

int GroupsTableModel::rowCount(const QModelIndex&) const
{
    return m_filteredGroups.size();
}

int GroupsTableModel::columnCount(const QModelIndex&) const
{
    return 4;  // Название, Курс, Год, Студентов
}

QVariant GroupsTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_filteredGroups.size() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const QStringList& group = m_filteredGroups[index.row()];

    if (group.size() < 5) {
        return QVariant();
    }

    if (index.column() == 0) return group[1];      // Название
    if (index.column() == 1) return group[2];      // Курс
    if (index.column() == 2) return group[3];      // Год
    if (index.column() == 3) return group[4];      // Студентов (автоматический подсчёт)

    return QVariant();
}

QVariant GroupsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        QStringList headers = {"Название", "Курс", "Год", "Студентов"};
        if (section < headers.size()) return headers[section];
    }
    return QVariant();
}

void GroupsTableModel::refresh()
{
    beginResetModel();
    m_groups = DatabaseManager::instance().getAllGroups();
    applyFilter();
    endResetModel();
}

void GroupsTableModel::setFilter(const QString& filterText)
{
    m_filter = filterText;
    beginResetModel();
    applyFilter();
    endResetModel();
}

void GroupsTableModel::applyFilter()
{
    m_filteredGroups.clear();

    if (m_filter.isEmpty()) {
        m_filteredGroups = m_groups;
        return;
    }

    for (const auto& group : m_groups) {
        if (group.size() > 1) {
            QString groupName = group[1];
            if (groupName.contains(m_filter, Qt::CaseInsensitive)) {
                m_filteredGroups.append(group);
            }
        }
    }
}