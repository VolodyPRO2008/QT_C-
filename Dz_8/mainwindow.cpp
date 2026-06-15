#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFontDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QDateTime>
#include <QPrinter>
#include <QPrintDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , printer(new QPrinter)
{
    ui->setupUi(this);
    setWindowTitle("Текстовый редактор");
    currentFilePath = "";
    showStatusMessage("Готов");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete printer;
}

void MainWindow::showStatusMessage(const QString& msg)
{
    ui->statusbar->showMessage(msg, 2000);
}

// ========== ФАЙЛ ==========
void MainWindow::onNewDocument()
{
    if (!ui->textEdit->document()->isModified() ||
        QMessageBox::question(this, "Новый документ",
                              "Сохранить изменения?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        ui->textEdit->clear();
        currentFilePath = "";
        setWindowTitle("Текстовый редактор");
        showStatusMessage("Новый документ создан");
    } else {
        onSaveDocument();
        ui->textEdit->clear();
        currentFilePath = "";
    }
}

void MainWindow::onOpenDocument()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Открыть файл", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file.close();

    currentFilePath = fileName;
    setWindowTitle("Текстовый редактор - " + fileName);
    showStatusMessage("Файл открыт: " + fileName);
}

void MainWindow::onSaveDocument()
{
    if (currentFilePath.isEmpty()) {
        onSaveAsDocument();
        return;
    }

    QFile file(currentFilePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();

    showStatusMessage("Сохранено: " + currentFilePath);
}

void MainWindow::onSaveAsDocument()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Сохранить как", "", "Текстовые файлы (*.txt)");

    if (fileName.isEmpty()) return;

    currentFilePath = fileName;
    onSaveDocument();
    setWindowTitle("Текстовый редактор - " + fileName);
}

void MainWindow::onPrintDocument()
{
    QPrintDialog dialog(printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        ui->textEdit->print(printer);
        showStatusMessage("Печать завершена");
    }
}

void MainWindow::onExit()
{
    close();
}

// ========== ПРАВКА ==========
void MainWindow::onUndo()
{
    ui->textEdit->undo();
}

void MainWindow::onCopy()
{
    ui->textEdit->copy();
}

void MainWindow::onPaste()
{
    ui->textEdit->paste();
}

void MainWindow::onCut()
{
    ui->textEdit->cut();
}

void MainWindow::onDelete()
{
    ui->textEdit->textCursor().removeSelectedText();
}

void MainWindow::onInsertDateTime()
{
    QString dateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    ui->textEdit->insertPlainText(dateTime);
}

// ========== ВИД ==========
void MainWindow::onFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->font(), this);
    if (ok) {
        ui->textEdit->setFont(font);
    }
}

void MainWindow::onAlignLeft()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::onAlignCenter()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::onAlignRight()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

// ========== НАЙТИ ==========
void MainWindow::onFind()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, "Поиск",
                                               "Найти:", QLineEdit::Normal, "", &ok);

    if (!ok || searchText.isEmpty()) return;

    bool found = ui->textEdit->find(searchText);
    if (!found) {
        QMessageBox::information(this, "Поиск", "Текст не найден");
    }
}

void MainWindow::onReplace()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, "Заменить",
                                               "Найти:", QLineEdit::Normal, "", &ok);

    if (!ok || searchText.isEmpty()) return;

    QString replaceText = QInputDialog::getText(this, "Заменить",
                                                "Заменить на:", QLineEdit::Normal, "", &ok);

    if (!ok) return;

    QString text = ui->textEdit->toPlainText();
    text.replace(searchText, replaceText);
    ui->textEdit->setPlainText(text);
    showStatusMessage("Замена выполнена");
}

void MainWindow::onGoToLine()
{
    bool ok;
    int line = QInputDialog::getInt(this, "Перейти к строке",
                                    "Номер строки:", 1, 1, ui->textEdit->document()->lineCount(), 1, &ok);

    if (ok) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line - 1);
        ui->textEdit->setTextCursor(cursor);
    }
}

// ========== СПРАВКА ==========
void MainWindow::onAbout()
{
    QMessageBox::about(this, "О программе",
                       "Текстовый редактор\n"
                       "Версия 1.0\n"
                       "Разработан в Qt Creator\n"
                       "Возможности:\n"
                       "- Открытие/сохранение файлов\n"
                       "- Печать\n"
                       "- Копирование/вставка\n"
                       "- Поиск и замена\n"
                       "- Настройка шрифта\n"
                       "- Выравнивание текста");
}