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
    return 4;  // ID, ФИО, Зачётная книжка, Группа
}

QVariant StudentsTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_students.size() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const QStringList& student = m_students[index.row()];
    if (index.column() == 0) return student[0];  // ID
    if (index.column() == 1) return student[1];  // ФИО
    if (index.column() == 2) return student[2];  // Зачётная книжка
    if (index.column() == 3) return student[3];  // Группа

    return QVariant();
}

QVariant StudentsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        QStringList headers = {"ID", "ФИО", "Зачётная книжка", "Группа"};
        if (section < headers.size()) return headers[section];
    }
    return QVariant();
}

int StudentsTableModel::getStudentId(int row) const
{
    if (row < 0 || row >= m_students.size()) {
        return -1;
    }
    return m_students[row][0].toInt();
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