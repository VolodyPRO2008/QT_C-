#include "mainwindow.h"
#include <QPainterPath>
#include <QRandomGenerator>

// ==================== DRAW WIDGET ====================

DrawWidget::DrawWidget(QWidget *parent)
    : QWidget(parent)
    , m_drawMode(0)
    , m_numberCount(5)
    , m_second(0)
{
    setMinimumSize(500, 500);
    setStyleSheet("background-color: white;");

    // Таймер для часов
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        m_second++;
        if (m_second >= 60) m_second = 0;
        update();
    });
    m_timer->start(1000);

    generateNumbers();
}

// УБИРАЕМ ПУСТОЙ ДЕСТРУКТОР - ОН НЕ НУЖЕН!
// (Ошибка была в том, что мы объявили деструктор в .h, но не определили его)

void DrawWidget::setDrawMode(int mode)
{
    m_drawMode = mode;
    update();
}

void DrawWidget::setNumberCount(int count)
{
    m_numberCount = count;
    generateNumbers();
}

void DrawWidget::generateNumbers()
{
    m_numbers.clear();

    // Заполняем числами от 1 до m_numberCount
    for (int i = 1; i <= m_numberCount; ++i) {
        m_numbers.append(i);
    }

    // Перемешиваем случайным образом (Qt 6 способ)
    QRandomGenerator *generator = QRandomGenerator::global();
    for (int i = m_numbers.size() - 1; i > 0; --i) {
        int j = generator->bounded(i + 1);
        m_numbers.swapItemsAt(i, j);
    }

    update();
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    switch (m_drawMode) {
    case 0:
        drawClock(painter);
        break;
    case 1:
        drawNumbers(painter);
        break;
    case 2:
        drawPattern(painter);
        break;
    case 3:
        drawGraph(painter);
        break;
    default:
        break;
    }
}

// ==================== РИСОВАНИЕ ЧАСОВ ====================

void DrawWidget::drawClock(QPainter &painter)
{
    int w = this->width();      // ← ИЗМЕНИЛ width НА w
    int h = this->height();     // ← ИЗМЕНИЛ height НА h
    int centerX = w / 2;
    int centerY = h / 2;
    int radius = qMin(w, h) / 2 - 40;

    // Рисуем циферблат
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(Qt::white));
    painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // Рисуем деления (от 1 до 12)
    painter.setPen(QPen(Qt::black, 2));
    for (int i = 1; i <= 12; ++i) {
        double angle = i * M_PI / 6 - M_PI / 2;
        int x1 = centerX + (radius - 25) * cos(angle);
        int y1 = centerY + (radius - 25) * sin(angle);
        int x2 = centerX + (radius - 10) * cos(angle);
        int y2 = centerY + (radius - 10) * sin(angle);
        painter.drawLine(x1, y1, x2, y2);

        // Цифры
        int xText = centerX + (radius - 40) * cos(angle);
        int yText = centerY + (radius - 40) * sin(angle);
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(xText - 10, yText + 5, QString::number(i));
    }

    // Вычисляем углы для стрелок
    double secondAngle = m_second * M_PI / 30 - M_PI / 2;
    double minuteAngle = (m_second / 60.0) * M_PI / 30 - M_PI / 2;
    double hourAngle = (m_second / 3600.0) * M_PI / 6 - M_PI / 2;

    // Секундная стрелка (красная)
    painter.setPen(QPen(Qt::red, 1));
    int secLen = radius - 30;
    painter.drawLine(centerX, centerY,
                     centerX + secLen * cos(secondAngle),
                     centerY + secLen * sin(secondAngle));

    // Минутная стрелка (черная, толще)
    painter.setPen(QPen(Qt::black, 3));
    int minLen = radius - 50;
    painter.drawLine(centerX, centerY,
                     centerX + minLen * cos(minuteAngle),
                     centerY + minLen * sin(minuteAngle));

    // Часовая стрелка (черная, самая толстая)
    painter.setPen(QPen(Qt::black, 5));
    int hourLen = radius - 70;
    painter.drawLine(centerX, centerY,
                     centerX + hourLen * cos(hourAngle),
                     centerY + hourLen * sin(hourAngle));

    // Центральная точка
    painter.setBrush(QBrush(Qt::black));
    painter.setPen(QPen(Qt::black));
    painter.drawEllipse(centerX - 5, centerY - 5, 10, 10);

    // Подпись
    painter.setPen(QPen(Qt::gray, 1));
    painter.setFont(QFont("Arial", 10));
    painter.drawText(10, h - 10, "Секундная стрелка");
    painter.drawText(10, h - 30, "Минутная стрелка");
    painter.drawText(10, h - 50, "Часовая стрелка");

    // Легенда цветов
    painter.setPen(QPen(Qt::red, 2));
    painter.drawLine(150, h - 20, 170, h - 20);
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(150, h - 40, 170, h - 40);
    painter.setPen(QPen(Qt::black, 5));
    painter.drawLine(150, h - 60, 170, h - 60);
}

