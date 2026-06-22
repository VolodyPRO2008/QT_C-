#ifndef REPORTTABLEMODEL_H
#define REPORTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>

class ReportTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ReportTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void refresh(const QString& groupName, const QString& startDate, const QString& endDate);

private:
    QList<QStringList> m_reportData;
};

#endif // REPORTTABLEMODEL_H