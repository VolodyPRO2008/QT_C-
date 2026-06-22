#include "reporttab.h"
#include <QLabel>
#include <QHeaderView>

ReportTab::ReportTab(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);

    auto* topLayout = new QHBoxLayout();

    topLayout->addWidget(new QLabel("Группа:"));
    m_groupCombo = new QComboBox;
    topLayout->addWidget(m_groupCombo);

    topLayout->addWidget(new QLabel("С:"));
    m_startDateEdit = new QDateEdit;
    m_startDateEdit->setDate(QDate(2026, 2, 1));
    m_startDateEdit->setCalendarPopup(true);
    topLayout->addWidget(m_startDateEdit);

    topLayout->addWidget(new QLabel("По:"));
    m_endDateEdit = new QDateEdit;
    m_endDateEdit->setDate(QDate(2026, 3, 1));
    m_endDateEdit->setCalendarPopup(true);
    topLayout->addWidget(m_endDateEdit);

    m_refreshButton = new QPushButton("Обновить");
    m_exportButton = new QPushButton("Экспорт в CSV");
    topLayout->addWidget(m_refreshButton);
    topLayout->addWidget(m_exportButton);
    topLayout->addStretch();

    mainLayout->addLayout(topLayout);

    m_tableView = new QTableView;
    m_model = new ReportTableModel(this);
    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(m_tableView);

    connect(m_refreshButton, &QPushButton::clicked, this, &ReportTab::refresh);
    connect(m_exportButton, &QPushButton::clicked, this, &ReportTab::exportToCSV);

    auto groups = DatabaseManager::instance().getAllGroups();
    for (const auto& group : groups) {
        if (group.size() > 1) m_groupCombo->addItem(group[1], group[0]);
    }

    refresh();
}

void ReportTab::refresh()
{
    QString groupName = m_groupCombo->currentText();
    QString startDate = m_startDateEdit->date().toString("yyyy-MM-dd");
    QString endDate = m_endDateEdit->date().toString("yyyy-MM-dd");

    if (!groupName.isEmpty()) {
        m_model->refresh(groupName, startDate, endDate);
    }
}

void ReportTab::exportToCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить отчёт", "report.csv", "CSV файлы (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл");
        return;
    }

    QTextStream stream(&file);


#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    stream.setEncoding(QStringConverter::Utf8);   // Qt 6
#else
    stream.setCodec("UTF-8");                     // Qt 5
#endif

    stream << "ID;ФИО;Всего занятий;Посещений;Опозданий\n";

    for (int row = 0; row < m_model->rowCount(); ++row) {
        for (int col = 0; col < m_model->columnCount(); ++col) {
            QModelIndex index = m_model->index(row, col);
            stream << m_model->data(index).toString();
            if (col < m_model->columnCount() - 1) stream << ";";
        }
        stream << "\n";
    }

    file.close();
    QMessageBox::information(this, "Успех", "Отчёт экспортирован в " + fileName);
}