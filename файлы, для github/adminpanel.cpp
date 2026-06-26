#include "adminpanel.h"
#include "databasemanager.h"
#include "models.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>


// ДИАЛОГ ДЛЯ СМЕНЫ РОЛИ

ChangeRoleDialog::ChangeRoleDialog(const QString& fullName, int currentRole, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Смена роли");
    setFixedSize(400, 300);

    setStyleSheet(R"(
        QDialog {
            background: #2c3e50;
        }
        QLabel {
            color: #ecf0f1;
            font-size: 14px;
        }
        QLabel#title {
            font-size: 18px;
            font-weight: bold;
            color: #3498db;
        }
        QLabel#infoLabel {
            color: #bdc3c7;
            font-size: 13px;
        }
        QComboBox {
            padding: 10px 14px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 35px;
            font-size: 15px;
        }
        QComboBox:focus {
            border: 2px solid #3498db;
        }
        QPushButton {
            padding: 10px 25px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            color: white;
            font-size: 15px;
            min-height: 40px;
        }
        QPushButton#okBtn {
            background: #3498db;
        }
        QPushButton#okBtn:hover {
            background: #2980b9;
        }
        QPushButton#cancelBtn {
            background: #e74c3c;
        }
        QPushButton#cancelBtn:hover {
            background: #c0392b;
        }
        QFrame#line {
            background: #34495e;
            max-height: 1px;
            margin: 8px 0;
        }
        QLabel#nameValue {
            color: #3498db;
            font-weight: bold;
            font-size: 15px;
        }
        QLabel#roleValue {
            color: #f39c12;
            font-weight: bold;
            font-size: 15px;
        }
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(18);
    layout->setContentsMargins(35, 30, 35, 30);

    auto* titleLabel = new QLabel("🔄 Смена роли");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* line = new QFrame;
    line->setObjectName("line");
    layout->addWidget(line);

    auto* nameLayout = new QHBoxLayout();
    auto* nameLabel = new QLabel("Пользователь:");
    nameLabel->setObjectName("infoLabel");
    nameLayout->addWidget(nameLabel);
    auto* nameValue = new QLabel(fullName);
    nameValue->setObjectName("nameValue");
    nameLayout->addWidget(nameValue);
    nameLayout->addStretch();
    layout->addLayout(nameLayout);

    auto* currentRoleLayout = new QHBoxLayout();
    auto* currentRoleLabel = new QLabel("Текущая роль:");
    currentRoleLabel->setObjectName("infoLabel");
    currentRoleLayout->addWidget(currentRoleLabel);
    QString roleName = currentRole == 0 ? "Ученик" : currentRole == 1 ? "Преподаватель" : "Администратор";
    auto* currentRoleValue = new QLabel(roleName);
    currentRoleValue->setObjectName("roleValue");
    currentRoleLayout->addWidget(currentRoleValue);
    currentRoleLayout->addStretch();
    layout->addLayout(currentRoleLayout);

    auto* newRoleLayout = new QHBoxLayout();
    auto* newRoleLabel = new QLabel("Новая роль:");
    newRoleLabel->setObjectName("infoLabel");
    newRoleLayout->addWidget(newRoleLabel);
    m_roleCombo = new QComboBox;
    m_roleCombo->addItem("Ученик", 0);
    m_roleCombo->addItem("Преподаватель", 1);
    m_roleCombo->addItem("Администратор", 2);
    m_roleCombo->setCurrentIndex(currentRole);
    m_roleCombo->setMinimumWidth(150);
    newRoleLayout->addWidget(m_roleCombo);
    newRoleLayout->addStretch();
    layout->addLayout(newRoleLayout);

    layout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    auto* okButton = new QPushButton("✅ Сохранить");
    okButton->setObjectName("okBtn");
    auto* cancelButton = new QPushButton("❌ Отмена");
    cancelButton->setObjectName("cancelBtn");

    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

int ChangeRoleDialog::getNewRole() const
{
    return m_roleCombo->currentData().toInt();
}


