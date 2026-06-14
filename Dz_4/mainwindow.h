#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QQueue>

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

    void on_buttonStack_clicked();

    void on_buttonQueue_clicked();

private:
    Ui::MainWindow *ui;

    void doStackTask();
    void doQueueTask();

    QString stackToString(QStack<int> stack);
    QString queueToString(QQueue<int> queue);

    QStack<int> myStack;
    QQueue<int> myQueue;
};

#endif