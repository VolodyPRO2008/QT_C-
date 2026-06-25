#ifndef GROUPSTABLEMODEL_H
#define GROUPSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>

class GroupsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GroupsTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void refresh();
    void setFilter(const QString& filterText);

private:
    void applyFilter();

private:
    QList<QStringList> m_groups;
    QList<QStringList> m_filteredGroups;
    QString m_filter;
};

#endif // GROUPSTABLEMODEL_H