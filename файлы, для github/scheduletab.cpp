#include "scheduletab.h"
#include <QHeaderView>
#include <QDateTime>
#include <QSqlQuery>
#include <QFormLayout>
#include <QSpinBox>

// ============================================================
// ДИАЛОГ ДЛЯ ДОБАВЛЕНИЯ ПРЕДМЕТА
// ============================================================
AddSubjectDialog::AddSubjectDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Добавление предмета");
    setFixedSize(470, 380);

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
        QLineEdit, QComboBox, QSpinBox {
            padding: 8px 12px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 30px;
            font-size: 14px;
        }
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus {
            border: 2px solid #3498db;
        }
        QPushButton {
            padding: 8px 20px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            color: white;
            font-size: 14px;
            min-height: 35px;
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
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(30, 20, 30, 20);

    auto* titleLabel = new QLabel("📚 Добавление предмета");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* line = new QFrame;
    line->setObjectName("line");
    layout->addWidget(line);

    auto* formLayout = new QFormLayout();
    formLayout->setSpacing(10);
    formLayout->setLabelAlignment(Qt::AlignRight);

    m_nameEdit = new QLineEdit;
    m_nameEdit->setPlaceholderText("Например: Программирование");
    formLayout->addRow("Название:", m_nameEdit);

    m_semesterCombo = new QComboBox;
    m_semesterCombo->addItem("1-й семестр", 1);
    m_semesterCombo->addItem("2-й семестр", 2);
    m_semesterCombo->addItem("3-й семестр", 3);
    m_semesterCombo->addItem("4-й семестр", 4);
    formLayout->addRow("Семестр:", m_semesterCombo);

    m_hoursSpin = new QSpinBox;
    m_hoursSpin->setRange(16, 128);
    m_hoursSpin->setSingleStep(8);
    m_hoursSpin->setValue(32);
    m_hoursSpin->setSuffix(" ч.");
    formLayout->addRow("Часы:", m_hoursSpin);

    layout->addLayout(formLayout);
    layout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);

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

QString AddSubjectDialog::getSubjectName() const
{
    return m_nameEdit->text().trimmed();
}

int AddSubjectDialog::getSemester() const
{
    return m_semesterCombo->currentData().toInt();
}

int AddSubjectDialog::getHours() const
{
    return m_hoursSpin->value();
}

// ============================================================
// ДИАЛОГ ДЛЯ УСТАНОВКИ/РЕДАКТИРОВАНИЯ ПАРЫ
// ============================================================
EditLessonDialog::EditLessonDialog(QWidget* parent, int lessonId)
    : QDialog(parent), m_lessonId(lessonId)
{
    setWindowTitle(lessonId == -1 ? "Установка пары" : "Редактирование пары");
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
        QComboBox, QDateEdit, QSpinBox {
            padding: 8px 12px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 30px;
            font-size: 14px;
        }
        QComboBox:focus, QDateEdit:focus, QSpinBox:focus {
            border: 2px solid #3498db;
        }
        QDateEdit {
            min-width: 120px;
        }
        QPushButton {
            padding: 8px 20px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            color: white;
            font-size: 14px;
            min-height: 35px;
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
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(30, 20, 30, 20);

    auto* titleLabel = new QLabel(m_lessonId == -1 ? "📅 Установка пары" : "✏️ Редактирование пары");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* line = new QFrame;
    line->setObjectName("line");
    layout->addWidget(line);

    auto* formLayout = new QFormLayout();
    formLayout->setSpacing(10);
    formLayout->setLabelAlignment(Qt::AlignRight);

    // Группа
    m_groupCombo = new QComboBox;
    auto groups = DatabaseManager::instance().getAllGroups();
    for (const auto& group : groups) {
        if (group.size() > 1) {
            m_groupCombo->addItem(group[1], group[0].toInt());
        }
    }
    formLayout->addRow("Группа:", m_groupCombo);

    // Предмет
    m_subjectCombo = new QComboBox;
    QSqlQuery subjectQuery("SELECT id, name FROM disciplines ORDER BY name");
    while (subjectQuery.next()) {
        m_subjectCombo->addItem(subjectQuery.value(1).toString(), subjectQuery.value(0).toInt());
    }
    formLayout->addRow("Предмет:", m_subjectCombo);

    // Учитель
    m_teacherCombo = new QComboBox;
    QSqlQuery teacherQuery("SELECT id, full_name FROM teachers ORDER BY full_name");
    while (teacherQuery.next()) {
        m_teacherCombo->addItem(teacherQuery.value(1).toString(), teacherQuery.value(0).toInt());
    }
    formLayout->addRow("Учитель:", m_teacherCombo);

    // Дата
    m_dateEdit = new QDateEdit;
    m_dateEdit->setDate(QDate::currentDate());
    m_dateEdit->setCalendarPopup(true);
    formLayout->addRow("Дата:", m_dateEdit);

    // Номер пары
    m_lessonNumberCombo = new QComboBox;
    m_lessonNumberCombo->addItem("1-я пара", 1);
    m_lessonNumberCombo->addItem("2-я пара", 2);
    m_lessonNumberCombo->addItem("3-я пара", 3);
    m_lessonNumberCombo->addItem("4-я пара", 4);
    m_lessonNumberCombo->addItem("5-я пара", 5);
    formLayout->addRow("Пара:", m_lessonNumberCombo);

    layout->addLayout(formLayout);
    layout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);

    auto* okButton = new QPushButton(m_lessonId == -1 ? "✅ Установить" : "✅ Сохранить");
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

    if (m_lessonId != -1) {
        loadLessonData();
    }
}

