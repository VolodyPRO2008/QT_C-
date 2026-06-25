#include "teacherviewtab.h"
#include "databasemanager.h"
#include "models.h"
#include <QVBoxLayout>
#include <QLabel>

TeacherViewTab::TeacherViewTab(int teacherId, QWidget* parent)
    : QWidget(parent), m_teacherId(teacherId)
{
    setupUI();
    refresh();
}

void TeacherViewTab::setupUI()
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
    )");

    auto* mainLayout = new QVBoxLayout(this);

    auto* titleLabel = new QLabel("📋 Моё расписание");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    auto* scheduleGroup = new QGroupBox("📅 Расписание занятий");
    auto* scheduleLayout = new QVBoxLayout(scheduleGroup);
    m_scheduleView = new QTableView;
    m_scheduleModel = new TeacherScheduleModel(this);
    m_scheduleView->setModel(m_scheduleModel);
    m_scheduleView->horizontalHeader()->setStretchLastSection(true);
    m_scheduleView->setAlternatingRowColors(true);
    scheduleLayout->addWidget(m_scheduleView);
    mainLayout->addWidget(scheduleGroup);

    refresh();
}

void TeacherViewTab::refresh()
{
    loadSchedule();
}

void TeacherViewTab::loadSchedule()
{
    auto schedule = DatabaseManager::instance().getScheduleForTeacher(m_teacherId);

    // Форматируем данные для отображения с парами
    QList<QStringList> formattedSchedule;
    for (const auto& item : schedule) {
        if (item.size() >= 3) {
            QStringList row;
            row << item[0]  // Дата
                << item[1]  // Дисциплина
                << item[2]  // Группа
                << item[3]  // Пара
                << item[4]; // Аудитория
            formattedSchedule.append(row);
        }
    }

    if (m_scheduleModel) {
        m_scheduleModel->setScheduleData(formattedSchedule);
    }
}