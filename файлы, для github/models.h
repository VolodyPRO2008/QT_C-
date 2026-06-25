#ifndef MODELS_H
#define MODELS_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>

// ============================================================
// МОДЕЛЬ ДЛЯ РАСПИСАНИЯ УЧЕНИКА (5 колонок)
// ============================================================
class ScheduleModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ScheduleModel(QObject* parent = nullptr);

    void setScheduleData(const QList<QStringList>& data);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<QStringList> m_data;
};

// ============================================================
// МОДЕЛЬ ДЛЯ ПОСЕЩАЕМОСТИ УЧЕНИКА
// ============================================================
class AttendanceViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AttendanceViewModel(QObject* parent = nullptr);

    void setAttendanceData(const QList<QStringList>& data);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // ===== ДЛЯ ПОДСЧЁТА СТАТИСТИКИ =====
    int getTotalCount() const { return m_data.size(); }
    int getPresentCount() const;

private:
    QList<QStringList> m_data;
};

// ============================================================
// МОДЕЛЬ ДЛЯ РАСПИСАНИЯ УЧИТЕЛЯ
// ============================================================
class TeacherScheduleModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TeacherScheduleModel(QObject* parent = nullptr);

    void setScheduleData(const QList<QStringList>& data);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<QStringList> m_data;
};

// ============================================================
// МОДЕЛЬ ДЛЯ ПОЛЬЗОВАТЕЛЕЙ (АДМИН) - С ГРУППОЙ
// ============================================================
class UsersTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit UsersTableModel(QObject* parent = nullptr);

    void setTableData(const QList<QStringList>& data);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<QStringList> m_data;
};

#endif // MODELS_H