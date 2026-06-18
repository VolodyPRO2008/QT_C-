#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Лабораторная работа №9: Работа с файлами и папками");
    setMinimumSize(900, 700);
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    // Центральный виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // ========== Верхняя панель с кнопками ==========
    QHBoxLayout *topLayout = new QHBoxLayout;

    btnOpen = new QPushButton("📂 Открыть файл", this);
    btnOpen->setStyleSheet("font-size: 14px; padding: 8px 20px; background-color: #4CAF50; color: white; border-radius: 5px;");

    btnClear = new QPushButton("🗑️ Очистить", this);
    btnClear->setStyleSheet("font-size: 14px; padding: 8px 20px; background-color: #f44336; color: white; border-radius: 5px;");

    labelFileName = new QLabel("Файл не выбран", this);
    labelFileName->setStyleSheet("font-size: 14px; font-weight: bold; color: #2C3E50; padding: 8px;");
    labelFileName->setAlignment(Qt::AlignCenter);

    topLayout->addWidget(btnOpen);
    topLayout->addWidget(btnClear);
    topLayout->addStretch();
    topLayout->addWidget(labelFileName);

    mainLayout->addLayout(topLayout);

    // ========== Информация о файле ==========
    QGroupBox *infoGroup = new QGroupBox("📋 Информация о файле", this);
    infoGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 14px; }");

    textEditInfo = new QTextEdit(this);
    textEditInfo->setReadOnly(true);
    textEditInfo->setStyleSheet("font-size: 13px; background-color: #f8f9fa; font-family: monospace;");
    textEditInfo->setMinimumHeight(120);
    textEditInfo->setPlaceholderText("Здесь будет отображаться информация о файле...");

    QVBoxLayout *infoLayout = new QVBoxLayout;
    infoLayout->addWidget(textEditInfo);
    infoGroup->setLayout(infoLayout);
    mainLayout->addWidget(infoGroup);

    // ========== Содержимое файла ==========
    QGroupBox *contentGroup = new QGroupBox("📄 Содержимое файла", this);
    contentGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 14px; }");

    textEditContent = new QTextEdit(this);
    textEditContent->setReadOnly(true);
    textEditContent->setStyleSheet("font-size: 13px; font-family: monospace; background-color: #ffffff;");
    textEditContent->setPlaceholderText("Здесь будет отображаться содержимое файла...");

    QVBoxLayout *contentLayout = new QVBoxLayout;
    contentLayout->addWidget(textEditContent);
    contentGroup->setLayout(contentLayout);
    mainLayout->addWidget(contentGroup);

    // ========== Подключение сигналов ==========
    connect(btnOpen, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::clearAll);
}

void MainWindow::openFile()
{
    // Открываем диалог выбора файла
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Выберите текстовый файл",
        QDir::homePath(),
        "Текстовые файлы (*.txt);;Все файлы (*.*)"
        );

    if (filePath.isEmpty()) {
        return; // Пользователь отменил выбор
    }

    QFileInfo fileInfo(filePath);

    // Проверяем, существует ли файл
    if (!fileInfo.exists()) {
        QMessageBox::warning(this, "Ошибка", "Файл не существует!");
        return;
    }

    // Проверяем, является ли файл текстовым (по расширению)
    QString suffix = fileInfo.suffix().toLower();
    if (suffix != "txt" && suffix != "log" && suffix != "csv" &&
        suffix != "xml" && suffix != "json" && suffix != "html" &&
        suffix != "cpp" && suffix != "h" && suffix != "py" &&
        suffix != "java" && suffix != "js" && suffix != "css") {

        // Спрашиваем, хотите ли вы открыть не текстовый файл
        int reply = QMessageBox::question(
            this,
            "Предупреждение",
            "Этот файл может не быть текстовым. Открыть его?",
            QMessageBox::Yes | QMessageBox::No
            );
        if (reply == QMessageBox::No) {
            return;
        }
    }

    // Отображаем имя файла
    labelFileName->setText("📁 " + fileInfo.fileName());

    // Отображаем информацию о файле
    displayFileInfo(filePath);

    // Отображаем содержимое файла
    displayFileContent(filePath);
}

