#ifndef ATTENDANCETAB_H
#define ATTENDANCETAB_H

#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDate>
#include <QGroupBox>
#include <QStatusBar>
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QHeaderView>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include "databasemanager.h"

// ===== ДИАЛОГ ДЛЯ РЕДАКТИРОВАНИЯ ПОСЕЩАЕМОСТИ =====
class EditAttendanceDialog : public QDialog
{
    Q_OBJECT
public:
    EditAttendanceDialog(int attendanceId, int studentId, const QString& studentName, bool currentStatus, const QString& currentComment, QWidget* parent = nullptr);
    bool getNewStatus() const;
    QString getNewComment() const;

private:
    QComboBox* m_statusCombo;
    QLineEdit* m_commentEdit;
};

// ===== ОСНОВНАЯ ВКЛАДКА =====
class AttendanceEditTab : public QWidget
{
    Q_OBJECT
public:
    explicit AttendanceEditTab(QWidget* parent = nullptr, int userRole = -1);

signals:
    void attendanceUpdated();

public slots:
    void refresh();
    void editAttendance();
    void deleteAttendance();
    void exportAttendanceToCSV();
    void onDateChanged(const QDate& date);
    void onTableRowSelected(const QModelIndex& current, const QModelIndex& previous);

private:
    QDateEdit* m_dateEdit;
    QTableView* m_tableView;
    QAbstractTableModel* m_model;
    QStatusBar* m_statusBar;
    int m_userRole;
    int m_selectedAttendanceId;

    // Кнопки
    QPushButton* m_editButton;
    QPushButton* m_deleteButton;
    QPushButton* m_exportButton;  // <-- НОВАЯ КНОПКА

    void setupUI();
    void setupPermissions();
    void loadAttendance(const QDate& date);
    bool isAttendanceSelected() const;
};

#endif // ATTENDANCETAB_H