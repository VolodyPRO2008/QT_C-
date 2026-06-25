#include "groupstab.h"
#include "databasemanager.h"
#include <QLabel>
#include <QHeaderView>
#include <QFormLayout>

// ============================================================
// ДИАЛОГ ДЛЯ ДОБАВЛЕНИЯ ГРУППЫ (БЕЗ СТУДЕНТОВ)
// ============================================================
AddGroupDialog::AddGroupDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Добавление группы");
    setFixedSize(420, 320);  // Уменьшено, т.к. убрали студентов

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
        QLineEdit {
            padding: 5px 14px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 30px;
            font-size: 15px;
            margin-top: -5px;
        }
        QLineEdit:focus {
            border: 2px solid #3498db;
        }
        QSpinBox {
            padding: 3px 12px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 30px;
            font-size: 15px;
            min-width: 80px;
            margin-top: -5px;
        }
        QSpinBox:focus {
            border: 2px solid #3498db;
        }
        QSpinBox::up-button, QSpinBox::down-button {
            background: #34495e;
            border: none;
            color: #ecf0f1;
            width: 20px;
            height: 14px;
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
        QFormLayout {
            spacing: 8px;
        }
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(18);
    layout->setContentsMargins(35, 30, 35, 30);

    auto* titleLabel = new QLabel("📚 Добавление группы");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* line = new QFrame;
    line->setObjectName("line");
    layout->addWidget(line);

    auto* formGroup = new QGroupBox("📝 Данные группы");
    auto* formLayout = new QFormLayout(formGroup);
    formLayout->setSpacing(8);
    formLayout->setLabelAlignment(Qt::AlignRight);

    m_nameEdit = new QLineEdit;
    m_nameEdit->setPlaceholderText("Например: ИОС-102");
    formLayout->addRow("Название группы:", m_nameEdit);

    m_courseSpin = new QSpinBox;
    m_courseSpin->setRange(1, 6);
    m_courseSpin->setValue(1);
    formLayout->addRow("Курс:", m_courseSpin);

    m_yearSpin = new QSpinBox;
    m_yearSpin->setRange(2020, 2030);
    m_yearSpin->setValue(QDate::currentDate().year());
    formLayout->addRow("Год создания:", m_yearSpin);

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
}

QString AddGroupDialog::getGroupName() const { return m_nameEdit->text().trimmed(); }
int AddGroupDialog::getCourse() const { return m_courseSpin->value(); }
int AddGroupDialog::getYear() const { return m_yearSpin->value(); }