// ==================== РИСОВАНИЕ ЧИСЕЛ ====================

void DrawWidget::drawNumbers(QPainter &painter)
{
    int w = this->width();      // ← ИЗМЕНИЛ width НА w
    int h = this->height();     // ← ИЗМЕНИЛ height НА h
    int margin = 60;
    int spacing = 80;
    int startX = margin;
    int startY = h / 2 - 30;

    // Заголовок
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.setPen(QPen(Qt::darkBlue));
    painter.drawText(20, 40, "Случайные числа (перемешанные)");

    // Рисуем числа
    for (int i = 0; i < m_numbers.size(); ++i) {
        int x = startX + i * spacing;
        int y = startY;

        // Квадрат для числа
        painter.setPen(QPen(Qt::blue, 2));
        painter.setBrush(QBrush(Qt::lightGray));
        painter.drawRect(x, y, 50, 50);

        // Само число
        painter.setPen(QPen(Qt::black));
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(x + 15, y + 32, QString::number(m_numbers[i]));
    }

    // Информация внизу
    painter.setPen(QPen(Qt::darkGray));
    painter.setFont(QFont("Arial", 11));
    painter.drawText(20, h - 20,
                     QString("Количество чисел: %1 | Сортировка: случайная")
                         .arg(m_numbers.size()));
}

// ==================== РИСОВАНИЕ УЗОРА ====================

void DrawWidget::drawPattern(QPainter &painter)
{
    int w = this->width();      // ← ИЗМЕНИЛ width НА w
    int h = this->height();     // ← ИЗМЕНИЛ height НА h

    // Заголовок
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.setPen(QPen(Qt::darkBlue));
    painter.drawText(20, 40, "Графический узор из точек");

    // Массив координат для узора (как в методичке)
    int ArrayX[16], ArrayY[16];
    int k;

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            k = 4 * i + j - 4;
            ArrayX[k] = j - 3;
            ArrayY[k] = i - 3;
        }
    }

    ArrayX[2] = 0;
    ArrayY[2] = -3;
    ArrayX[8] = 2;
    ArrayY[8] = 0;
    ArrayX[9] = -3;
    ArrayY[9] = -1;
    ArrayX[15] = -1;
    ArrayY[15] = 2;

    // Рисуем узор
    QPen pen(Qt::blue);
    pen.setWidth(3);
    painter.setPen(pen);

    int centerX = w / 2;
    int centerY = h / 2 + 20;
    int scale = 12;

    for (int i = 1; i <= 16; i++) {
        for (int j = 1; j <= 16; j++) {
            for (int l = 1; l <= 16; l++) {
                int x = centerX + scale * (ArrayX[i] + 4 * ArrayX[j] + ArrayX[l]);
                int y = centerY + scale * (ArrayY[i] + 4 * ArrayY[j] + ArrayY[l]);
                painter.drawPoint(x, y);
            }
        }
    }

    // Информация
    painter.setPen(QPen(Qt::darkGray));
    painter.setFont(QFont("Arial", 11));
    painter.drawText(20, h - 20,
                     QString("Узор из точек | Всего точек: %1").arg(16 * 16 * 16));
}

// ==================== РИСОВАНИЕ ГРАФИКА ФУНКЦИИ ====================

