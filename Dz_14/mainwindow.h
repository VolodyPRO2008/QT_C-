#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPoint>
#include <QTimer>
#include <QList>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QComboBox>
#include <QMessageBox>
#include <QRandomGenerator>
#include <cmath>

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawWidget(QWidget *parent = nullptr);
    // УБИРАЕМ ДЕСТРУКТОР, ТАК КАК ОН НЕ НУЖЕН
    // ~DrawWidget();  // ← УДАЛИТЬ ЭТУ СТРОКУ!

    void setDrawMode(int mode);
    void setNumberCount(int count);
    void generateNumbers();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawClock(QPainter &painter);
    void drawNumbers(QPainter &painter);
    void drawPattern(QPainter &painter);
    void drawGraph(QPainter &painter);

    int m_drawMode;
    int m_numberCount;
    QList<int> m_numbers;
    QTimer *m_timer;
    int m_second;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onModeChanged(int index);
    void onCountChanged(int value);
    void onGenerateClicked();

private:
    void setupUI();

    DrawWidget *drawWidget;
    QComboBox *comboMode;
    QSpinBox *spinCount;
    QPushButton *btnGenerate;
    QLabel *labelStatus;
};

#endif // MAINWINDOW_H