void MainWindow::displayFileInfo(const QString &filePath)
{
    QFileInfo fileInfo(filePath);

    QString info;
    info += "📌 Имя файла: " + fileInfo.fileName() + "\n";
    info += "📂 Путь: " + fileInfo.absolutePath() + "\n";
    info += "📏 Размер: " + QString::number(fileInfo.size()) + " байт";

    // Переводим размер в удобочитаемый вид
    if (fileInfo.size() > 1024 * 1024) {
        info += " (" + QString::number(fileInfo.size() / (1024.0 * 1024.0), 'f', 2) + " МБ)";
    } else if (fileInfo.size() > 1024) {
        info += " (" + QString::number(fileInfo.size() / 1024.0, 'f', 2) + " КБ)";
    }
    info += "\n";

    // Дата создания
    info += "📅 Дата создания: " + fileInfo.birthTime().toString("dd.MM.yyyy hh:mm:ss") + "\n";
    info += "🔄 Дата последнего изменения: " + fileInfo.lastModified().toString("dd.MM.yyyy hh:mm:ss") + "\n";
    info += "👁️ Дата последнего доступа: " + fileInfo.lastRead().toString("dd.MM.yyyy hh:mm:ss") + "\n";

    // Атрибуты файла
    info += "🔒 Атрибуты: " + getFileAttributes(fileInfo) + "\n";

    // Расширение
    info += "📎 Расширение: " + (fileInfo.suffix().isEmpty() ? "нет" : fileInfo.suffix()) + "\n";

    // Тип файла
    if (fileInfo.isDir()) {
        info += "📁 Тип: Папка\n";
    } else if (fileInfo.isFile()) {
        info += "📄 Тип: Файл\n";
    }

    // Является ли ссылкой
    if (fileInfo.isSymLink()) {
        info += "🔗 Символическая ссылка на: " + fileInfo.symLinkTarget() + "\n";
    }

    // Является ли исполняемым
    if (fileInfo.isExecutable()) {
        info += "⚡ Исполняемый файл\n";
    }

    textEditInfo->setText(info);
}

void MainWindow::displayFileContent(const QString &filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения!");
        textEditContent->setText("Ошибка: Не удалось открыть файл");
        return;
    }

    // В Qt 6 используем QTextStream без setCodec
    // или читаем напрямую через QByteArray для корректной работы с кодировками
    QByteArray data = file.readAll();
    file.close();

    // Пытаемся декодировать как UTF-8, если не получается - используем локальную кодировку
    QString content = QString::fromUtf8(data);

    // Проверяем, есть ли битые символы
    if (content.contains(QChar::ReplacementCharacter)) {
        // Если есть битые символы, пробуем системную кодировку
        content = QString::fromLocal8Bit(data);
    }

    if (content.isEmpty() && !data.isEmpty()) {
        // Если все равно пусто, показываем как есть (может быть бинарный файл)
        content = "⚠️ Файл содержит бинарные данные или нечитаемый текст";
    }

    // Подсчет строк
    int lineCount = content.count('\n') + 1;
    int charCount = content.length();

    QString header = "📊 Всего строк: " + QString::number(lineCount) +
                     " | Символов: " + QString::number(charCount) + "\n";
    header += "──────────────────────────────────────────────────\n\n";

    if (content.isEmpty() && data.isEmpty()) {
        textEditContent->setText("📄 Файл пуст");
    } else {
        textEditContent->setText(header + content);
    }
}

QString MainWindow::getFileAttributes(const QFileInfo &fileInfo)
{
    QStringList attrs;

    if (fileInfo.isReadable()) {
        attrs << "Чтение";
    }
    if (fileInfo.isWritable()) {
        attrs << "Запись";
    }
    if (fileInfo.isExecutable()) {
        attrs << "Исполнение";
    }
    if (fileInfo.isHidden()) {
        attrs << "Скрытый";
    }
    if (fileInfo.isSymLink()) {
        attrs << "Символическая ссылка";
    }

    return attrs.isEmpty() ? "Нет атрибутов" : attrs.join(", ");
}

void MainWindow::clearAll()
{
    textEditInfo->clear();
    textEditContent->clear();
    labelFileName->setText("Файл не выбран");
}