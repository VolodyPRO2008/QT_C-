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
#include "studentstab.h"
#include "attendancetab.h"
#include "reporttab.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const QString& username, QWidget* parent = nullptr);

private slots:
    void onRefresh();
    void onAdd();
    void onSave();
    void onExport();
    void onExit();

private:
    QTabWidget* m_tabWidget;
    GroupsTab* m_groupsTab;
    StudentsTab* m_studentsTab;
    AttendanceTab* m_attendanceTab;
    ReportTab* m_reportTab;

    void setupUI();
    void createMenuBar();
    void createToolBar();
    void createStatusBar();
};

#endif // MAINWINDOW_H