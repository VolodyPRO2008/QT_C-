#include "attendancetab.h"
#include <QHeaderView>
#include <QDateTime>
#include <QSqlQuery>

// ============================================================
// ДИАЛОГ ДЛЯ РЕДАКТИРОВАНИЯ ПОСЕЩАЕМОСТИ
// ============================================================
EditAttendanceDialog::EditAttendanceDialog(int attendanceId, int studentId, const QString& studentName, bool currentStatus, const QString& currentComment, QWidget* parent)
    : QDialog(parent)
{
    // Используем параметры, чтобы убрать предупреждения
    Q_UNUSED(attendanceId);
    Q_UNUSED(studentId);

    setWindowTitle("Редактирование посещаемости");
    setFixedSize(500, 400);

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
        QLabel#studentName {
            color: #f39c12;
            font-weight: bold;
            font-size: 15px;
        }
        QComboBox {
            padding: 8px 12px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 30px;
            font-size: 14px;
        }
        QComboBox:focus {
            border: 2px solid #3498db;
        }
        QLineEdit {
            padding: 8px 12px;
            border: 2px solid #34495e;
            border-radius: 6px;
            background: #34495e;
            color: #ecf0f1;
            min-height: 30px;
            font-size: 14px;
        }
        QLineEdit:focus {
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
    )");

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(30, 20, 30, 20);

    auto* titleLabel = new QLabel("✏️ Редактирование посещаемости");
    titleLabel->setObjectName("title");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    auto* line = new QFrame;
    line->setObjectName("line");
    layout->addWidget(line);

    // Информация о студенте
    auto* infoLayout = new QHBoxLayout();
    auto* infoLabel = new QLabel("Студент:");
    infoLabel->setObjectName("infoLabel");
    infoLayout->addWidget(infoLabel);
    auto* nameLabel = new QLabel(studentName);
    nameLabel->setObjectName("studentName");
    infoLayout->addWidget(nameLabel);
    infoLayout->addStretch();
    layout->addLayout(infoLayout);

    // Статус
    auto* statusLayout = new QHBoxLayout();
    auto* statusLabel = new QLabel("Статус:");
    statusLabel->setObjectName("infoLabel");
    statusLayout->addWidget(statusLabel);
    m_statusCombo = new QComboBox;
    m_statusCombo->addItem("Присутствовал", 1);
    m_statusCombo->addItem("Отсутствовал", 0);
    m_statusCombo->addItem("Опоздал", 2);
    // Устанавливаем текущий статус
    if (currentStatus) {
        m_statusCombo->setCurrentIndex(0);
    } else {
        m_statusCombo->setCurrentIndex(1);
    }
    statusLayout->addWidget(m_statusCombo);
    statusLayout->addStretch();
    layout->addLayout(statusLayout);

    // Комментарий
    auto* commentLayout = new QHBoxLayout();
    auto* commentLabel = new QLabel("Комментарий:");
    commentLabel->setObjectName("infoLabel");
    commentLayout->addWidget(commentLabel);
    m_commentEdit = new QLineEdit;
    m_commentEdit->setText(currentComment);
    m_commentEdit->setPlaceholderText("Введите комментарий...");
    commentLayout->addWidget(m_commentEdit);
    layout->addLayout(commentLayout);

    layout->addStretch();

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);

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

bool EditAttendanceDialog::getNewStatus() const
{
    int status = m_statusCombo->currentData().toInt();
    return status == 1; // true - присутствовал, false - отсутствовал
}

QString EditAttendanceDialog::getNewComment() const
{
    return m_commentEdit->text().trimmed();
}

// ============================================================
// МОДЕЛЬ ДЛЯ ПОСЕЩАЕМОСТИ
// ============================================================
class AttendanceEditTableModel : public QAbstractTableModel
{
public:
    AttendanceEditTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

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
            QStringList headers = {"Студент", "Дисциплина", "Статус", "Комментарий", "Учитель"};
            if (section < headers.size()) return headers[section];
        }
        return QVariant();
    }

    int getAttendanceId(int row) const {
        if (row < 0 || row >= m_data.size() || m_data[row].size() < 6) {
            return -1;
        }
        return m_data[row][5].toInt();
    }

    int getStudentId(int row) const {
        if (row < 0 || row >= m_data.size() || m_data[row].size() < 7) {
            return -1;
        }
        return m_data[row][6].toInt();
    }

private:
    QList<QStringList> m_data;
};

// ============================================================
// ОСНОВНАЯ ВКЛАДКА
// ============================================================
AttendanceEditTab::AttendanceEditTab(QWidget* parent, int userRole)
    : QWidget(parent), m_userRole(userRole), m_selectedAttendanceId(-1)
{
    setupUI();
    setupPermissions();
    refresh();
}

