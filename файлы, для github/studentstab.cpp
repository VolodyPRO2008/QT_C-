#include "studentstab.h"
#include "databasemanager.h"
#include <QLabel>
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

    // Заполнение комбобокса группами
    auto groups = DatabaseManager::instance().getAllGroups();
    for (const auto& group : groups) {
        if (group.size() > 1) {
            m_groupCombo->addItem(group[1], group[0]);
        }
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
        // ===== ОБНОВЛЯЕМ ВСЕ ВКЛАДКИ С ГРУППАМИ =====
        emit groupsUpdated();  // Сигнал для обновления GroupsTab
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить студента");
    }
}


void StudentsTab::onGroupChanged(int)
{
    refresh();
}

void StudentsTab::deleteStudent()
{
    QModelIndex index = m_tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите студента для удаления");
        return;
    }

    int studentId = m_model->getStudentId(index.row());
    QString studentName = m_model->data(m_model->index(index.row(), 1)).toString();

    if (studentId == -1) {
        QMessageBox::warning(this, "Ошибка", "Не удалось определить ID студента");
        return;
    }

    QMessageBox confirmDialog;
    confirmDialog.setWindowTitle("Подтверждение удаления");
    confirmDialog.setIcon(QMessageBox::Warning);
    confirmDialog.setText(QString("Вы действительно хотите удалить студента <b>'%1'</b>?").arg(studentName));
    confirmDialog.setInformativeText("Это действие нельзя будет отменить!");
    confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmDialog.setDefaultButton(QMessageBox::No);
    confirmDialog.setButtonText(QMessageBox::Yes, "✅ Да, удалить");
    confirmDialog.setButtonText(QMessageBox::No, "❌ Нет, отмена");

    confirmDialog.setStyleSheet(R"(
        QMessageBox {
            background: #2c3e50;
        }
        QLabel {
            color: #ecf0f1;
            font-size: 14px;
        }
        QPushButton {
            padding: 8px 20px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            color: white;
            font-size: 14px;
            min-height: 35px;
            min-width: 100px;
        }
        QPushButton[text="✅ Да, удалить"] {
            background: #e74c3c;
        }
        QPushButton[text="✅ Да, удалить"]:hover {
            background: #c0392b;
        }
        QPushButton[text="❌ Нет, отмена"] {
            background: #95a5a6;
        }
        QPushButton[text="❌ Нет, отмена"]:hover {
            background: #7f8c8d;
        }
    )");

    if (confirmDialog.exec() == QMessageBox::Yes) {
        if (DatabaseManager::instance().deleteStudent(studentId)) {
            refresh();
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage(QString("🗑️ Студент '%1' успешно удалён").arg(studentName), 3000);
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить студента");
        }
    }
}
