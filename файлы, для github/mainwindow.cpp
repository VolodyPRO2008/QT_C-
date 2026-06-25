#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

MainWindow::MainWindow(const UserInfo& user, QWidget* parent)
    : QMainWindow(parent), m_currentUser(user)
{
    QString roleName;
    switch (user.role) {
    case UserRole::Student: roleName = "Ученик"; break;
    case UserRole::Teacher: roleName = "Преподаватель"; break;
    case UserRole::Administrator: roleName = "Администратор"; break;
    }

    setWindowTitle(QString("ИСУПС - %1 (%2)").arg(user.fullName, roleName));
    resize(1100, 750);

    setStyleSheet(R"(
        QMainWindow {
            background: #1a252f;
        }
        QTabWidget::pane {
            background: #2c3e50;
            border: 1px solid #34495e;
            border-radius: 4px;
        }
        QTabBar::tab {
            background: #34495e;
            color: #bdc3c7;
            padding: 8px 16px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
            font-weight: bold;
        }
        QTabBar::tab:selected {
            background: #3498db;
            color: white;
        }
        QTabBar::tab:hover:!selected {
            background: #3d566e;
        }
        QMenuBar {
            background: #2c3e50;
            color: #ecf0f1;
        }
        QMenuBar::item:selected {
            background: #34495e;
        }
        QMenu {
            background: #2c3e50;
            color: #ecf0f1;
        }
        QMenu::item:selected {
            background: #3498db;
        }
        QToolBar {
            background: #2c3e50;
            border: none;
            spacing: 5px;
            padding: 3px 5px;
            max-height: 35px;
        }
        QStatusBar {
            background: #2c3e50;
            color: #bdc3c7;
        }
    )");

    setupUI();
    createMenuBar();
    createToolBar();
    createStatusBar();
    setupPermissions();

    statusBar()->showMessage(QString("Добро пожаловать, %1 (%2)").arg(user.fullName, roleName), 5000);
}

void MainWindow::setupUI()
{
    m_tabWidget = new QTabWidget(this);

    m_groupsTab = new GroupsTab;
    m_scheduleTab = new ScheduleTab(this, static_cast<int>(m_currentUser.role));
    m_attendanceEditTab = new AttendanceEditTab(this, static_cast<int>(m_currentUser.role));
    m_studentViewTab = new StudentViewTab(m_currentUser.id);
    m_studentScheduleTab = new StudentScheduleTab(m_currentUser.id);
    m_teacherViewTab = new TeacherViewTab(m_currentUser.id);
    m_adminPanel = new AdminPanel;

    m_tabWidget->addTab(m_groupsTab, "Группы");
    m_tabWidget->addTab(m_scheduleTab, "Расписание");
    m_tabWidget->addTab(m_attendanceEditTab, "Посещаемость");
    m_tabWidget->addTab(m_studentViewTab, "Моя посещаемость");
    m_tabWidget->addTab(m_studentScheduleTab, "Моё расписание");
    m_tabWidget->addTab(m_teacherViewTab, "Моё расписание");
    m_tabWidget->addTab(m_adminPanel, "Редактирование пользователей");

    setCentralWidget(m_tabWidget);

    // Подключаем сигналы
    connect(m_adminPanel, &AdminPanel::groupsUpdated, m_groupsTab, &GroupsTab::refresh);

    // ===== НОВЫЙ СИГНАЛ: обновляем вкладку "Моя посещаемость" после изменений =====
    connect(m_attendanceEditTab, &AttendanceEditTab::attendanceUpdated, m_studentViewTab, &StudentViewTab::refresh);
}

void MainWindow::setupPermissions()
{
    for (int i = 0; i < m_tabWidget->count(); ++i) {
        m_tabWidget->setTabVisible(i, false);
    }

    switch (m_currentUser.role) {
    case UserRole::Administrator:
        m_tabWidget->setTabVisible(0, true);  // Группы
        m_tabWidget->setTabVisible(1, true);  // Расписание
        m_tabWidget->setTabVisible(2, true);  // Посещаемость
        m_tabWidget->setTabVisible(6, true);  // Редактирование пользователей
        break;

    case UserRole::Teacher:
        m_tabWidget->setTabVisible(0, true);  // Группы
        m_tabWidget->setTabVisible(1, true);  // Расписание
        m_tabWidget->setTabVisible(2, true);  // Посещаемость
        m_tabWidget->setTabVisible(5, true);  // Моё расписание (для учителя)
        break;

    case UserRole::Student:
        m_tabWidget->setTabVisible(3, true);  // Моя посещаемость
        m_tabWidget->setTabVisible(4, true);  // Моё расписание
        break;
    }
}

void MainWindow::createMenuBar()
{
    auto* menuBar = new QMenuBar(this);

    auto* systemMenu = menuBar->addMenu("&Система");
    auto* exitAction = new QAction("Выход", this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);
    systemMenu->addAction(exitAction);

    if (m_currentUser.role == UserRole::Administrator) {
        auto* dataMenu = menuBar->addMenu("&Данные");
        auto* usersAction = new QAction("Управление пользователями", this);
        connect(usersAction, &QAction::triggered, [this]() {
            m_tabWidget->setCurrentIndex(6);
        });
        dataMenu->addAction(usersAction);
    }

    setMenuBar(menuBar);
}

void MainWindow::createToolBar()
{
    auto* toolbar = addToolBar("Главная");
    toolbar->setMovable(false);

    toolbar->addSeparator();

    QString roleDisplay;
    switch (m_currentUser.role) {
    case UserRole::Administrator: roleDisplay = "Админ"; break;
    case UserRole::Teacher: roleDisplay = "Учитель"; break;
    case UserRole::Student: roleDisplay = "Ученик"; break;
    }

    auto* userInfoLabel = new QLabel(QString("  👤 %1 (%2)  ")
                                         .arg(m_currentUser.fullName, roleDisplay));
    userInfoLabel->setStyleSheet("color: #3498db; font-weight: bold; padding: 0 15px;");
    QWidget* spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolbar->addWidget(spacer);
    toolbar->addWidget(userInfoLabel);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage("Готов к работе");
}

void MainWindow::onRefresh()
{
    int currentIndex = m_tabWidget->currentIndex();
    QWidget* widget = m_tabWidget->widget(currentIndex);

    if (auto* groups = qobject_cast<GroupsTab*>(widget)) {
        groups->refresh();
    } else if (auto* schedule = qobject_cast<ScheduleTab*>(widget)) {
        schedule->refresh();
    } else if (auto* attendance = qobject_cast<AttendanceEditTab*>(widget)) {
        attendance->refresh();
    } else if (auto* studentView = qobject_cast<StudentViewTab*>(widget)) {
        studentView->refresh();
    } else if (auto* studentSchedule = qobject_cast<StudentScheduleTab*>(widget)) {
        studentSchedule->refresh();
    } else if (auto* teacherView = qobject_cast<TeacherViewTab*>(widget)) {
        teacherView->refresh();
    } else if (auto* admin = qobject_cast<AdminPanel*>(widget)) {
        admin->refresh();
    }

    statusBar()->showMessage("Данные обновлены", 2000);
}

void MainWindow::onExit()
{
    close();
}