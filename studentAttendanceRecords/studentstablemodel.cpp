#include "studentstablemodel.h"
#include "databasemanager.h"

StudentsTableModel::StudentsTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    refresh();
}

int StudentsTableModel::rowCount(const QModelIndex&) const
{
    return m_students.size();
}

int StudentsTableModel::columnCount(const QModelIndex&) const
{
    return 3;
}

QVariant StudentsTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_students.size() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const QStringList& student = m_students[index.row()];
    if (index.column() == 0) return student[1];
    if (index.column() == 1) return student[2];
    if (index.column() == 2) return student[3];

    return QVariant();
}

QVariant StudentsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        QStringList headers = {"ФИО", "Зачётная книжка", "Группа"};
        if (section < headers.size()) return headers[section];
    }
    return QVariant();
}

void StudentsTableModel::refresh()
{
    beginResetModel();
    m_students = DatabaseManager::instance().getAllStudents();
    endResetModel();
}

void StudentsTableModel::refreshByGroup(const QString& groupName)
{
    beginResetModel();
    m_students = DatabaseManager::instance().getStudentsByGroup(groupName);
    endResetModel();
}