void EditLessonDialog::loadLessonData()
{
    QSqlQuery query;
    query.prepare("SELECT group_id, discipline_id, teacher_id, lesson_date, lesson_number FROM lessons WHERE id = ?");
    query.bindValue(0, m_lessonId);

    if (query.exec() && query.next()) {
        int groupId = query.value(0).toInt();
        for (int i = 0; i < m_groupCombo->count(); ++i) {
            if (m_groupCombo->itemData(i).toInt() == groupId) {
                m_groupCombo->setCurrentIndex(i);
                break;
            }
        }

        int subjectId = query.value(1).toInt();
        for (int i = 0; i < m_subjectCombo->count(); ++i) {
            if (m_subjectCombo->itemData(i).toInt() == subjectId) {
                m_subjectCombo->setCurrentIndex(i);
                break;
            }
        }

        int teacherId = query.value(2).toInt();
        for (int i = 0; i < m_teacherCombo->count(); ++i) {
            if (m_teacherCombo->itemData(i).toInt() == teacherId) {
                m_teacherCombo->setCurrentIndex(i);
                break;
            }
        }

        QDate date = QDate::fromString(query.value(3).toString(), "yyyy-MM-dd");
        m_dateEdit->setDate(date);

        int lessonNumber = query.value(4).toInt();
        for (int i = 0; i < m_lessonNumberCombo->count(); ++i) {
            if (m_lessonNumberCombo->itemData(i).toInt() == lessonNumber) {
                m_lessonNumberCombo->setCurrentIndex(i);
                break;
            }
        }
    }
}

int EditLessonDialog::getGroupId() const
{
    return m_groupCombo->currentData().toInt();
}

int EditLessonDialog::getSubjectId() const
{
    return m_subjectCombo->currentData().toInt();
}

int EditLessonDialog::getTeacherId() const
{
    return m_teacherCombo->currentData().toInt();
}

QDate EditLessonDialog::getDate() const
{
    return m_dateEdit->date();
}

int EditLessonDialog::getLessonNumber() const
{
    return m_lessonNumberCombo->currentData().toInt();
}

// ============================================================
// МОДЕЛЬ ДЛЯ РАСПИСАНИЯ
// ============================================================
class ScheduleTableModel : public QAbstractTableModel
{
public:
    ScheduleTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setData(const QList<QStringList>& data) {
        beginResetModel();
        m_data = data;
        endResetModel();
    }

    int rowCount(const QModelIndex&) const override {
        return m_data.size();
    }

    int columnCount(const QModelIndex&) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (!index.isValid() || role != Qt::DisplayRole || index.row() >= m_data.size()) {
            return QVariant();
        }
        if (index.column() < m_data[index.row()].size()) {
            return m_data[index.row()][index.column()];
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
            QStringList headers = {"Пара", "Дисциплина", "Группа", "Учитель", "Аудитория"};
            if (section < headers.size()) return headers[section];
        }
        return QVariant();
    }

    int getLessonId(int row) const {
        if (row < 0 || row >= m_data.size() || m_data[row].size() < 6) {
            return -1;
        }
        return m_data[row][5].toInt();
    }

private:
    QList<QStringList> m_data;
};

