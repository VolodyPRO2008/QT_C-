#include "studentstab.h"
#include "qlabel.h"
#include <QHeaderView>

StudentsTab::StudentsTab(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);

    auto* topLayout = new QHBoxLayout();
    topLayout->addWidget(new QLabel("Группа:"));
    m_groupCombo = new QComboBox;
    topLayout->addWidget(m_groupCombo);

    topLayout->addWidget(new QLabel("ФИО:"));
    m_nameEdit = new QLineEdit;
    m_nameEdit->setPlaceholderText("Введите ФИО...");
    topLayout->addWidget(m_nameEdit);

    topLayout->addWidget(new QLabel("Зачётная книжка:"));
    m_cardEdit = new QLineEdit;
    m_cardEdit->setPlaceholderText("Введите номер...");
    topLayout->addWidget(m_cardEdit);

    m_addButton = new QPushButton("Добавить");
    m_deleteButton = new QPushButton("Удалить");
    topLayout->addWidget(m_addButton);
    topLayout->addWidget(m_deleteButton);
    topLayout->addStretch();

    mainLayout->addLayout(topLayout);

    m_tableView = new QTableView;
    m_model = new StudentsTableModel(this);
    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(m_tableView);

    connect(m_addButton, &QPushButton::clicked, this, &StudentsTab::addStudent);
    connect(m_deleteButton, &QPushButton::clicked, this, &StudentsTab::deleteStudent);
    connect(m_groupCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &StudentsTab::onGroupChanged);
    connect(m_nameEdit, &QLineEdit::returnPressed, this, &StudentsTab::addStudent);

    auto groups = DatabaseManager::instance().getAllGroups();
    for (const auto& group : groups) {
        if (group.size() > 1) m_groupCombo->addItem(group[1], group[0]);
    }

    refresh();
}

void StudentsTab::refresh()
{
    QString groupName = m_groupCombo->currentText();
    if (m_groupCombo->count() > 0 && !groupName.isEmpty()) {
        m_model->refreshByGroup(groupName);
    } else {
        m_model->refresh();
    }
    m_nameEdit->clear();
    m_cardEdit->clear();
}

void StudentsTab::addStudent()
{
    QString name = m_nameEdit->text().trimmed();
    QString card = m_cardEdit->text().trimmed();

    if (name.isEmpty() || card.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля");
        return;
    }

    if (DatabaseManager::instance().addStudent(name, m_groupCombo->currentText())) {
        refresh();
        QMessageBox::information(this, "Успех", "Студент добавлен");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить студента");
    }
}

void StudentsTab::deleteStudent()
{
    QMessageBox::information(this, "Удаление", "Функция удаления студента будет реализована в следующей версии");
}

void StudentsTab::onGroupChanged(int)
{
    refresh();
}