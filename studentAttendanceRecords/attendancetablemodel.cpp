#include "attendancetablemodel.h"
#include "databasemanager.h"

AttendanceTableModel::AttendanceTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int AttendanceTableModel::rowCount(const QModelIndex&) const
{
    return m_records.size();
}

int AttendanceTableModel::columnCount(const QModelIndex&) const
{
    return 3;
}

QVariant AttendanceTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_records.size()) {
        return QVariant();
    }

    const AttendanceRecord& record = m_records[index.row()];

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) return record.fullName;
        if (index.column() == 1) return record.status ? "Присутствовал" : "Отсутствовал";
        if (index.column() == 2) return record.comment;
    }

    if (role == Qt::EditRole && index.column() == 1) {
        return record.status;
    }

    return QVariant();
}

bool AttendanceTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || index.row() >= m_records.size() || role != Qt::EditRole || index.column() != 1) {
        return false;
    }

    m_records[index.row()].status = value.toBool();
    emit dataChanged(index, index);
    return true;
}

QVariant AttendanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        QStringList headers = {"ФИО", "Статус", "Комментарий"};
        if (section < headers.size()) return headers[section];
    }
    return QVariant();
}

Qt::ItemFlags AttendanceTableModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::ItemIsEnabled;

    if (index.column() == 1) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void AttendanceTableModel::refreshByGroup(const QString& groupName)
{
    beginResetModel();
    m_records.clear();

    auto students = DatabaseManager::instance().getStudentsByGroup(groupName);
    for (const auto& student : students) {
        AttendanceRecord record;
        record.studentId = student[0].toInt();
        record.fullName = student[1];
        record.status = false;
        record.comment = "";
        m_records.append(record);
    }

    endResetModel();
}