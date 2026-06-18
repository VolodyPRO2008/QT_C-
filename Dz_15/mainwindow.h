#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include <QComboBox>

class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onModeChanged(int index);
    void onCurvatureChanged(int value);
    void onRotateXChanged(int value);
    void onRotateYChanged(int value);
    void onAngleChanged(int value);
    void onSpeedChanged(int value);

private:
    void setupUI();

    GLWidget *glWidget;
    QComboBox *comboMode;
    QSlider *sliderCurvature;
    QSlider *sliderRotateX;
    QSlider *sliderRotateY;
    QSlider *sliderAngle;
    QSlider *sliderSpeed;
    QLabel *labelStatus;
};

#endif // MAINWINDOW_H