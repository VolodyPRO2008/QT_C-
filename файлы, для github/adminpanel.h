#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>
#include <QStatusBar>
#include <QInputDialog>
#include <QDialog>
#include <QDialogButtonBox>
#include <QStackedWidget>
#include <QFormLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

class UsersTableModel;

// ===== ДИАЛОГ ДЛЯ СМЕНЫ РОЛИ =====
class ChangeRoleDialog : public QDialog
{
    Q_OBJECT
public:
    ChangeRoleDialog(const QString& fullName, int currentRole, QWidget* parent = nullptr);
    int getNewRole() const;

private:
    QComboBox* m_roleCombo;
};

// ===== ДИАЛОГ ДЛЯ РЕДАКТИРОВАНИЯ ПОЛЬЗОВАТЕЛЯ (ФИО + ГРУППА) =====
class EditUserDialog : public QDialog
{
    Q_OBJECT
public:
    EditUserDialog(const QString& currentName, int currentRole, const QString& currentGroup, QWidget* parent = nullptr);
    QString getNewName() const;
    int getNewGroupId() const;
    bool isStudent() const;

private:
    QLineEdit* m_nameEdit;
    QComboBox* m_groupCombo;
    QLabel* m_groupLabel;
    QWidget* m_groupWidget;
    int m_currentRole;
};

// ===== ДИАЛОГ ДЛЯ ДОБАВЛЕНИЯ ПОЛЬЗОВАТЕЛЯ =====
class AddUserDialog : public QDialog
{
    Q_OBJECT
public:
    AddUserDialog(QWidget* parent = nullptr);
    QString getFullName() const;
    int getRole() const;
    int getGroupId() const;
    bool isStudent() const;

private slots:
    void onRoleChanged(int index);

private:
    QLineEdit* m_nameEdit;
    QComboBox* m_roleCombo;
    QComboBox* m_groupCombo;
    QLabel* m_groupLabel;
    QWidget* m_groupWidget;
};

// ===== ОСНОВНОЙ КЛАСС =====
class AdminPanel : public QWidget
{
    Q_OBJECT
public:
    explicit AdminPanel(QWidget* parent = nullptr);

signals:
    void groupsUpdated();

public slots:
    void refresh();
    void addUser();
    void deleteUser();
    void changeRole();
    void editUser();
    void onUserSelected(int index);
    void exportUsersToCSV();  // <-- ДОБАВИТЬ ЭТУ СТРОКУ

private:
    QTableView* m_usersTable;
    UsersTableModel* m_usersModel;

    QComboBox* m_userCombo;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
    QPushButton* m_changeRoleButton;
    QPushButton* m_editUserButton;
    QPushButton* m_exportButton;  // <-- ДОБАВИТЬ КНОПКУ

    QStatusBar* m_statusBar;
    int m_selectedUserId;
    QString m_selectedUserName;
    int m_selectedUserRole;
    QString m_selectedUserGroup;
};

#endif // ADMINPANEL_H