// ============================================================
// ОСНОВНАЯ ВКЛАДКА
// ============================================================
ScheduleTab::ScheduleTab(QWidget* parent, int userRole)
    : QWidget(parent), m_userRole(userRole), m_selectedLessonId(-1)
{
    setupUI();
    setupPermissions();
    refresh();
}

void ScheduleTab::setupUI()
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
        QDateEdit {
            padding: 6px 10px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 25px;
            font-size: 13px;
        }
        QDateEdit:focus {
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
        QPushButton#addSubjectBtn {
            background: #9b59b6;
        }
        QPushButton#addSubjectBtn:hover {
            background: #8e44ad;
        }
        QPushButton#addLessonBtn {
            background: #2ecc71;
        }
        QPushButton#addLessonBtn:hover {
            background: #27ae60;
        }
        QPushButton#editLessonBtn {
            background: #f39c12;
        }
        QPushButton#editLessonBtn:hover {
            background: #d68910;
        }
        QPushButton#deleteLessonBtn {
            background: #e74c3c;
        }
        QPushButton#deleteLessonBtn:hover {
            background: #c0392b;
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
    )");

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    auto* titleLabel = new QLabel("📅 Расписание занятий");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #3498db; padding: 5px 0 8px 0;");
    mainLayout->addWidget(titleLabel);

    // ===== ВЕРХНЯЯ ПАНЕЛЬ =====
    auto* topGroup = new QGroupBox("📋 Управление расписанием");
    auto* topLayout = new QHBoxLayout(topGroup);
    topLayout->setContentsMargins(10, 8, 10, 8);
    topLayout->setSpacing(8);

    topLayout->addWidget(new QLabel("Дата:"));

    m_dateEdit = new QDateEdit;
    m_dateEdit->setDate(QDate::currentDate());
    m_dateEdit->setCalendarPopup(true);
    m_dateEdit->setDisplayFormat("dd.MM.yyyy");
    m_dateEdit->setMinimumWidth(120);
    topLayout->addWidget(m_dateEdit);

    topLayout->addStretch();

    // Кнопки для администратора - ТЕКСТ ДОЛЖЕН ОТОБРАЖАТЬСЯ
    m_addSubjectButton = new QPushButton("Добавить предмет");
    m_addSubjectButton->setObjectName("addSubjectBtn");
    m_addLessonButton = new QPushButton("Установить пару");
    m_addLessonButton->setObjectName("addLessonBtn");
    m_editLessonButton = new QPushButton("Редактировать пару");
    m_editLessonButton->setObjectName("editLessonBtn");
    m_deleteLessonButton = new QPushButton("Удалить пару");
    m_deleteLessonButton->setObjectName("deleteLessonBtn");

    // Можно добавить иконки через setText с эмодзи
    m_addSubjectButton->setText("📚 Добавить предмет");
    m_addLessonButton->setText("📅 Установить пару");
    m_editLessonButton->setText("✏️ Редактировать пару");
    m_deleteLessonButton->setText("🗑 Удалить пару");

    topLayout->addWidget(m_addSubjectButton);
    topLayout->addWidget(m_addLessonButton);
    topLayout->addWidget(m_editLessonButton);
    topLayout->addWidget(m_deleteLessonButton);

    mainLayout->addWidget(topGroup);

    // ===== ТАБЛИЦА =====
    auto* tableGroup = new QGroupBox("📋 Расписание");
    auto* tableLayout = new QVBoxLayout(tableGroup);
    tableLayout->setContentsMargins(10, 8, 10, 8);
    m_tableView = new QTableView;
    m_model = new ScheduleTableModel(this);
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
    connect(m_dateEdit, &QDateEdit::dateChanged, this, &ScheduleTab::onDateChanged);
    connect(m_addSubjectButton, &QPushButton::clicked, this, &ScheduleTab::addSubject);
    connect(m_addLessonButton, &QPushButton::clicked, this, &ScheduleTab::addLesson);
    connect(m_editLessonButton, &QPushButton::clicked, this, &ScheduleTab::editLesson);
    connect(m_deleteLessonButton, &QPushButton::clicked, this, &ScheduleTab::deleteLesson);

    connect(m_tableView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &ScheduleTab::onTableRowSelected);
}

void ScheduleTab::setupPermissions()
{
    bool isAdmin = (m_userRole == 2);
    m_addSubjectButton->setVisible(isAdmin);
    m_addLessonButton->setVisible(isAdmin);
    m_editLessonButton->setVisible(isAdmin);
    m_deleteLessonButton->setVisible(isAdmin);  // <-- НОВАЯ КНОПКА
}

