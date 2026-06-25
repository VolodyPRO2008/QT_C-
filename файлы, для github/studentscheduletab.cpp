#include "studentscheduletab.h"
#include "databasemanager.h"
#include "models.h"
#include <QVBoxLayout>
#include <QLabel>

StudentScheduleTab::StudentScheduleTab(int studentId, QWidget* parent)
    : QWidget(parent), m_studentId(studentId)
{
    setupUI();
    refresh();
}

void StudentScheduleTab::setupUI()
{
    setStyleSheet(R"(
        QGroupBox {
            font-weight: bold;
            color: #ecf0f1;
            border: 2px solid #34495e;
            border-radius: 8px;
            margin-top: 10px;
            padding-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 10px;
            color: #3498db;
        }
        QTableView {
            background: #2c3e50;
            alternate-background-color: #34495e;
            color: #ecf0f1;
            gridline-color: #3d566e;
            border: none;
        }
        QHeaderView::section {
            background: #34495e;
            color: #3498db;
            padding: 8px;
            border: none;
        }
        QLabel {
            color: #ecf0f1;
        }
        QLabel#title {
            font-size: 20px;
            font-weight: bold;
            color: #3498db;
            padding: 10px;
        }
        QLabel#infoLabel {
            color: #bdc3c7;
            font-size: 14px;
            padding: 20px;
        }
    )");

    auto* mainLayout = new QVBoxLayout(this);

    auto* titleLabel = new QLabel("📅 Моё расписание");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    auto* scheduleGroup = new QGroupBox("📅 Расписание занятий");
    auto* scheduleLayout = new QVBoxLayout(scheduleGroup);

    m_scheduleView = new QTableView;
    m_scheduleModel = new ScheduleModel(this);
    m_scheduleView->setModel(m_scheduleModel);
    m_scheduleView->horizontalHeader()->setStretchLastSection(true);
    m_scheduleView->setAlternatingRowColors(true);
    scheduleLayout->addWidget(m_scheduleView);

    // Информационная метка, если данных нет
    m_infoLabel = new QLabel("Загрузка расписания...");
    m_infoLabel->setObjectName("infoLabel");
    m_infoLabel->setAlignment(Qt::AlignCenter);
    scheduleLayout->addWidget(m_infoLabel);

    mainLayout->addWidget(scheduleGroup);

    refresh();
}

void StudentScheduleTab::refresh()
{
    loadSchedule();
}

void StudentScheduleTab::loadSchedule()
{
    auto schedule = DatabaseManager::instance().getScheduleForStudent(m_studentId);

    if (schedule.isEmpty()) {
        m_infoLabel->setText("📭 Расписание не найдено\n\n"
                             "Для вашей группы ещё не добавлены занятия.\n"
                             "Обратитесь к администратору.");
        m_infoLabel->setVisible(true);
    } else {
        m_infoLabel->setVisible(false);
    }

    if (m_scheduleModel) {
        m_scheduleModel->setScheduleData(schedule);
    }
}