void AttendanceEditTab::setupUI()
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
        QPushButton#editBtn {
            background: #f39c12;
        }
        QPushButton#editBtn:hover {
            background: #d68910;
        }
        QPushButton#deleteBtn {
            background: #e74c3c;
        }
        QPushButton#deleteBtn:hover {
            background: #c0392b;
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

    auto* titleLabel = new QLabel("📊 Редактирование посещаемости");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #3498db; padding: 5px 0 8px 0;");
    mainLayout->addWidget(titleLabel);

    // ===== ВЕРХНЯЯ ПАНЕЛЬ =====
    auto* topGroup = new QGroupBox("📋 Управление посещаемостью");
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

    // Кнопки для администратора
    m_editButton = new QPushButton("✏️ Редактировать");
    m_editButton->setObjectName("editBtn");
    m_deleteButton = new QPushButton("🗑 Удалить");
    m_deleteButton->setObjectName("deleteBtn");
    m_exportButton = new QPushButton("📥 Скачать отчет CSV");  // <-- НОВАЯ КНОПКА
    m_exportButton->setObjectName("exportBtn");

    topLayout->addWidget(m_editButton);
    topLayout->addWidget(m_deleteButton);
    topLayout->addWidget(m_exportButton);

    mainLayout->addWidget(topGroup);

    // ===== ТАБЛИЦА =====
    auto* tableGroup = new QGroupBox("📋 Список посещаемости");
    auto* tableLayout = new QVBoxLayout(tableGroup);
    tableLayout->setContentsMargins(10, 8, 10, 8);
    m_tableView = new QTableView;
    m_model = new AttendanceEditTableModel(this);
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
    connect(m_dateEdit, &QDateEdit::dateChanged, this, &AttendanceEditTab::onDateChanged);
    connect(m_editButton, &QPushButton::clicked, this, &AttendanceEditTab::editAttendance);
    connect(m_deleteButton, &QPushButton::clicked, this, &AttendanceEditTab::deleteAttendance);
    connect(m_exportButton, &QPushButton::clicked, this, &AttendanceEditTab::exportAttendanceToCSV);  // <-- НОВЫЙ СИГНАЛ

    connect(m_tableView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &AttendanceEditTab::onTableRowSelected);
}

void AttendanceEditTab::setupPermissions()
{
    bool isAdmin = (m_userRole == 2);
    m_editButton->setVisible(isAdmin);
    m_deleteButton->setVisible(isAdmin);
    m_exportButton->setVisible(isAdmin);  // <-- НОВАЯ КНОПКА
}

// ============================================================
// ЭКСПОРТ В CSV (НОВЫЙ МЕТОД)
// ============================================================
void AttendanceEditTab::exportAttendanceToCSV()
{
    QString dateStr = m_dateEdit->date().toString("dd.MM.yyyy");

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет о посещаемости",
        QString("attendance_%1.csv").arg(dateStr.replace(".", "_")),
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

    // ===== ИСПРАВЛЕНО: добавляем BOM для UTF-8 =====
    stream.setEncoding(QStringConverter::Utf8);

    // Записываем BOM (Byte Order Mark) для корректного отображения в Excel
    stream << QChar(0xFEFF);

    // Заголовки
    stream << "Студент;Дисциплина;Статус;Комментарий;Учитель\n";

    // Данные из таблицы
    for (int row = 0; row < m_model->rowCount(); ++row) {
        for (int col = 0; col < m_model->columnCount(); ++col) {
            QModelIndex index = m_model->index(row, col);
            QString value = m_model->data(index).toString();
            // Экранируем точки с запятой и кавычки в данных
            if (value.contains(';') || value.contains('"')) {
                value.replace('"', "\"\"");  // Экранируем кавычки
                value = "\"" + value + "\"";
            }
            stream << value;
            if (col < m_model->columnCount() - 1) {
                stream << ";";
            }
        }
        stream << "\n";
    }

    file.close();

    m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
    m_statusBar->showMessage(QString("✅ Отчет за %1 успешно сохранен").arg(dateStr), 3000);
}


// ============================================================
// ОСТАЛЬНЫЕ МЕТОДЫ (БЕЗ ИЗМЕНЕНИЙ)
// ============================================================
void AttendanceEditTab::onTableRowSelected(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous);
    if (current.isValid()) {
        auto* model = dynamic_cast<AttendanceEditTableModel*>(m_model);
        if (model) {
            m_selectedAttendanceId = model->getAttendanceId(current.row());
        }
    } else {
        m_selectedAttendanceId = -1;
    }
}