// ============================================================
// ДИАЛОГ ДЛЯ РЕДАКТИРОВАНИЯ ГРУППЫ (БЕЗ СТУДЕНТОВ)
// ============================================================
EditGroupDialog::EditGroupDialog(const QString& currentName, int currentCourse, int currentYear, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Редактирование группы");
    setFixedSize(500, 460);

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
        QLabel#currentValue {
            color: #f39c12;
            font-weight: bold;
            font-size: 15px;
        }
        QLineEdit {
            padding: 5px 14px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 30px;
            font-size: 15px;
            margin-top: -5px;
        }
        QLineEdit:focus {
            border: 2px solid #3498db;
        }
        QSpinBox {
            padding: 3px 12px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 30px;
            font-size: 15px;
            min-width: 80px;
            margin-top: -5px;
        }
        QSpinBox:focus {
            border: 2px solid #3498db;
        }
        QSpinBox::up-button, QSpinBox::down-button {
            background: #34495e;
            border: none;
            color: #ecf0f1;
            width: 20px;
            height: 14px;
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
        QFormLayout {
            spacing: 8px;
        }
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(18);
    layout->setContentsMargins(35, 30, 35, 30);

    auto* titleLabel = new QLabel("✏️ Редактирование группы");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* line = new QFrame;
    line->setObjectName("line");
    layout->addWidget(line);

    // Текущие данные
    auto* infoGroup = new QGroupBox("📋 Текущие данные");
    auto* infoLayout = new QFormLayout(infoGroup);
    infoLayout->setSpacing(8);
    infoLayout->setLabelAlignment(Qt::AlignRight);

    auto* nameLabel = new QLabel(currentName);
    nameLabel->setObjectName("currentValue");
    infoLayout->addRow("Название:", nameLabel);

    auto* courseLabel = new QLabel(QString::number(currentCourse));
    courseLabel->setObjectName("currentValue");
    infoLayout->addRow("Курс:", courseLabel);

    auto* yearLabel = new QLabel(QString::number(currentYear));
    yearLabel->setObjectName("currentValue");
    infoLayout->addRow("Год:", yearLabel);

    layout->addWidget(infoGroup);

    // Новые данные
    auto* formGroup = new QGroupBox("✏️ Новые данные");
    auto* formLayout = new QFormLayout(formGroup);
    formLayout->setSpacing(8);
    formLayout->setLabelAlignment(Qt::AlignRight);

    m_nameEdit = new QLineEdit;
    m_nameEdit->setText(currentName);
    formLayout->addRow("Название:", m_nameEdit);

    m_courseSpin = new QSpinBox;
    m_courseSpin->setRange(1, 6);
    m_courseSpin->setValue(currentCourse);
    formLayout->addRow("Курс:", m_courseSpin);

    m_yearSpin = new QSpinBox;
    m_yearSpin->setRange(2020, 2030);
    m_yearSpin->setValue(currentYear);
    formLayout->addRow("Год:", m_yearSpin);

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

QString EditGroupDialog::getNewName() const { return m_nameEdit->text().trimmed(); }
int EditGroupDialog::getNewCourse() const { return m_courseSpin->value(); }
int EditGroupDialog::getNewYear() const { return m_yearSpin->value(); }

// ============================================================
// GROUPS TAB
// ============================================================
GroupsTab::GroupsTab(QWidget* parent)
    : QWidget(parent), m_selectedGroupId(-1), m_selectedGroupCourse(0), m_selectedGroupYear(0)
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
        QLineEdit {
            padding: 6px 10px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 25px;
            font-size: 13px;
        }
        QLineEdit:focus {
            border: 2px solid #3498db;
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
        QPushButton#editBtn {
            background: #3498db;
        }
        QPushButton#editBtn:hover {
            background: #2980b9;
        }
        QPushButton#clearBtn {
            background: #95a5a6;
        }
        QPushButton#clearBtn:hover {
            background: #7f8c8d;
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

    auto* titleLabel = new QLabel("📚 Редактирование групп");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #3498db; padding: 5px 0 8px 0;");
    mainLayout->addWidget(titleLabel);

    // ===== ВЫБОР ГРУППЫ =====
    auto* selectGroup = new QGroupBox("👥 Выбор группы");
    auto* selectLayout = new QHBoxLayout(selectGroup);
    selectLayout->setContentsMargins(10, 8, 10, 8);

    selectLayout->addWidget(new QLabel("Группа:"));
    m_groupCombo = new QComboBox;
    m_groupCombo->setMinimumWidth(250);
    selectLayout->addWidget(m_groupCombo);
    selectLayout->addStretch();

    mainLayout->addWidget(selectGroup);

    // ===== УПРАВЛЕНИЕ ГРУППОЙ =====
    auto* controlGroup = new QGroupBox("✏️ Управление группой");
    auto* controlLayout = new QHBoxLayout(controlGroup);
    controlLayout->setContentsMargins(10, 8, 10, 8);
    controlLayout->setSpacing(8);

    m_addButton = new QPushButton("➕ Добавить");
    m_addButton->setObjectName("addBtn");
    m_deleteButton = new QPushButton("🗑 Удалить");
    m_deleteButton->setObjectName("deleteBtn");
    m_editButton = new QPushButton("✏️ Редактировать");
    m_editButton->setObjectName("editBtn");

    controlLayout->addWidget(m_addButton);
    controlLayout->addWidget(m_deleteButton);
    controlLayout->addWidget(m_editButton);
    controlLayout->addStretch();

    mainLayout->addWidget(controlGroup);

    // ===== ФИЛЬТР =====
    auto* filterGroup = new QGroupBox("🔍 Фильтр");
    auto* filterLayout = new QHBoxLayout(filterGroup);
    filterLayout->setContentsMargins(10, 8, 10, 8);

    filterLayout->addWidget(new QLabel("Поиск:"));
    m_filterEdit = new QLineEdit;
    m_filterEdit->setPlaceholderText("Введите название группы...");
    filterLayout->addWidget(m_filterEdit);

    m_clearFilterButton = new QPushButton("✖ Очистить");
    m_clearFilterButton->setObjectName("clearBtn");
    filterLayout->addWidget(m_clearFilterButton);
    filterLayout->addStretch();

    mainLayout->addWidget(filterGroup);

    // ===== ТАБЛИЦА =====
    auto* tableGroup = new QGroupBox("📋 Список групп");
    auto* tableLayout = new QVBoxLayout(tableGroup);
    tableLayout->setContentsMargins(10, 8, 10, 8);
    m_tableView = new QTableView;
    m_model = new GroupsTableModel(this);
    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableLayout->addWidget(m_tableView);
    mainLayout->addWidget(tableGroup);

    // ===== СТАТУС БАР =====
    m_statusBar = new QStatusBar;
    m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
    m_statusBar->showMessage("Готов к работе");
    mainLayout->addWidget(m_statusBar);

    // ===== СИГНАЛЫ =====
    connect(m_addButton, &QPushButton::clicked, this, &GroupsTab::addGroup);
    connect(m_deleteButton, &QPushButton::clicked, this, &GroupsTab::deleteGroup);
    connect(m_editButton, &QPushButton::clicked, this, &GroupsTab::editGroup);
    connect(m_filterEdit, &QLineEdit::textChanged, this, &GroupsTab::filterGroups);
    connect(m_clearFilterButton, &QPushButton::clicked, this, &GroupsTab::clearFilter);
    connect(m_groupCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GroupsTab::onGroupSelected);
    connect(m_tableView->selectionModel(), &QItemSelectionModel::currentChanged,
            [this](const QModelIndex& current, const QModelIndex&) {
                if (current.isValid()) {
                    int groupId = m_model->data(m_model->index(current.row(), 0)).toInt();
                    for (int i = 0; i < m_groupCombo->count(); ++i) {
                        if (m_groupCombo->itemData(i).toInt() == groupId) {
                            m_groupCombo->setCurrentIndex(i);
                            break;
                        }
                    }
                }
            });

    refresh();
}

