#include "groupstab.h"
#include <QLabel>          // <-- ДОБАВИТЬ
#include <QHeaderView>     // <-- ДОБАВИТЬ

GroupsTab::GroupsTab(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);

    auto* topLayout = new QHBoxLayout();
    topLayout->addWidget(new QLabel("Название группы:"));
    m_nameEdit = new QLineEdit;
    m_nameEdit->setPlaceholderText("Введите название...");
    topLayout->addWidget(m_nameEdit);

    m_addButton = new QPushButton("Добавить");
    m_deleteButton = new QPushButton("Удалить");
    topLayout->addWidget(m_addButton);
    topLayout->addWidget(m_deleteButton);
    topLayout->addStretch();

    mainLayout->addLayout(topLayout);

    m_tableView = new QTableView;
    m_model = new GroupsTableModel(this);
    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(m_tableView);

    connect(m_addButton, &QPushButton::clicked, this, &GroupsTab::addGroup);
    connect(m_deleteButton, &QPushButton::clicked, this, &GroupsTab::deleteGroup);
    connect(m_nameEdit, &QLineEdit::returnPressed, this, &GroupsTab::addGroup);

    refresh();
}

void GroupsTab::refresh()
{
    m_model->refresh();
    m_nameEdit->clear();
    m_nameEdit->setFocus();
}

void GroupsTab::addGroup()
{
    QString name = m_nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название группы");
        return;
    }

    if (DatabaseManager::instance().addGroup(name)) {
        refresh();
        QMessageBox::information(this, "Успех", "Группа добавлена");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить группу");
    }
}

void GroupsTab::deleteGroup()
{
    QModelIndex index = m_tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите группу для удаления");
        return;
    }

    QString name = m_model->data(index).toString();

    if (QMessageBox::question(this, "Подтверждение",
                              QString("Удалить группу '%1'?").arg(name),
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        if (DatabaseManager::instance().deleteGroup(name)) {
            refresh();
            QMessageBox::information(this, "Успех", "Группа удалена");
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить группу");
        }
    }
}