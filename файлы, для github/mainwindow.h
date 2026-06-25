#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QMessageBox>
#include "groupstab.h"
#include "attendancetab.h"
#include "databasemanager.h"
#include "studentviewtab.h"
#include "studentscheduletab.h"  // <-- ДОБАВИТЬ
#include "teacherviewtab.h"
#include "adminpanel.h"
#include "scheduletab.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const UserInfo& user, QWidget* parent = nullptr);

private slots:
    void onRefresh();
    void onExit();

private:
    QTabWidget* m_tabWidget;
    UserInfo m_currentUser;

    // Вкладки
    GroupsTab* m_groupsTab = nullptr;
    ScheduleTab* m_scheduleTab = nullptr;
    AttendanceEditTab* m_attendanceEditTab = nullptr;
    StudentViewTab* m_studentViewTab = nullptr;
    StudentScheduleTab* m_studentScheduleTab = nullptr;  // <-- ДОБАВИТЬ
    TeacherViewTab* m_teacherViewTab = nullptr;
    AdminPanel* m_adminPanel = nullptr;

    void setupUI();
    void createMenuBar();
    void createToolBar();
    void createStatusBar();
    void setupPermissions();
};

#endif // MAINWINDOW_H