#include "mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Лабораторная работа №11: Введение в OpenGL на Qt");
    setMinimumSize(900, 700);
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // ========== Панель управления ==========
    QGroupBox *controlGroup = new QGroupBox("🎛️ Управление", this);
    QHBoxLayout *controlLayout = new QHBoxLayout;

    QLabel *labelMode = new QLabel("Режим:", this);
    labelMode->setStyleSheet("font-weight: bold;");
    controlLayout->addWidget(labelMode);

    comboMode = new QComboBox(this);
    comboMode->addItems({"📈 График функции", "⚽ Движение шарика"});
    comboMode->setStyleSheet("padding: 5px; font-size: 13px;");
    comboMode->setMinimumWidth(150);
    controlLayout->addWidget(comboMode);

    controlLayout->addSpacing(15);

    QLabel *labelCurv = new QLabel("Кривизна:", this);
    labelCurv->setStyleSheet("font-weight: bold;");
    controlLayout->addWidget(labelCurv);

    sliderCurvature = new QSlider(Qt::Horizontal, this);
    sliderCurvature->setRange(0, 200);
    sliderCurvature->setValue(50);
    sliderCurvature->setFixedWidth(80);
    controlLayout->addWidget(sliderCurvature);

    controlLayout->addSpacing(15);

    QLabel *labelRX = new QLabel("X:", this);
    labelRX->setStyleSheet("font-weight: bold;");
    controlLayout->addWidget(labelRX);

    sliderRotateX = new QSlider(Qt::Horizontal, this);
    sliderRotateX->setRange(0, 360);
    sliderRotateX->setValue(0);
    sliderRotateX->setFixedWidth(60);
    controlLayout->addWidget(sliderRotateX);

    controlLayout->addSpacing(5);

    QLabel *labelRY = new QLabel("Y:", this);
    labelRY->setStyleSheet("font-weight: bold;");
    controlLayout->addWidget(labelRY);

    sliderRotateY = new QSlider(Qt::Horizontal, this);
    sliderRotateY->setRange(0, 360);
    sliderRotateY->setValue(0);
    sliderRotateY->setFixedWidth(60);
    controlLayout->addWidget(sliderRotateY);

    controlLayout->addSpacing(15);

    QLabel *labelAngle = new QLabel("Угол:", this);
    labelAngle->setStyleSheet("font-weight: bold;");
    controlLayout->addWidget(labelAngle);

    sliderAngle = new QSlider(Qt::Horizontal, this);
    sliderAngle->setRange(0, 360);
    sliderAngle->setValue(45);
    sliderAngle->setFixedWidth(60);
    controlLayout->addWidget(sliderAngle);

    controlLayout->addSpacing(15);

    QLabel *labelSpeed = new QLabel("Скорость:", this);
    labelSpeed->setStyleSheet("font-weight: bold;");
    controlLayout->addWidget(labelSpeed);

    sliderSpeed = new QSlider(Qt::Horizontal, this);
    sliderSpeed->setRange(1, 20);
    sliderSpeed->setValue(5);
    sliderSpeed->setFixedWidth(60);
    controlLayout->addWidget(sliderSpeed);

    controlLayout->addStretch();
    controlGroup->setLayout(controlLayout);
    mainLayout->addWidget(controlGroup);

    // ========== Виджет рисования ==========
    glWidget = new GLWidget(this);
    glWidget->setMinimumHeight(500);
    mainLayout->addWidget(glWidget);

    // ========== Статус ==========
    labelStatus = new QLabel("Готов к работе | Режим: График функции", this);
    labelStatus->setStyleSheet("padding: 5px; color: #555;");
    mainLayout->addWidget(labelStatus);

    // ========== Подключение сигналов ==========
    connect(comboMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onModeChanged);

    connect(sliderCurvature, &QSlider::valueChanged,
            this, &MainWindow::onCurvatureChanged);

    connect(sliderRotateX, &QSlider::valueChanged,
            this, &MainWindow::onRotateXChanged);

    connect(sliderRotateY, &QSlider::valueChanged,
            this, &MainWindow::onRotateYChanged);

    connect(sliderAngle, &QSlider::valueChanged,
            this, &MainWindow::onAngleChanged);

    connect(sliderSpeed, &QSlider::valueChanged,
            this, &MainWindow::onSpeedChanged);
}

void MainWindow::onModeChanged(int index)
{
    glWidget->setDrawMode(index);
    labelStatus->setText("Режим: " + comboMode->currentText());
}

void MainWindow::onCurvatureChanged(int value)
{
    glWidget->setCurvature(value);
    labelStatus->setText("Кривизна: " + QString::number(value));
}

void MainWindow::onRotateXChanged(int value)
{
    glWidget->setRotateX(value);
    labelStatus->setText("Поворот X: " + QString::number(value));
}

void MainWindow::onRotateYChanged(int value)
{
    glWidget->setRotateY(value);
    labelStatus->setText("Поворот Y: " + QString::number(value));
}

void MainWindow::onAngleChanged(int value)
{
    glWidget->setAngle(value);
    labelStatus->setText("Угол: " + QString::number(value));
}

void MainWindow::onSpeedChanged(int value)
{
    glWidget->setSpeed(value);
    labelStatus->setText("Скорость: " + QString::number(value));
}