void DrawWidget::drawGraph(QPainter &painter)
{
    int w = this->width();      // ← ИЗМЕНИЛ width НА w
    int h = this->height();     // ← ИЗМЕНИЛ height НА h
    int margin = 60;
    int graphWidth = w - 2 * margin;
    int graphHeight = h - 2 * margin - 40;
    int centerY = h / 2 + 20;

    // Заголовок
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.setPen(QPen(Qt::darkBlue));
    painter.drawText(20, 40, "График тригонометрической функции y = sin(x)");

    // Оси координат
    painter.setPen(QPen(Qt::black, 2));

    // Ось X
    painter.drawLine(margin, centerY, w - margin, centerY);

    // Ось Y
    painter.drawLine(margin, margin, margin, h - margin - 40);

    // Стрелки на осях
    painter.drawLine(w - margin - 10, centerY - 5, w - margin, centerY);
    painter.drawLine(w - margin - 10, centerY + 5, w - margin, centerY);
    painter.drawLine(margin - 5, margin + 10, margin, margin);
    painter.drawLine(margin + 5, margin + 10, margin, margin);

    // Подписи осей
    painter.setFont(QFont("Arial", 12));
    painter.drawText(w - margin + 5, centerY + 5, "X");
    painter.drawText(margin - 20, margin - 5, "Y");

    // Значения на оси X
    painter.setFont(QFont("Arial", 10));
    for (int i = -4; i <= 4; ++i) {
        if (i == 0) continue;
        int x = margin + graphWidth / 2 + i * (graphWidth / 8);
        painter.drawLine(x, centerY - 5, x, centerY + 5);
        painter.drawText(x - 10, centerY + 20, QString::number(i));
    }
    painter.drawText(margin + graphWidth / 2 - 5, centerY + 20, "0");

    // Значения на оси Y
    for (int i = -2; i <= 2; ++i) {
        if (i == 0) continue;
        int y = centerY - i * (graphHeight / 4);
        painter.drawLine(margin - 5, y, margin + 5, y);
        painter.drawText(margin - 30, y + 5, QString::number(i * -1));
    }

    // Рисуем график sin(x)
    painter.setPen(QPen(Qt::red, 3));
    painter.setBrush(QBrush(Qt::NoBrush));

    QPainterPath path;
    bool first = true;

    for (int i = 0; i <= graphWidth; ++i) {
        double x = (i - graphWidth / 2.0) * (8.0 / graphWidth) * M_PI;
        double y = sin(x);

        int screenX = margin + i;
        int screenY = centerY - y * (graphHeight / 2.5);

        if (first) {
            path.moveTo(screenX, screenY);
            first = false;
        } else {
            path.lineTo(screenX, screenY);
        }
    }

    painter.drawPath(path);

    // График cos(x) для сравнения
    painter.setPen(QPen(Qt::blue, 2));
    painter.setBrush(QBrush(Qt::NoBrush));

    QPainterPath path2;
    first = true;

    for (int i = 0; i <= graphWidth; ++i) {
        double x = (i - graphWidth / 2.0) * (8.0 / graphWidth) * M_PI;
        double y = cos(x);

        int screenX = margin + i;
        int screenY = centerY - y * (graphHeight / 2.5);

        if (first) {
            path2.moveTo(screenX, screenY);
            first = false;
        } else {
            path2.lineTo(screenX, screenY);
        }
    }

    painter.drawPath(path2);

    // Легенда
    painter.setPen(QPen(Qt::red, 3));
    painter.drawLine(w - 150, h - 50, w - 120, h - 50);
    painter.setPen(QPen(Qt::black));
    painter.setFont(QFont("Arial", 11));
    painter.drawText(w - 115, h - 45, "sin(x)");

    painter.setPen(QPen(Qt::blue, 2));
    painter.drawLine(w - 150, h - 30, w - 120, h - 30);
    painter.setPen(QPen(Qt::black));
    painter.drawText(w - 115, h - 25, "cos(x)");
}

// ==================== MAIN WINDOW ====================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Лабораторная работа №10: Графика и алгоритмы в Qt");
    setMinimumSize(700, 600);
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
    comboMode->addItems({
        "⏰ Аналоговые часы",
        "🔢 Случайные числа",
        "🎨 Узор из точек",
        "📈 График функции"
    });
    comboMode->setStyleSheet("padding: 5px; font-size: 13px;");
    comboMode->setMinimumWidth(180);
    controlLayout->addWidget(comboMode);

    controlLayout->addSpacing(20);

    QLabel *labelCount = new QLabel("Количество чисел:", this);
    labelCount->setStyleSheet("font-weight: bold;");
    controlLayout->addWidget(labelCount);

    spinCount = new QSpinBox(this);
    spinCount->setRange(3, 20);
    spinCount->setValue(5);
    spinCount->setStyleSheet("padding: 5px;");
    controlLayout->addWidget(spinCount);

    controlLayout->addSpacing(20);

    btnGenerate = new QPushButton("🔄 Сгенерировать", this);
    btnGenerate->setStyleSheet("padding: 8px 20px; background-color: #4CAF50; color: white; border-radius: 5px; font-weight: bold;");
    controlLayout->addWidget(btnGenerate);

    controlLayout->addStretch();
    controlGroup->setLayout(controlLayout);
    mainLayout->addWidget(controlGroup);

    // ========== Область рисования ==========
    drawWidget = new DrawWidget(this);
    drawWidget->setMinimumHeight(500);
    mainLayout->addWidget(drawWidget);

    // ========== Статус ==========
    labelStatus = new QLabel("Готов к работе", this);
    labelStatus->setStyleSheet("padding: 5px; color: #555;");
    mainLayout->addWidget(labelStatus);

    // ========== Подключение сигналов ==========
    connect(comboMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onModeChanged);

    connect(spinCount, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onCountChanged);

    connect(btnGenerate, &QPushButton::clicked,
            this, &MainWindow::onGenerateClicked);
}

void MainWindow::onModeChanged(int index)
{
    drawWidget->setDrawMode(index);
    labelStatus->setText("Режим: " + comboMode->currentText());
}

void MainWindow::onCountChanged(int value)
{
    drawWidget->setNumberCount(value);
    labelStatus->setText("Количество чисел изменено: " + QString::number(value));
}

void MainWindow::onGenerateClicked()
{
    drawWidget->generateNumbers();
    labelStatus->setText("Числа сгенерированы! Количество: " +
                         QString::number(spinCount->value()));
}