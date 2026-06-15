#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Файл
    void onNewDocument();
    void onOpenDocument();
    void onSaveDocument();
    void onSaveAsDocument();
    void onPrintDocument();
    void onExit();

    // Правка
    void onUndo();
    void onCopy();
    void onPaste();
    void onCut();
    void onDelete();
    void onInsertDateTime();

    // Вид
    void onFont();
    void onAlignLeft();
    void onAlignCenter();
    void onAlignRight();

    // Найти
    void onFind();
    void onReplace();
    void onGoToLine();

    // Справка
    void onAbout();

private:
    Ui::MainWindow *ui;
    QString currentFilePath;
    QPrinter *printer;

    void showStatusMessage(const QString& msg);
};

#endif