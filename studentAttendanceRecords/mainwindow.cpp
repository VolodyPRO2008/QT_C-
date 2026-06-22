#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(const QString& username, QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle(QString("ИСУП - Информационная система учёта посещаемости (%1)").arg(username));
    resize(1024, 700);

    setupUI();
    createMenuBar();
    createToolBar();
    createStatusBar();

    statusBar()->showMessage("Добро пожаловать, " + username, 3000);
}

void MainWindow::setupUI()
{
    m_tabWidget = new QTabWidget(this);

    m_groupsTab = new GroupsTab;
    m_studentsTab = new StudentsTab;
    m_attendanceTab = new AttendanceTab;
    m_reportTab = new ReportTab;

    m_tabWidget->addTab(m_groupsTab, "Группы");
    m_tabWidget->addTab(m_studentsTab, "Студенты");
    m_tabWidget->addTab(m_attendanceTab, "Журнал");
    m_tabWidget->addTab(m_reportTab, "Отчёты");

    setCentralWidget(m_tabWidget);
}

void MainWindow::createMenuBar()
{
    auto* menuBar = new QMenuBar(this);

    auto* systemMenu = menuBar->addMenu("&Система");
    auto* exitAction = new QAction("Выход", this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);
    systemMenu->addAction(exitAction);

    auto* dataMenu = menuBar->addMenu("&Данные");
    auto* refreshAction = new QAction("Обновить", this);
    refreshAction->setShortcut(QKeySequence("Ctrl+R"));
    connect(refreshAction, &QAction::triggered, this, &MainWindow::onRefresh);
    dataMenu->addAction(refreshAction);

    auto* addAction = new QAction("Добавить", this);
    addAction->setShortcut(QKeySequence("Ctrl+N"));
    connect(addAction, &QAction::triggered, this, &MainWindow::onAdd);
    dataMenu->addAction(addAction);

    dataMenu->addSeparator();

    auto* saveAction = new QAction("Сохранить", this);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);
    dataMenu->addAction(saveAction);

    auto* exportAction = new QAction("Экспорт", this);
    exportAction->setShortcut(QKeySequence("Ctrl+E"));
    connect(exportAction, &QAction::triggered, this, &MainWindow::onExport);
    dataMenu->addAction(exportAction);

    setMenuBar(menuBar);
}

void MainWindow::createToolBar()
{
    auto* toolbar = addToolBar("Главная");
    toolbar->setMovable(false);

    auto* refreshBtn = new QAction("Обновить", this);
    connect(refreshBtn, &QAction::triggered, this, &MainWindow::onRefresh);
    toolbar->addAction(refreshBtn);

    auto* addBtn = new QAction("Добавить", this);
    connect(addBtn, &QAction::triggered, this, &MainWindow::onAdd);
    toolbar->addAction(addBtn);

    auto* saveBtn = new QAction("Сохранить", this);
    connect(saveBtn, &QAction::triggered, this, &MainWindow::onSave);
    toolbar->addAction(saveBtn);

    auto* exportBtn = new QAction("Экспорт", this);
    connect(exportBtn, &QAction::triggered, this, &MainWindow::onExport);
    toolbar->addAction(exportBtn);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage("Готов к работе");
}

void MainWindow::onRefresh()
{
    int currentIndex = m_tabWidget->currentIndex();
    if (currentIndex == 0) m_groupsTab->refresh();
    else if (currentIndex == 1) m_studentsTab->refresh();
    else if (currentIndex == 2) m_attendanceTab->refresh();
    else if (currentIndex == 3) m_reportTab->refresh();
    statusBar()->showMessage("Данные обновлены", 2000);
}

void MainWindow::onAdd()
{
    int currentIndex = m_tabWidget->currentIndex();
    if (currentIndex == 0) m_groupsTab->addGroup();
    else if (currentIndex == 1) m_studentsTab->addStudent();
    else if (currentIndex == 2) m_attendanceTab->markAllPresent();
    statusBar()->showMessage("Добавление выполнено", 2000);
}

void MainWindow::onSave()
{
    int currentIndex = m_tabWidget->currentIndex();
    if (currentIndex == 2) m_attendanceTab->saveAttendance();
    else QMessageBox::information(this, "Сохранение", "Данные сохранены в БД");
    statusBar()->showMessage("Данные сохранены", 2000);
}

void MainWindow::onExport()
{
    int currentIndex = m_tabWidget->currentIndex();
    if (currentIndex == 3) m_reportTab->exportToCSV();
    else QMessageBox::information(this, "Экспорт", "Экспорт доступен только в разделе 'Отчёты'");
}

void MainWindow::onExit()
{
    close();
}