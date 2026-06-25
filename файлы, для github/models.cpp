#include "models.h"

ScheduleModel::ScheduleModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void ScheduleModel::setScheduleData(const QList<QStringList>& data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
}

int ScheduleModel::rowCount(const QModelIndex&) const
{
    return m_data.size();
}

int ScheduleModel::columnCount(const QModelIndex&) const
{
    return 5;  // Дата, Дисциплина, Преподаватель, Пара, Аудитория
}

QVariant ScheduleModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.row() >= m_data.size() || index.column() >= m_data[index.row()].size()) {
        return QVariant();
    }

    return m_data[index.row()][index.column()];
}

QVariant ScheduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QVariant();
    }

    QStringList headers = {"Дата", "Дисциплина", "Преподаватель", "Пара", "Аудитория"};
    if (section < headers.size()) {
        return headers[section];
    }

    return QVariant();
}
// ============================================================
// AttendanceViewModel
// ============================================================
AttendanceViewModel::AttendanceViewModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void AttendanceViewModel::setAttendanceData(const QList<QStringList>& data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
}

int AttendanceViewModel::rowCount(const QModelIndex&) const
{
    return m_data.size();
}

int AttendanceViewModel::columnCount(const QModelIndex&) const
{
    return 4;
}

QVariant AttendanceViewModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.row() >= m_data.size() || index.column() >= m_data[index.row()].size()) {
        return QVariant();
    }

    return m_data[index.row()][index.column()];
}

QVariant AttendanceViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QVariant();
    }

    QStringList headers = {"Дата", "Дисциплина", "Статус", "Комментарий"};
    if (section < headers.size()) {
        return headers[section];
    }

    return QVariant();
}

// ============================================================
// TeacherScheduleModel
// ============================================================
TeacherScheduleModel::TeacherScheduleModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void TeacherScheduleModel::setScheduleData(const QList<QStringList>& data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
}

int TeacherScheduleModel::rowCount(const QModelIndex&) const
{
    return m_data.size();
}

int TeacherScheduleModel::columnCount(const QModelIndex&) const
{
    return 3;
}

QVariant TeacherScheduleModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.row() >= m_data.size() || index.column() >= m_data[index.row()].size()) {
        return QVariant();
    }

    return m_data[index.row()][index.column()];
}

QVariant TeacherScheduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QVariant();
    }

    QStringList headers = {"Дата", "Дисциплина", "Группа"};
    if (section < headers.size()) {
        return headers[section];
    }

    return QVariant();
}

// ============================================================
// UsersTableModel - С ГРУППОЙ
// ============================================================
UsersTableModel::UsersTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void UsersTableModel::setTableData(const QList<QStringList>& data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
}

int UsersTableModel::rowCount(const QModelIndex&) const
{
    return m_data.size();
}

int UsersTableModel::columnCount(const QModelIndex&) const
{
    return 4;  // ID, ФИО, Роль, Группа
}

QVariant UsersTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.row() >= m_data.size() || index.column() >= m_data[index.row()].size()) {
        return QVariant();
    }

    if (index.column() == 2) {
        int roleInt = m_data[index.row()][2].toInt();
        if (roleInt == 0) return "Ученик";
        if (roleInt == 1) return "Преподаватель";
        if (roleInt == 2) return "Администратор";
        return "Неизвестно";
    }

    return m_data[index.row()][index.column()];
}

QVariant UsersTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QVariant();
    }

    QStringList headers = {"ID", "ФИО", "Роль", "Группа"};
    if (section < headers.size()) {
        return headers[section];
    }

    return QVariant();
}
int AttendanceViewModel::getPresentCount() const
{
    int count = 0;
    for (const auto& record : m_data) {
        if (record.size() >= 3 && record[2] == "Присутствовал") {
            count++;
        }
    }
    return count;
}