bool AttendanceEditTab::isAttendanceSelected() const
{
    return m_selectedAttendanceId != -1;
}

void AttendanceEditTab::onDateChanged(const QDate& date)
{
    loadAttendance(date);
}

void AttendanceEditTab::loadAttendance(const QDate& date)
{
    QList<QStringList> attendanceData;

    QString dateStr = date.toString("yyyy-MM-dd");

    QSqlQuery lessonsQuery;
    lessonsQuery.prepare("SELECT id, group_id, discipline_id, teacher_id FROM lessons WHERE lesson_date = ?");
    lessonsQuery.bindValue(0, dateStr);

    QList<int> lessonIds;
    QList<int> groupIds;
    QList<int> disciplineIds;
    QList<int> teacherIds;

    if (lessonsQuery.exec()) {
        while (lessonsQuery.next()) {
            lessonIds.append(lessonsQuery.value(0).toInt());
            groupIds.append(lessonsQuery.value(1).toInt());
            disciplineIds.append(lessonsQuery.value(2).toInt());
            teacherIds.append(lessonsQuery.value(3).toInt());
        }
    }

    if (lessonIds.isEmpty()) {
        if (auto* model = dynamic_cast<AttendanceEditTableModel*>(m_model)) {
            model->setData(attendanceData);
        }
        m_statusBar->showMessage(QString("На %1 нет занятий").arg(date.toString("dd.MM.yyyy")), 2000);
        return;
    }

    for (int i = 0; i < lessonIds.size(); ++i) {
        int lessonId = lessonIds[i];
        int groupId = groupIds[i];
        int disciplineId = disciplineIds[i];
        int teacherId = teacherIds[i];

        QSqlQuery discQuery;
        discQuery.prepare("SELECT name FROM disciplines WHERE id = ?");
        discQuery.bindValue(0, disciplineId);
        QString disciplineName = "Неизвестно";
        if (discQuery.exec() && discQuery.next()) {
            disciplineName = discQuery.value(0).toString();
        }

        QSqlQuery teacherQuery;
        teacherQuery.prepare("SELECT full_name FROM teachers WHERE id = ?");
        teacherQuery.bindValue(0, teacherId);
        QString teacherName = "Неизвестно";
        if (teacherQuery.exec() && teacherQuery.next()) {
            teacherName = teacherQuery.value(0).toString();
        }

        QSqlQuery studentsQuery;
        studentsQuery.prepare("SELECT id, full_name FROM students WHERE group_id = ? ORDER BY full_name");
        studentsQuery.bindValue(0, groupId);

        if (studentsQuery.exec()) {
            while (studentsQuery.next()) {
                int studentId = studentsQuery.value(0).toInt();
                QString studentName = studentsQuery.value(1).toString();

                QSqlQuery attQuery;
                attQuery.prepare("SELECT id, status, comment FROM attendance WHERE student_id = ? AND lesson_id = ?");
                attQuery.bindValue(0, studentId);
                attQuery.bindValue(1, lessonId);

                int attendanceId = -1;
                QString statusText = "Отсутствовал";
                QString comment = "";
                int statusInt = 0;

                if (attQuery.exec() && attQuery.next()) {
                    attendanceId = attQuery.value(0).toInt();
                    statusInt = attQuery.value(1).toInt();
                    comment = attQuery.value(2).toString();
                    if (statusInt == 1) statusText = "Присутствовал";
                    else if (statusInt == 2) statusText = "Опоздал";
                    else statusText = "Отсутствовал";
                } else {
                    QSqlQuery insertAtt;
                    insertAtt.prepare("INSERT INTO attendance (student_id, lesson_id, status, comment) VALUES (?, ?, 0, '')");
                    insertAtt.bindValue(0, studentId);
                    insertAtt.bindValue(1, lessonId);
                    if (insertAtt.exec()) {
                        attendanceId = insertAtt.lastInsertId().toInt();
                    }
                }

                if (attendanceId == -1) continue;

                QStringList row;
                row << studentName
                    << disciplineName
                    << statusText
                    << comment
                    << teacherName
                    << QString::number(attendanceId)
                    << QString::number(studentId);
                attendanceData.append(row);
            }
        }
    }

    if (auto* model = dynamic_cast<AttendanceEditTableModel*>(m_model)) {
        model->setData(attendanceData);
    }

    m_selectedAttendanceId = -1;

    m_statusBar->showMessage(QString("Загружено посещаемость на %1 (%2 записей)")
                                 .arg(date.toString("dd.MM.yyyy"))
                                 .arg(attendanceData.size()), 2000);
}

