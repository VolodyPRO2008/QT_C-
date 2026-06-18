#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFrame>
#include <QScrollArea>
#include <QHeaderView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();

    // Вкладки
    QWidget* createStoriesTab();
    QWidget* createConceptualTab();
    QWidget* createUseCasesTab();
    QWidget* createUserFlowTab();
    QWidget* createScreenMapTab();
    QWidget* createAnswersTab();

    // Вспомогательные методы
    QTableWidget* createTable(const QStringList &headers, const QList<QStringList> &data);
    QFrame* createCard(const QString &title, const QString &desc, const QString &icon = "");
};

#endif // MAINWINDOW_H