// ДИАЛОГ ДЛЯ РЕДАКТИРОВАНИЯ ПОЛЬЗОВАТЕЛЯ (ФИО + ГРУППА)

EditUserDialog::EditUserDialog(const QString& currentName, int currentRole, const QString& currentGroup, QWidget* parent)
    : QDialog(parent), m_currentRole(currentRole)
{
    setWindowTitle("Редактирование пользователя");
    setFixedSize(600, 500);

    setStyleSheet(R"(
        QDialog {
            background: #2c3e50;
        }
        QLabel {
            color: #ecf0f1;
            font-size: 14px;
        }
        QLabel#title {
            font-size: 18px;
            font-weight: bold;
            color: #3498db;
        }
        QLabel#infoLabel {
            color: #bdc3c7;
            font-size: 13px;
        }
        QLabel#currentName {
            color: #f39c12;
            font-weight: bold;
            font-size: 15px;
        }
        QLineEdit {
            padding: 10px 14px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 35px;
            font-size: 15px;
        }
        QLineEdit:focus {
            border: 2px solid #3498db;
        }
        QComboBox {
            padding: 10px 14px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 35px;
            font-size: 15px;
        }
        QComboBox:focus {
            border: 2px solid #3498db;
        }
        QPushButton {
            padding: 10px 25px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            color: white;
            font-size: 15px;
            min-height: 40px;
        }
        QPushButton#okBtn {
            background: #3498db;
        }
        QPushButton#okBtn:hover {
            background: #2980b9;
        }
        QPushButton#cancelBtn {
            background: #e74c3c;
        }
        QPushButton#cancelBtn:hover {
            background: #c0392b;
        }
        QFrame#line {
            background: #34495e;
            max-height: 1px;
            margin: 8px 0;
        }
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
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(18);
    layout->setContentsMargins(35, 30, 35, 30);

    auto* titleLabel = new QLabel("✏️ Редактирование пользователя");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* line = new QFrame;
    line->setObjectName("line");
    layout->addWidget(line);

    // ===== ТЕКУЩИЕ ДАННЫЕ =====
    auto* infoGroup = new QGroupBox("📋 Текущие данные");
    auto* infoLayout = new QFormLayout(infoGroup);
    infoLayout->setSpacing(10);
    infoLayout->setLabelAlignment(Qt::AlignRight);

    auto* nameLabel = new QLabel(currentName);
    nameLabel->setObjectName("currentName");
    infoLayout->addRow("ФИО:", nameLabel);

    QString roleName = currentRole == 0 ? "Ученик" : currentRole == 1 ? "Преподаватель" : "Администратор";
    auto* roleLabel = new QLabel(roleName);
    roleLabel->setObjectName("currentName");
    infoLayout->addRow("Роль:", roleLabel);

    if (currentRole == 0) {
        auto* groupLabel = new QLabel(currentGroup.isEmpty() ? "Не назначена" : currentGroup);
        groupLabel->setObjectName("currentName");
        infoLayout->addRow("Группа:", groupLabel);
    }

    layout->addWidget(infoGroup);

    // ===== НОВЫЕ ДАННЫЕ =====
    auto* formGroup = new QGroupBox("✏️ Новые данные");
    auto* formLayout = new QFormLayout(formGroup);
    formLayout->setSpacing(10);
    formLayout->setLabelAlignment(Qt::AlignRight);

    // ФИО
    m_nameEdit = new QLineEdit;
    m_nameEdit->setText(currentName);
    m_nameEdit->selectAll();
    formLayout->addRow("Новое ФИО:", m_nameEdit);

    // Группа (только для учеников)
    if (currentRole == 0) {
        m_groupLabel = new QLabel("Новая группа:");
        m_groupCombo = new QComboBox;

        auto groups = DatabaseManager::instance().getAllGroups();
        m_groupCombo->addItem("-- Без группы --", -1);
        for (const auto& group : groups) {
            if (group.size() >= 2) {
                m_groupCombo->addItem(group[1], group[0].toInt());
            }
        }

        if (!currentGroup.isEmpty()) {
            for (int i = 0; i < m_groupCombo->count(); ++i) {
                if (m_groupCombo->itemText(i) == currentGroup) {
                    m_groupCombo->setCurrentIndex(i);
                    break;
                }
            }
        }

        m_groupWidget = new QWidget;
        auto* groupLayout = new QHBoxLayout(m_groupWidget);
        groupLayout->setContentsMargins(0, 0, 250, 0);
        groupLayout->setSpacing(10);
        groupLayout->addWidget(m_groupLabel);
        groupLayout->addWidget(m_groupCombo);
        formLayout->addRow(m_groupWidget);
    } else {
        m_groupWidget = nullptr;
        m_groupCombo = nullptr;
    }

    layout->addWidget(formGroup);
    layout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    auto* okButton = new QPushButton("✅ Сохранить");
    okButton->setObjectName("okBtn");
    auto* cancelButton = new QPushButton("❌ Отмена");
    cancelButton->setObjectName("cancelBtn");

    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_nameEdit, &QLineEdit::returnPressed, this, &QDialog::accept);
}

