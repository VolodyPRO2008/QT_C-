#ifndef SCHEDULETAB_H
#define SCHEDULETAB_H

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
#include "databasemanager.h"

// ===== ДИАЛОГ ДЛЯ ДОБАВЛЕНИЯ ПРЕДМЕТА =====
class AddSubjectDialog : public QDialog
{
    Q_OBJECT
public:
    AddSubjectDialog(QWidget* parent = nullptr);
    QString getSubjectName() const;
    int getSemester() const;
    int getHours() const;

private:
    QLineEdit* m_nameEdit;
    QComboBox* m_semesterCombo;
    QSpinBox* m_hoursSpin;
};

// ===== ДИАЛОГ ДЛЯ УСТАНОВКИ/РЕДАКТИРОВАНИЯ ПАРЫ =====
class EditLessonDialog : public QDialog
{
    Q_OBJECT
public:
    EditLessonDialog(QWidget* parent = nullptr, int lessonId = -1);
    int getGroupId() const;
    int getSubjectId() const;
    int getTeacherId() const;
    QDate getDate() const;
    int getLessonNumber() const;
    bool isEditMode() const { return m_lessonId != -1; }

private:
    QComboBox* m_groupCombo;
    QComboBox* m_subjectCombo;
    QComboBox* m_teacherCombo;
    QDateEdit* m_dateEdit;
    QComboBox* m_lessonNumberCombo;
    int m_lessonId;
    void loadLessonData();
};

// ===== ОСНОВНАЯ ВКЛАДКА =====
class ScheduleTab : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleTab(QWidget* parent = nullptr, int userRole = -1);

public slots:
    void refresh();
    void addSubject();
    void addLesson();
    void editLesson();
    void deleteLesson();
    void onDateChanged(const QDate& date);
    void onTableRowSelected(const QModelIndex& current, const QModelIndex& previous);

private:
    QDateEdit* m_dateEdit;
    QTableView* m_tableView;
    QAbstractTableModel* m_model;
    QStatusBar* m_statusBar;
    int m_userRole;
    int m_selectedLessonId;

    // Кнопки
    QPushButton* m_addSubjectButton;
    QPushButton* m_addLessonButton;
    QPushButton* m_editLessonButton;
    QPushButton* m_deleteLessonButton;  // <-- НОВАЯ КНОПКА

    void setupUI();
    void setupPermissions();
    void loadSchedule(const QDate& date);
    bool isLessonSelected() const;
};

#endif // SCHEDULETAB_H