void ScheduleTab::onTableRowSelected(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous);
    if (current.isValid()) {
        auto* model = dynamic_cast<ScheduleTableModel*>(m_model);
        if (model) {
            m_selectedLessonId = model->getLessonId(current.row());
        }
    } else {
        m_selectedLessonId = -1;
    }
}

bool ScheduleTab::isLessonSelected() const
{
    return m_selectedLessonId != -1;
}

void ScheduleTab::onDateChanged(const QDate& date)
{
    loadSchedule(date);
}

void ScheduleTab::loadSchedule(const QDate& date)
{
    QList<QStringList> scheduleData;

    QString dateStr = date.toString("yyyy-MM-dd");

    QSqlQuery query;
    query.prepare(
        "SELECT l.id, l.lesson_number, d.name, g.name, t.full_name, l.room "
        "FROM lessons l "
        "JOIN disciplines d ON l.discipline_id = d.id "
        "JOIN groups g ON l.group_id = g.id "
        "JOIN teachers t ON l.teacher_id = t.id "
        "WHERE l.lesson_date = ? "
        "ORDER BY l.lesson_number"
        );
    query.bindValue(0, dateStr);

    if (query.exec()) {
        while (query.next()) {
            QStringList row;
            row << query.value(1).toString() + "-я пара"
                << query.value(2).toString()
                << query.value(3).toString()
                << query.value(4).toString()
                << query.value(5).toString()
                << query.value(0).toString();
            scheduleData.append(row);
        }
    }

    if (auto* model = dynamic_cast<ScheduleTableModel*>(m_model)) {
        model->setData(scheduleData);
    }

    // Сбрасываем выбранную пару после обновления
    m_selectedLessonId = -1;

    m_statusBar->showMessage(QString("Загружено расписание на %1 (%2 пар)")
                                 .arg(date.toString("dd.MM.yyyy"))
                                 .arg(scheduleData.size()), 2000);
}

void ScheduleTab::refresh()
{
    loadSchedule(m_dateEdit->date());
}

void ScheduleTab::addSubject()
{
    AddSubjectDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getSubjectName();
        int semester = dialog.getSemester();
        int hours = dialog.getHours();

        if (name.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите название предмета");
            return;
        }

        QSqlQuery query;
        query.prepare("INSERT INTO disciplines (name, semester, hours) VALUES (?, ?, ?)");
        query.bindValue(0, name);
        query.bindValue(1, semester);
        query.bindValue(2, hours);

        if (query.exec()) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage(QString("✅ Предмет '%1' успешно добавлен").arg(name), 3000);
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при добавлении предмета", 3000);
        }
    }
}

void ScheduleTab::addLesson()
{
    EditLessonDialog dialog(this, -1);

    if (dialog.exec() == QDialog::Accepted) {
        int groupId = dialog.getGroupId();
        int subjectId = dialog.getSubjectId();
        int teacherId = dialog.getTeacherId();
        QDate date = dialog.getDate();
        int lessonNumber = dialog.getLessonNumber();

        if (groupId == -1) {
            QMessageBox::warning(this, "Ошибка", "Выберите группу");
            return;
        }

        if (subjectId == -1) {
            QMessageBox::warning(this, "Ошибка", "Выберите предмет");
            return;
        }

        if (teacherId == -1) {
            QMessageBox::warning(this, "Ошибка", "Выберите учителя");
            return;
        }

        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT id FROM lessons WHERE lesson_date = ? AND lesson_number = ? AND group_id = ?");
        checkQuery.bindValue(0, date.toString("yyyy-MM-dd"));
        checkQuery.bindValue(1, lessonNumber);
        checkQuery.bindValue(2, groupId);

        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, "Ошибка", "На эту дату и время уже есть пара для этой группы!");
            return;
        }

        QSqlQuery query;
        query.prepare(
            "INSERT INTO lessons (discipline_id, group_id, teacher_id, lesson_date, lesson_number, room) "
            "VALUES (?, ?, ?, ?, ?, ?)"
            );
        query.bindValue(0, subjectId);
        query.bindValue(1, groupId);
        query.bindValue(2, teacherId);
        query.bindValue(3, date.toString("yyyy-MM-dd"));
        query.bindValue(4, lessonNumber);
        query.bindValue(5, "Ауд. " + QString::number(100 + lessonNumber * 5));

        if (query.exec()) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("✅ Пара успешно установлена", 3000);
            refresh();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при установке пары: " + query.lastError().text(), 3000);
        }
    }
}