QString EditUserDialog::getNewName() const
{
    return m_nameEdit->text().trimmed();
}

int EditUserDialog::getNewGroupId() const
{
    if (m_groupCombo && m_currentRole == 0) {
        return m_groupCombo->currentData().toInt();
    }
    return -1;
}

bool EditUserDialog::isStudent() const
{
    return m_currentRole == 0;
}


// ДИАЛОГ ДЛЯ ДОБАВЛЕНИЯ ПОЛЬЗОВАТЕЛЯ

AddUserDialog::AddUserDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Добавление пользователя");
    setFixedSize(500, 450);

    setStyleSheet(R"(
        QDialog {
            background: #2c3e50;
        }
        QLabel {
            color: #ecf0f1;
            font-size: 14px;
        }
        QLabel#title {
            font-size: 18px;
            font-weight: bold;
            color: #3498db;
        }
        QLabel#infoLabel {
            color: #bdc3c7;
            font-size: 13px;
        }
        QLineEdit {
            padding: 10px 14px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 35px;
            font-size: 15px;
        }
        QLineEdit:focus {
            border: 2px solid #3498db;
        }
        QComboBox {
            padding: 10px 14px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 35px;
            font-size: 15px;
        }
        QComboBox:focus {
            border: 2px solid #3498db;
        }
        QPushButton {
            padding: 10px 25px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            color: white;
            font-size: 15px;
            min-height: 40px;
        }
        QPushButton#okBtn {
            background: #2ecc71;
        }
        QPushButton#okBtn:hover {
            background: #27ae60;
        }
        QPushButton#cancelBtn {
            background: #e74c3c;
        }
        QPushButton#cancelBtn:hover {
            background: #c0392b;
        }
        QFrame#line {
            background: #34495e;
            max-height: 1px;
            margin: 8px 0;
        }
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
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(18);
    layout->setContentsMargins(35, 30, 35, 30);

    auto* titleLabel = new QLabel("➕ Добавление пользователя");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* line = new QFrame;
    line->setObjectName("line");
    layout->addWidget(line);

    auto* formGroup = new QGroupBox("📝 Данные пользователя");
    auto* formLayout = new QFormLayout(formGroup);
    formLayout->setSpacing(12);
    formLayout->setLabelAlignment(Qt::AlignRight);

    // ФИО
    m_nameEdit = new QLineEdit;
    m_nameEdit->setPlaceholderText("Введите ФИО пользователя...");
    formLayout->addRow("ФИО:", m_nameEdit);

    // Роль
    m_roleCombo = new QComboBox;
    m_roleCombo->addItem("Ученик", 0);
    m_roleCombo->addItem("Преподаватель", 1);
    m_roleCombo->addItem("Администратор", 2);
    formLayout->addRow("Роль:", m_roleCombo);

    // Группа (показывается только для ученика)
    m_groupLabel = new QLabel("Группа:");
    m_groupLabel->setObjectName("infoLabel");
    m_groupCombo = new QComboBox;

    auto groups = DatabaseManager::instance().getAllGroups();
    m_groupCombo->addItem("-- Выберите группу --", -1);
    for (const auto& group : groups) {
        if (group.size() >= 2) {
            m_groupCombo->addItem(group[1], group[0].toInt());
        }
    }

    m_groupWidget = new QWidget;
    auto* groupLayout = new QHBoxLayout(m_groupWidget);
    groupLayout->setContentsMargins(0, 0, 170, 0);
    groupLayout->setSpacing(10);
    groupLayout->addWidget(m_groupLabel);
    groupLayout->addWidget(m_groupCombo);
    formLayout->addRow(m_groupWidget);

    m_groupWidget->setVisible(true);

    layout->addWidget(formGroup);
    layout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    auto* okButton = new QPushButton("✅ Добавить");
    okButton->setObjectName("okBtn");
    auto* cancelButton = new QPushButton("❌ Отмена");
    cancelButton->setObjectName("cancelBtn");

    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_nameEdit, &QLineEdit::returnPressed, this, &QDialog::accept);
    connect(m_roleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AddUserDialog::onRoleChanged);
}

