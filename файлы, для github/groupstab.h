#ifndef GROUPSTAB_H
#define GROUPSTAB_H

#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QDialog>
#include <QSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QStatusBar>
#include "groupstablemodel.h"

// ===== ДИАЛОГ ДЛЯ ДОБАВЛЕНИЯ ГРУППЫ (БЕЗ СТУДЕНТОВ) =====
class AddGroupDialog : public QDialog
{
    Q_OBJECT
public:
    AddGroupDialog(QWidget* parent = nullptr);
    QString getGroupName() const;
    int getCourse() const;
    int getYear() const;

private:
    QLineEdit* m_nameEdit;
    QSpinBox* m_courseSpin;
    QSpinBox* m_yearSpin;
};

// ===== ДИАЛОГ ДЛЯ РЕДАКТИРОВАНИЯ ГРУППЫ (БЕЗ СТУДЕНТОВ) =====
class EditGroupDialog : public QDialog
{
    Q_OBJECT
public:
    EditGroupDialog(const QString& currentName, int currentCourse, int currentYear, QWidget* parent = nullptr);
    QString getNewName() const;
    int getNewCourse() const;
    int getNewYear() const;

private:
    QLineEdit* m_nameEdit;
    QSpinBox* m_courseSpin;
    QSpinBox* m_yearSpin;
};

// ===== ОСНОВНОЙ КЛАСС =====
class GroupsTab : public QWidget
{
    Q_OBJECT
public:
    explicit GroupsTab(QWidget* parent = nullptr);

public slots:
    void refresh();
    void addGroup();
    void deleteGroup();
    void editGroup();
    void filterGroups(const QString& text);
    void clearFilter();
    void onGroupSelected(int index);

private:
    QTableView* m_tableView;
    GroupsTableModel* m_model;
    QComboBox* m_groupCombo;
    QLineEdit* m_filterEdit;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
    QPushButton* m_editButton;
    QPushButton* m_clearFilterButton;
    QStatusBar* m_statusBar;

    int m_selectedGroupId;
    QString m_selectedGroupName;
    int m_selectedGroupCourse;
    int m_selectedGroupYear;
};

#endif // GROUPSTAB_H