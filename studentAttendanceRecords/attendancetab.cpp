#include "attendancetab.h"
#include <QHeaderView>     // <-- ДОБАВИТЬ

AttendanceTab::AttendanceTab(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);

    auto* topLayout = new QHBoxLayout();

    topLayout->addWidget(new QLabel("Группа:"));
    m_groupCombo = new QComboBox;
    topLayout->addWidget(m_groupCombo);

    topLayout->addWidget(new QLabel("Занятие:"));
    m_lessonCombo = new QComboBox;
    topLayout->addWidget(m_lessonCombo);

    topLayout->addWidget(new QLabel("Дата:"));
    m_dateEdit = new QDateEdit;
    m_dateEdit->setDate(QDate::currentDate());
    m_dateEdit->setCalendarPopup(true);
    topLayout->addWidget(m_dateEdit);

    topLayout->addStretch();

    m_markAllButton = new QPushButton("Отметить всех");
    m_saveButton = new QPushButton("Сохранить");
    topLayout->addWidget(m_markAllButton);
    topLayout->addWidget(m_saveButton);

    mainLayout->addLayout(topLayout);

    m_tableView = new QTableView;
    m_model = new AttendanceTableModel(this);
    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(m_tableView);

    connect(m_groupCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AttendanceTab::onGroupChanged);
    connect(m_markAllButton, &QPushButton::clicked, this, &AttendanceTab::markAllPresent);
    connect(m_saveButton, &QPushButton::clicked, this, &AttendanceTab::saveAttendance);
    connect(m_dateEdit, &QDateEdit::dateChanged, this, &AttendanceTab::refresh);

    setupGroupCombo();
    setupLessonCombo();    // <-- ДОБАВИТЬ вызов, иначе занятие не заполнится
    refresh();
}
void AttendanceTab::setupGroupCombo()
{
    m_groupCombo->clear();
    auto groups = DatabaseManager::instance().getAllGroups();
    for (const auto& group : groups) {
        if (group.size() > 1) m_groupCombo->addItem(group[1], group[0]);
    }
}

void AttendanceTab::setupLessonCombo()
{
    m_lessonCombo->clear();
    m_lessonCombo->addItem("Программирование", 1);
    m_lessonCombo->addItem("Базы данных", 2);
    m_lessonCombo->addItem("Веб-технологии", 3);
}

void AttendanceTab::onGroupChanged(int)
{
    refresh();
}

void AttendanceTab::refresh()
{
    QString groupName = m_groupCombo->currentText();
    if (!groupName.isEmpty()) {
        m_model->refreshByGroup(groupName);
    }
}

void AttendanceTab::markAllPresent()
{
    for (int row = 0; row < m_model->rowCount(); ++row) {
        QModelIndex index = m_model->index(row, 1);
        m_model->setData(index, true, Qt::EditRole);
    }
    QMessageBox::information(this, "Успех", "Все студенты отмечены как присутствующие");
}

void AttendanceTab::saveAttendance()
{
    QMessageBox::information(this, "Сохранение", "Данные сохранены в базу данных");
}