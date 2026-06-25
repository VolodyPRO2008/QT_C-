#include "studentviewtab.h"
#include "databasemanager.h"
#include "models.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

StudentViewTab::StudentViewTab(int studentId, QWidget* parent)
    : QWidget(parent), m_studentId(studentId)
{
    setupUI();
    refresh();
}

void StudentViewTab::setupUI()
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
            font-size: 14px;
        }
        QLabel#title {
            font-size: 20px;
            font-weight: bold;
            color: #3498db;
            padding: 10px;
        }
        QLabel#percentLabel {
            font-size: 24px;
            font-weight: bold;
            padding: 5px;
        }
        QProgressBar {
            background: #2c3e50;
            border: 2px solid #34495e;
            border-radius: 8px;
            text-align: center;
            color: #ecf0f1;
            font-weight: bold;
            min-height: 25px;
        }
        QProgressBar::chunk {
            border-radius: 6px;
        }
    )");

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);

    // Заголовок
    auto* titleLabel = new QLabel("📊 Моя посещаемость");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // ===== СТАТИСТИКА =====
    auto* statsGroup = new QGroupBox("📈 Статистика посещаемости");
    auto* statsLayout = new QVBoxLayout(statsGroup);
    statsLayout->setSpacing(10);

    // Процент
    auto* percentLayout = new QHBoxLayout();
    percentLayout->addStretch();
    m_percentLabel = new QLabel("0%");
    m_percentLabel->setObjectName("percentLabel");
    percentLayout->addWidget(m_percentLabel);
    percentLayout->addStretch();
    statsLayout->addLayout(percentLayout);

    // Прогресс-бар
    m_progressBar = new QProgressBar;
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(0);
    statsLayout->addWidget(m_progressBar);

    // Текст с количеством
    m_infoLabel = new QLabel("Посещено: 0 из 0 занятий (0%)");
    m_infoLabel->setObjectName("infoLabel");
    m_infoLabel->setAlignment(Qt::AlignCenter);
    m_infoLabel->setStyleSheet("color: #bdc3c7; font-size: 13px;");
    statsLayout->addWidget(m_infoLabel);

    mainLayout->addWidget(statsGroup);

    // ===== ТАБЛИЦА ПОСЕЩАЕМОСТИ =====
    auto* attendanceGroup = new QGroupBox("📋 Детали посещаемости");
    auto* attendanceLayout = new QVBoxLayout(attendanceGroup);
    m_attendanceView = new QTableView;
    m_attendanceModel = new AttendanceViewModel(this);
    m_attendanceView->setModel(m_attendanceModel);
    m_attendanceView->horizontalHeader()->setStretchLastSection(true);
    m_attendanceView->setAlternatingRowColors(true);
    attendanceLayout->addWidget(m_attendanceView);
    mainLayout->addWidget(attendanceGroup);
}

void StudentViewTab::refresh()
{
    loadAttendance();
    updateStats();
}

void StudentViewTab::loadAttendance()
{
    auto attendance = DatabaseManager::instance().getAttendanceForStudent(m_studentId);
    if (m_attendanceModel) {
        m_attendanceModel->setAttendanceData(attendance);
    }
}

void StudentViewTab::updateStats()
{
    auto records = DatabaseManager::instance().getAttendanceForStudent(m_studentId);

    int total = records.size();
    int present = 0;

    for (const auto& record : records) {
        if (record.size() >= 3 && record[2] == "Присутствовал") {
            present++;
        }
    }

    int percent = 0;
    if (total > 0) {
        percent = static_cast<int>(static_cast<double>(present) / total * 100);
    }

    m_percentLabel->setText(QString::number(percent) + "%");
    m_progressBar->setValue(percent);

    // Обновляем цвет процента в зависимости от значения
    if (percent >= 80) {
        m_percentLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2ecc71; padding: 5px;");
        m_progressBar->setStyleSheet("QProgressBar::chunk { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #2ecc71, stop:1 #27ae60); border-radius: 6px; }");
    } else if (percent >= 50) {
        m_percentLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #f39c12; padding: 5px;");
        m_progressBar->setStyleSheet("QProgressBar::chunk { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f39c12, stop:1 #d68910); border-radius: 6px; }");
    } else {
        m_percentLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #e74c3c; padding: 5px;");
        m_progressBar->setStyleSheet("QProgressBar::chunk { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #e74c3c, stop:1 #c0392b); border-radius: 6px; }");
    }

    m_infoLabel->setText(QString("Посещено: %1 из %2 занятий (%3%)")
                             .arg(present).arg(total).arg(percent));
}