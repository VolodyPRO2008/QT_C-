#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void clearAll();

private:
    void setupUI();
    void displayFileInfo(const QString &filePath);
    void displayFileContent(const QString &filePath);
    QString getFileAttributes(const QFileInfo &fileInfo);

    QTextEdit *textEditContent;
    QTextEdit *textEditInfo;
    QPushButton *btnOpen;
    QPushButton *btnClear;
    QLabel *labelFileName;
};

#endif // MAINWINDOW_H