void AddUserDialog::onRoleChanged(int index)
{
    Q_UNUSED(index);
    int role = m_roleCombo->currentData().toInt();
    m_groupWidget->setVisible(role == 0);

    if (role != 0) {
        m_groupCombo->setCurrentIndex(0);
    }
}

QString AddUserDialog::getFullName() const
{
    return m_nameEdit->text().trimmed();
}

int AddUserDialog::getRole() const
{
    return m_roleCombo->currentData().toInt();
}

int AddUserDialog::getGroupId() const
{
    return m_groupCombo->currentData().toInt();
}

bool AddUserDialog::isStudent() const
{
    return getRole() == 0;
}


// ADMINPANEL 

AdminPanel::AdminPanel(QWidget* parent)
    : QWidget(parent), m_selectedUserId(-1), m_selectedUserRole(0)
{
    setStyleSheet(R"(
        QGroupBox {
            font-weight: bold;
            color: #ecf0f1;
            border: 2px solid #34495e;
            border-radius: 8px;
            margin-top: 8px;
            padding-top: 8px;
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
            padding: 6px;
            border: none;
        }
        QComboBox {
            padding: 6px 10px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 25px;
            font-size: 13px;
        }
        QComboBox:focus {
            border: 2px solid #3498db;
        }
        QPushButton {
            padding: 6px 16px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            color: white;
            font-size: 13px;
            min-height: 30px;
            min-width: 80px;
        }
        QPushButton#addBtn {
            background: #2ecc71;
        }
        QPushButton#addBtn:hover {
            background: #27ae60;
        }
        QPushButton#deleteBtn {
            background: #e74c3c;
        }
        QPushButton#deleteBtn:hover {
            background: #c0392b;
        }
        QPushButton#roleBtn {
            background: #f39c12;
        }
        QPushButton#roleBtn:hover {
            background: #d68910;
        }
        QPushButton#editBtn {
            background: #3498db;
        }
        QPushButton#editBtn:hover {
            background: #2980b9;
        }
        QPushButton#exportBtn {
            background: #2ecc71;
        }
        QPushButton#exportBtn:hover {
            background: #27ae60;
        }
        QLabel {
            color: #ecf0f1;
            font-size: 13px;
        }
        QStatusBar {
            background: #2c3e50;
            color: #2ecc71;
            font-size: 13px;
            padding: 3px 8px;
            border-radius: 4px;
            margin-top: 8px;
        }
        QStatusBar#error {
            color: #e74c3c;
        }
    )");

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    auto* titleLabel = new QLabel("👤 Редактирование пользователей");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #3498db; padding: 5px 0 8px 0;");
    mainLayout->addWidget(titleLabel);

    // ===== ВЫБОР ПОЛЬЗОВАТЕЛЯ =====
    auto* selectGroup = new QGroupBox("👤 Выбор пользователя");
    auto* selectLayout = new QHBoxLayout(selectGroup);
    selectLayout->setContentsMargins(10, 8, 10, 8);

    selectLayout->addWidget(new QLabel("Пользователь:"));
    m_userCombo = new QComboBox;
    m_userCombo->setMinimumWidth(250);
    selectLayout->addWidget(m_userCombo);
    selectLayout->addStretch();

    mainLayout->addWidget(selectGroup);

    // ===== УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЕМ =====
    auto* controlGroup = new QGroupBox("✏️ Управление пользователем");
    auto* controlLayout = new QHBoxLayout(controlGroup);
    controlLayout->setContentsMargins(10, 8, 10, 8);
    controlLayout->setSpacing(8);

    m_addButton = new QPushButton("➕ Добавить");
    m_addButton->setObjectName("addBtn");
    m_deleteButton = new QPushButton("🗑 Удалить");
    m_deleteButton->setObjectName("deleteBtn");
    m_changeRoleButton = new QPushButton("🔄 Сменить роль");
    m_changeRoleButton->setObjectName("roleBtn");
    m_editUserButton = new QPushButton("✏️ Редактировать");
    m_editUserButton->setObjectName("editBtn");
    m_exportButton = new QPushButton("📥 Экспорт CSV");
    m_exportButton->setObjectName("exportBtn");

    controlLayout->addWidget(m_addButton);
    controlLayout->addWidget(m_deleteButton);
    controlLayout->addWidget(m_changeRoleButton);
    controlLayout->addWidget(m_editUserButton);
    controlLayout->addWidget(m_exportButton);
    controlLayout->addStretch();

    mainLayout->addWidget(controlGroup);

    // ===== ТАБЛИЦА ПОЛЬЗОВАТЕЛЕЙ =====
    auto* tableGroup = new QGroupBox("📋 Список пользователей");
    auto* tableLayout = new QVBoxLayout(tableGroup);
    tableLayout->setContentsMargins(10, 8, 10, 8);
    m_usersTable = new QTableView;
    m_usersModel = new UsersTableModel(this);
    m_usersTable->setModel(m_usersModel);
    m_usersTable->horizontalHeader()->setStretchLastSection(true);
    m_usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    tableLayout->addWidget(m_usersTable);
    mainLayout->addWidget(tableGroup);

    // ===== СТАТУС БАР =====
    m_statusBar = new QStatusBar;
    m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
    m_statusBar->showMessage("Готов к работе");
    mainLayout->addWidget(m_statusBar);

    // ===== СИГНАЛЫ =====
    connect(m_addButton, &QPushButton::clicked, this, &AdminPanel::addUser);
    connect(m_deleteButton, &QPushButton::clicked, this, &AdminPanel::deleteUser);
    connect(m_changeRoleButton, &QPushButton::clicked, this, &AdminPanel::changeRole);
    connect(m_editUserButton, &QPushButton::clicked, this, &AdminPanel::editUser);
    connect(m_exportButton, &QPushButton::clicked, this, &AdminPanel::exportUsersToCSV);
    connect(m_userCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AdminPanel::onUserSelected);
    connect(m_usersTable->selectionModel(), &QItemSelectionModel::currentChanged,
            [this](const QModelIndex& current, const QModelIndex&) {
                if (current.isValid()) {
                    int userId = m_usersModel->data(m_usersModel->index(current.row(), 0)).toInt();
                    for (int i = 0; i < m_userCombo->count(); ++i) {
                        if (m_userCombo->itemData(i).toInt() == userId) {
                            m_userCombo->setCurrentIndex(i);
                            break;
                        }
                    }
                }
            });

    refresh();
}

