#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

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
    // Цифры
    void onDigitClicked();
    // Операции
    void onAddClicked();
    void onSubtractClicked();
    void onMultiplyClicked();
    void onDivideClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onDecimalClicked();
    void onSignClicked();

private:
    Ui::MainWindow *ui;
    QStack<QString> stack;
    void calculate(const QString& sgn);
};

#endif