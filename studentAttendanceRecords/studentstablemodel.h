#ifndef STUDENTSTABLEMODEL_H
#define STUDENTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>

class StudentsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit StudentsTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void refresh();
    void refreshByGroup(const QString& groupName);

private:
    QList<QStringList> m_students;
};

#endif // STUDENTSTABLEMODEL_H