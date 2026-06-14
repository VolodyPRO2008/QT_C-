#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QString>

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

private:
    Ui::MainWindow *ui;

    void processData();  // Основная логика

    // Множества для хранения рыб
    QSet<QString> lakeFish;      // Все рыбы в озере
    QSet<QString> fisherman1;    // Рыбы первого рыбака
    QSet<QString> fisherman2;    // Рыбы второго рыбака
    QSet<QString> fisherman3;    // Рыбы третьего рыбака

    // Вспомогательные функции
    QString setToString(const QSet<QString>& set);
};

#endif