// ============================================================
// REFRESH
// ============================================================
void AdminPanel::refresh()
{
    auto users = DatabaseManager::instance().getAllUsers();
    if (auto* model = qobject_cast<UsersTableModel*>(m_usersModel)) {
        model->setTableData(users);
    }

    m_userCombo->clear();
    m_userCombo->addItem("-- Выберите пользователя --", -1);

    for (const auto& user : users) {
        if (user.size() >= 2) {
            QString displayName = user[1];
            int userId = user[0].toInt();
            int role = user[2].toInt();
            QString roleName = role == 0 ? "Ученик" : role == 1 ? "Преподаватель" : "Администратор";
            m_userCombo->addItem(QString("%1 (%2)").arg(displayName, roleName), userId);
        }
    }

    m_statusBar->showMessage("Данные обновлены", 2000);
}

// ============================================================
// ON USER SELECTED
// ============================================================
void AdminPanel::onUserSelected(int index)
{
    if (index <= 0 || m_userCombo->currentData().toInt() == -1) {
        m_selectedUserId = -1;
        m_selectedUserName = "";
        m_selectedUserRole = 0;
        m_selectedUserGroup = "";
        return;
    }

    m_selectedUserId = m_userCombo->currentData().toInt();

    auto users = DatabaseManager::instance().getAllUsers();
    for (const auto& user : users) {
        if (user[0].toInt() == m_selectedUserId) {
            m_selectedUserName = user[1];
            m_selectedUserRole = user[2].toInt();
            if (user.size() > 3) {
                m_selectedUserGroup = user[3];
            } else {
                m_selectedUserGroup = "";
            }
            break;
        }
    }

    for (int row = 0; row < m_usersModel->rowCount(); ++row) {
        if (m_usersModel->data(m_usersModel->index(row, 0)).toInt() == m_selectedUserId) {
            m_usersTable->selectRow(row);
            break;
        }
    }
}