void GroupsTab::refresh()
{
    // Принудительно обновляем модель
    if (auto* model = qobject_cast<GroupsTableModel*>(m_model)) {
        model->refresh();
    }

    // Обновляем комбобокс
    auto groups = DatabaseManager::instance().getAllGroups();
    m_groupCombo->clear();
    m_groupCombo->addItem("-- Выберите группу --", -1);

    for (const auto& group : groups) {
        if (group.size() >= 4) {
            QString displayName = group[1];
            int groupId = group[0].toInt();
            int course = group[2].toInt();
            int year = group[3].toInt();
            int students = group[4].toInt();  // Получаем количество студентов
            m_groupCombo->addItem(QString("%1 (Курс %2, %3 г., %4 чел.)")
                                      .arg(displayName).arg(course).arg(year).arg(students), groupId);
        }
    }

    m_filterEdit->clear();
    m_statusBar->showMessage("Данные обновлены", 2000);
}

void GroupsTab::onGroupSelected(int index)
{
    if (index <= 0 || m_groupCombo->currentData().toInt() == -1) {
        m_selectedGroupId = -1;
        m_selectedGroupName = "";
        m_selectedGroupCourse = 0;
        m_selectedGroupYear = 0;
        return;
    }

    m_selectedGroupId = m_groupCombo->currentData().toInt();

    auto groups = DatabaseManager::instance().getAllGroups();
    for (const auto& group : groups) {
        if (group[0].toInt() == m_selectedGroupId) {
            m_selectedGroupName = group[1];
            m_selectedGroupCourse = group[2].toInt();
            m_selectedGroupYear = group[3].toInt();
            break;
        }
    }

    for (int row = 0; row < m_model->rowCount(); ++row) {
        if (m_model->data(m_model->index(row, 0)).toInt() == m_selectedGroupId) {
            m_tableView->selectRow(row);
            break;
        }
    }
}

void GroupsTab::addGroup()
{
    AddGroupDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getGroupName();
        int course = dialog.getCourse();
        int year = dialog.getYear();

        if (name.isEmpty()) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("⚠️ Введите название группы", 3000);
            return;
        }

        if (DatabaseManager::instance().addGroup(name, course, year)) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage(QString("✅ Группа '%1' успешно добавлена").arg(name), 3000);
            refresh();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при добавлении группы", 3000);
        }
    }
}

void GroupsTab::editGroup()
{
    if (m_selectedGroupId == -1) {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
        m_statusBar->showMessage("⚠️ Выберите группу для редактирования", 3000);
        return;
    }

    EditGroupDialog dialog(m_selectedGroupName, m_selectedGroupCourse, m_selectedGroupYear, this);

    if (dialog.exec() == QDialog::Accepted) {
        QString newName = dialog.getNewName();
        int newCourse = dialog.getNewCourse();
        int newYear = dialog.getNewYear();

        if (newName.isEmpty()) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("⚠️ Название не может быть пустым", 3000);
            return;
        }

        if (DatabaseManager::instance().updateGroup(m_selectedGroupId, newName, newCourse, newYear)) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage(QString("✏️ Группа '%1' успешно обновлена").arg(newName), 3000);
            refresh();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при обновлении группы", 3000);
        }
    }
}

void GroupsTab::deleteGroup()
{
    if (m_selectedGroupId == -1) {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
        m_statusBar->showMessage("⚠️ Выберите группу для удаления", 3000);
        return;
    }

    QMessageBox confirmDialog;
    confirmDialog.setWindowTitle("Подтверждение удаления");
    confirmDialog.setIcon(QMessageBox::Warning);
    confirmDialog.setText(QString("Вы действительно хотите удалить группу <b>'%1'</b>?").arg(m_selectedGroupName));
    confirmDialog.setInformativeText("Это действие нельзя будет отменить!\nВсе студенты, связанные с этой группой, также будут удалены.");
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
        if (DatabaseManager::instance().deleteGroup(m_selectedGroupName)) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage(QString("🗑️ Группа '%1' успешно удалена").arg(m_selectedGroupName), 3000);
            refresh();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при удалении группы", 3000);
        }
    } else {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #f39c12; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
        m_statusBar->showMessage("ℹ️ Удаление отменено", 2000);
    }
}

void GroupsTab::filterGroups(const QString& text)
{
    if (auto* model = qobject_cast<GroupsTableModel*>(m_model)) {
        model->setFilter(text);
    }
}

void GroupsTab::clearFilter()
{
    m_filterEdit->clear();
}