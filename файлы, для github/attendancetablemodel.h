#ifndef ATTENDANCETABLEMODEL_H
#define ATTENDANCETABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>

struct AttendanceRecord {
    int studentId;
    QString fullName;
    bool status;
    QString comment;
};

class AttendanceTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AttendanceTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void refreshByGroup(const QString& groupName);

private:
    QList<AttendanceRecord> m_records;
};

#endif