// ADD USER

void AdminPanel::addUser()
{
    AddUserDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString fullName = dialog.getFullName();
        int role = dialog.getRole();
        int groupId = dialog.getGroupId();

        if (fullName.isEmpty()) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 10px; border-radius: 4px;");
            m_statusBar->showMessage("⚠️ Введите ФИО пользователя", 3000);
            return;
        }

        if (role == 0 && groupId == -1) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("⚠️ Выберите группу для ученика", 3000);
            return;
        }

        if (DatabaseManager::instance().addUser(fullName, role, groupId)) {
            QString roleName = role == 0 ? "Ученик" : role == 1 ? "Преподаватель" : "Администратор";
            QString groupName = "";
            if (role == 0 && groupId != -1) {
                auto groups = DatabaseManager::instance().getAllGroups();
                for (const auto& group : groups) {
                    if (group[0].toInt() == groupId) {
                        groupName = QString(" (Группа: %1)").arg(group[1]);
                        break;
                    }
                }
            }

            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage(QString("✅ Пользователь '%1' добавлен с ролью '%2'%3")
                                         .arg(fullName, roleName, groupName), 3000);
            refresh();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при добавлении пользователя", 3000);
        }
    }
}


// DELETE USER  

void AdminPanel::deleteUser()
{
    if (m_selectedUserId == -1) {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
        m_statusBar->showMessage("⚠️ Выберите пользователя для удаления", 3000);
        return;
    }

    QMessageBox confirmDialog;
    confirmDialog.setWindowTitle("Подтверждение удаления");
    confirmDialog.setIcon(QMessageBox::Warning);
    confirmDialog.setText(QString("Вы действительно хотите удалить пользователя <b>'%1'</b>?").arg(m_selectedUserName));

    QString roleName;
    switch (m_selectedUserRole) {
    case 0: roleName = "Ученик"; break;
    case 1: roleName = "Преподаватель"; break;
    case 2: roleName = "Администратор"; break;
    default: roleName = "Неизвестно";
    }

    confirmDialog.setInformativeText(QString("Роль: %1\n\nЭто действие нельзя будет отменить!").arg(roleName));

    // ИСПРАВЛЕНО: используем addButton вместо setButtonText
    confirmDialog.addButton("✅ Да, удалить", QMessageBox::YesRole);
    confirmDialog.addButton("❌ Нет, отмена", QMessageBox::NoRole);
    confirmDialog.setDefaultButton(QMessageBox::No);

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
        if (DatabaseManager::instance().deleteUser(m_selectedUserId)) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage(QString("🗑️ Пользователь '%1' успешно удалён").arg(m_selectedUserName), 3000);
            refresh();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при удалении пользователя", 3000);
        }
    } else {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #f39c12; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
        m_statusBar->showMessage("ℹ️ Удаление отменено", 2000);
    }
}