void AttendanceEditTab::refresh()
{
    loadAttendance(m_dateEdit->date());
}

void AttendanceEditTab::editAttendance()
{
    if (!isAttendanceSelected()) {
        QMessageBox::information(this, "Редактирование посещаемости",
                                 "Для редактирования посещаемости необходимо сначала выбрать запись в таблице.\n\n"
                                 "1. Кликните на строку с нужной записью\n"
                                 "2. Затем нажмите кнопку '✏️ Редактировать'");
        return;
    }

    // Получаем данные для редактирования
    QSqlQuery query;
    query.prepare("SELECT a.status, a.comment, s.full_name, a.student_id FROM attendance a JOIN students s ON a.student_id = s.id WHERE a.id = ?");
    query.bindValue(0, m_selectedAttendanceId);

    if (query.exec() && query.next()) {
        int status = query.value(0).toInt();
        QString comment = query.value(1).toString();
        QString studentName = query.value(2).toString();
        int studentId = query.value(3).toInt();

        EditAttendanceDialog dialog(m_selectedAttendanceId, studentId, studentName, status == 1, comment, this);

        if (dialog.exec() == QDialog::Accepted) {
            bool newStatus = dialog.getNewStatus();
            QString newComment = dialog.getNewComment();

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE attendance SET status = ?, comment = ? WHERE id = ?");
            updateQuery.bindValue(0, newStatus ? 1 : 0);
            updateQuery.bindValue(1, newComment);
            updateQuery.bindValue(2, m_selectedAttendanceId);

            if (updateQuery.exec()) {
                m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
                m_statusBar->showMessage("✏️ Запись успешно обновлена", 3000);
                refresh();

                // ===== ОБНОВЛЯЕМ ВСЕ ВКЛАДКИ С ПОСЕЩАЕМОСТЬЮ =====
                emit attendanceUpdated();  // <-- НОВЫЙ СИГНАЛ
            } else {
                m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
                m_statusBar->showMessage("❌ Ошибка при обновлении записи: " + updateQuery.lastError().text(), 3000);
            }
        }
    }
}

void AttendanceEditTab::deleteAttendance()
{
    if (!isAttendanceSelected()) {
        QMessageBox::information(this, "Удаление записи",
                                 "Для удаления записи необходимо сначала выбрать её в таблице.\n\n"
                                 "1. Кликните на строку с нужной записью\n"
                                 "2. Затем нажмите кнопку '🗑 Удалить'");
        return;
    }

    // Получаем информацию о записи для подтверждения
    QSqlQuery query;
    query.prepare(
        "SELECT s.full_name, d.name, a.status "
        "FROM attendance a "
        "JOIN students s ON a.student_id = s.id "
        "JOIN lessons l ON a.lesson_id = l.id "
        "JOIN disciplines d ON l.discipline_id = d.id "
        "WHERE a.id = ?"
        );
    query.bindValue(0, m_selectedAttendanceId);

    QString lessonInfo;
    if (query.exec() && query.next()) {
        QString studentName = query.value(0).toString();
        QString discipline = query.value(1).toString();
        int status = query.value(2).toInt();
        QString statusText = status == 1 ? "Присутствовал" : status == 2 ? "Опоздал" : "Отсутствовал";
        lessonInfo = QString("Студент: %1\nДисциплина: %2\nСтатус: %3")
                         .arg(studentName, discipline, statusText);
    }

    QMessageBox confirmDialog;
    confirmDialog.setWindowTitle("Подтверждение удаления");
    confirmDialog.setIcon(QMessageBox::Warning);
    confirmDialog.setText("Вы действительно хотите удалить эту запись о посещаемости?");
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
        deleteQuery.prepare("DELETE FROM attendance WHERE id = ?");
        deleteQuery.bindValue(0, m_selectedAttendanceId);

        if (deleteQuery.exec()) {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #2ecc71; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("🗑️ Запись успешно удалена", 3000);
            refresh();

            // ===== ОБНОВЛЯЕМ ВСЕ ВКЛАДКИ С ПОСЕЩАЕМОСТЬЮ =====
            emit attendanceUpdated();  // <-- НОВЫЙ СИГНАЛ
        } else {
            m_statusBar->setStyleSheet("background: #2c3e50; color: #e74c3c; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
            m_statusBar->showMessage("❌ Ошибка при удалении записи: " + deleteQuery.lastError().text(), 3000);
        }
    } else {
        m_statusBar->setStyleSheet("background: #2c3e50; color: #f39c12; font-size: 13px; padding: 3px 8px; border-radius: 4px;");
        m_statusBar->showMessage("ℹ️ Удаление отменено", 2000);
    }
}