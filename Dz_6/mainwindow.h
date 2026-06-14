#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

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


    void on_buttonProcess_clicked();

    void on_buttonSelectFile_clicked();

private:
    Ui::MainWindow *ui;

    QString sourceFilePath;

    void appendToTextEdit(QTextEdit* textEdit, const QString& text);
};

#endif