// CHANGE ROLE

void AdminPanel::changeRole()
{
    if (m_selectedUserId == -1) {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 14px; padding: 5px 10px; border-radius: 4px;");
        m_statusBar->showMessage("⚠️ Выберите пользователя для смены роли", 3000);
        return;
    }

    ChangeRoleDialog dialog(m_selectedUserName, m_selectedUserRole, this);

    if (dialog.exec() == QDialog::Accepted) {
        int newRole = dialog.getNewRole();

        if (newRole != m_selectedUserRole) {
            if (DatabaseManager::instance().updateUserRole(m_selectedUserId, newRole)) {
                QString roleName = newRole == 0 ? "Ученик" : newRole == 1 ? "Преподаватель" : "Администратор";
                m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 14px; padding: 5px 10px; border-radius: 4px;");
                m_statusBar->showMessage(QString("🔄 Роль пользователя '%1' изменена на '%2'")
                                             .arg(m_selectedUserName, roleName), 3000);
                refresh();
            }
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #f39c12; font-size: 14px; padding: 5px 10px; border-radius: 4px;");
            m_statusBar->showMessage("ℹ️ Роль не была изменена (выбрана та же роль)", 3000);
        }
    }
}


// EDIT USER

void AdminPanel::editUser()
{
    if (m_selectedUserId == -1) {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 14px; padding: 5px 10px; border-radius: 4px;");
        m_statusBar->showMessage("⚠️ Выберите пользователя для редактирования", 3000);
        return;
    }

    EditUserDialog dialog(m_selectedUserName, m_selectedUserRole, m_selectedUserGroup, this);

    if (dialog.exec() == QDialog::Accepted) {
        QString newName = dialog.getNewName();
        int newGroupId = dialog.getNewGroupId();

        bool nameChanged = !newName.isEmpty() && newName != m_selectedUserName;
        bool groupChanged = (m_selectedUserRole == 0 && newGroupId != -1);

        if (nameChanged) {
            if (DatabaseManager::instance().updateUserFullName(m_selectedUserId, newName)) {
                m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
                m_statusBar->showMessage(QString("✏️ ФИО пользователя изменено на '%1'").arg(newName), 3000);
            } else {
                m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
                m_statusBar->showMessage("❌ Ошибка при обновлении ФИО", 3000);
                return;
            }
        }

        if (groupChanged) {
            if (DatabaseManager::instance().updateStudentGroup(m_selectedUserId, newGroupId)) {
                m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
                m_statusBar->showMessage(QString("📁 Группа пользователя обновлена"), 3000);
            } else {
                m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
                m_statusBar->showMessage("❌ Ошибка при обновлении группы", 3000);
                return;
            }
        }

        if (nameChanged || groupChanged) {
            refresh();
            emit groupsUpdated();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #f39c12; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("ℹ️ Данные не были изменены", 3000);
        }
    }
}


// EXPORT USERS TO CSV

void AdminPanel::exportUsersToCSV()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить список пользователей",
        "users.csv",
        "CSV файлы (*.csv)"
        );

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл");
        return;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    stream << QChar(0xFEFF);

    stream << "ID;ФИО;Роль;Группа\n";

    auto users = DatabaseManager::instance().getAllUsers();
    for (const auto& user : users) {
        if (user.size() >= 4) {
            QString roleName;
            int roleInt = user[2].toInt();
            if (roleInt == 0) roleName = "Ученик";
            else if (roleInt == 1) roleName = "Преподаватель";
            else if (roleInt == 2) roleName = "Администратор";
            else roleName = "Неизвестно";

            stream << user[0] << ";"   // ID
                   << user[1] << ";"   // ФИО
                   << roleName << ";"  // Роль
                   << user[3] << "\n"; // Группа
        }
    }

    file.close();

    m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
    m_statusBar->showMessage("✅ Список пользователей успешно сохранен", 3000);
}