void ScheduleTab::editLesson()
{
    // ===== ПРОВЕРКА: ВЫБРАНА ЛИ ПАРА =====
    if (!isLessonSelected()) {
        QMessageBox::information(this, "Редактирование пары",
                                 "Для редактирования пары необходимо сначала выбрать её в таблице.\n\n"
                                 "1. Кликните на строку с нужной парой\n"
                                 "2. Затем нажмите кнопку '✏️ Редактировать пару'");
        return;
    }

    EditLessonDialog dialog(this, m_selectedLessonId);

    if (dialog.exec() == QDialog::Accepted) {
        int groupId = dialog.getGroupId();
        int subjectId = dialog.getSubjectId();
        int teacherId = dialog.getTeacherId();
        QDate date = dialog.getDate();
        int lessonNumber = dialog.getLessonNumber();

        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT id FROM lessons WHERE lesson_date = ? AND lesson_number = ? AND group_id = ? AND id != ?");
        checkQuery.bindValue(0, date.toString("yyyy-MM-dd"));
        checkQuery.bindValue(1, lessonNumber);
        checkQuery.bindValue(2, groupId);
        checkQuery.bindValue(3, m_selectedLessonId);

        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, "Ошибка", "На эту дату и время уже есть пара для этой группы!");
            return;
        }

        QSqlQuery query;
        query.prepare(
            "UPDATE lessons SET discipline_id = ?, group_id = ?, teacher_id = ?, lesson_date = ?, lesson_number = ?, room = ? "
            "WHERE id = ?"
            );
        query.bindValue(0, subjectId);
        query.bindValue(1, groupId);
        query.bindValue(2, teacherId);
        query.bindValue(3, date.toString("yyyy-MM-dd"));
        query.bindValue(4, lessonNumber);
        query.bindValue(5, "Ауд. " + QString::number(100 + lessonNumber * 5));
        query.bindValue(6, m_selectedLessonId);

        if (query.exec()) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("✏ Пара успешно обновлена", 3000);
            refresh();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при обновлении пары: " + query.lastError().text(), 3000);
        }
    }
}

void ScheduleTab::deleteLesson()
{
    // ===== ПРОВЕРКА: ВЫБРАНА ЛИ ПАРА =====
    if (!isLessonSelected()) {
        QMessageBox::information(this, "Удаление пары",
                                 "Для удаления пары необходимо сначала выбрать её в таблице.\n\n"
                                 "1. Кликните на строку с нужной парой\n"
                                 "2. Затем нажмите кнопку '🗑 Удалить пару'");
        return;
    }

    // Получаем информацию о паре для подтверждения
    QSqlQuery query;
    query.prepare(
        "SELECT d.name, g.name, l.lesson_number, l.lesson_date "
        "FROM lessons l "
        "JOIN disciplines d ON l.discipline_id = d.id "
        "JOIN groups g ON l.group_id = g.id "
        "WHERE l.id = ?"
        );
    query.bindValue(0, m_selectedLessonId);

    QString lessonInfo;
    if (query.exec() && query.next()) {
        QString subject = query.value(0).toString();
        QString group = query.value(1).toString();
        int number = query.value(2).toInt();
        QDate date = QDate::fromString(query.value(3).toString(), "yyyy-MM-dd");
        lessonInfo = QString("%1-я пара\nПредмет: %2\nГруппа: %3\nДата: %4")
                         .arg(number).arg(subject).arg(group).arg(date.toString("dd.MM.yyyy"));
    } else {
        lessonInfo = "ID: " + QString::number(m_selectedLessonId);
    }

    QMessageBox confirmDialog;
    confirmDialog.setWindowTitle("Подтверждение удаления");
    confirmDialog.setIcon(QMessageBox::Warning);
    confirmDialog.setText("Вы действительно хотите удалить эту пару?");
    confirmDialog.setInformativeText(lessonInfo + "\n\nЭто действие нельзя будет отменить!");
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
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM lessons WHERE id = ?");
        deleteQuery.bindValue(0, m_selectedLessonId);

        if (deleteQuery.exec()) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("🗑 Пара успешно удалена", 3000);
            refresh();
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при удалении пары: " + deleteQuery.lastError().text(), 3000);
        }
    } else {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #f39c12; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
        m_statusBar->showMessage("ℹ Удаление отменено", 2000);
    }
}