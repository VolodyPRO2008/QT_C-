#include "reporttablemodel.h"
#include "databasemanager.h"

ReportTableModel::ReportTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int ReportTableModel::rowCount(const QModelIndex&) const
{
    return m_reportData.size();
}

int ReportTableModel::columnCount(const QModelIndex&) const
{
    return 5;
}

QVariant ReportTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_reportData.size() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const QStringList& row = m_reportData[index.row()];
    if (index.column() < row.size()) return row[index.column()];

    return QVariant();
}

QVariant ReportTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        QStringList headers = {"ID", "ФИО", "Всего занятий", "Посещений", "Опозданий"};
        if (section < headers.size()) return headers[section];
    }
    return QVariant();
}

void ReportTableModel::refresh(const QString& groupName, const QString& startDate, const QString& endDate)
{
    beginResetModel();
    m_reportData = DatabaseManager::instance().generateReport(groupName, startDate, endDate);
    endResetModel();
}