#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <list>

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


    void on_buttonClear_clicked(); // Очистить

    void on_ButtonPart2_clicked();

    void on_ButtonPart1_clicked();

private:
    Ui::MainWindow *ui;

    void doTask1();                   // Задание 1
    void doTask2();                   // Задание 2

    QString listToStringQList(const QList<int>& list);
    QString listToStringStdList(const std::list<int>& list);

    QList<int> list1;
    QList<int> list2;
    std::list<int> linkedList;
};

#endif