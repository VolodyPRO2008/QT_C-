#include "glwidget.h"
#include <QDebug>

GLWidget::GLWidget(QWidget *parent)
    : QWidget(parent)
    , m_drawMode(0)
    , m_curvature(50.0f)
    , m_rotateX(0.0f)
    , m_rotateY(0.0f)
    , m_angle(45.0f)
    , m_speed(1.0f)
    , m_ballX(0.0f)
    , m_ballY(0.0f)
    , m_ballSpeedX(0.03f)
    , m_ballSpeedY(0.02f)
    , m_ballRadius(0.05f)
    , m_containerSize(0.8f)
{
    setMinimumSize(400, 400);
    setStyleSheet("background-color: #1a1a2e;");

    // Таймер для анимации шарика
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        // Движение шарика с учетом скорости
        float speedFactor = m_speed / 5.0f;
        m_ballX += m_ballSpeedX * speedFactor;
        m_ballY += m_ballSpeedY * speedFactor;

        // Отражение от стенок
        if (m_ballX + m_ballRadius > m_containerSize) {
            m_ballX = m_containerSize - m_ballRadius;
            m_ballSpeedX = -m_ballSpeedX;
        }
        if (m_ballX - m_ballRadius < -m_containerSize) {
            m_ballX = -m_containerSize + m_ballRadius;
            m_ballSpeedX = -m_ballSpeedX;
        }
        if (m_ballY + m_ballRadius > m_containerSize) {
            m_ballY = m_containerSize - m_ballRadius;
            m_ballSpeedY = -m_ballSpeedY;
        }
        if (m_ballY - m_ballRadius < -m_containerSize) {
            m_ballY = -m_containerSize + m_ballRadius;
            m_ballSpeedY = -m_ballSpeedY;
        }

        update();
    });
    m_timer->start(16); // ~60 FPS
}

GLWidget::~GLWidget() {}

void GLWidget::setDrawMode(int mode)
{
    m_drawMode = mode;
    update();
}

void GLWidget::setCurvature(int value)
{
    m_curvature = value;
    update();
}

void GLWidget::setRotateX(int value)
{
    m_rotateX = value;
    update();
}

void GLWidget::setRotateY(int value)
{
    m_rotateY = value;
    update();
}

void GLWidget::setAngle(int value)
{
    m_angle = value;
    update();
}

void GLWidget::setSpeed(int value)
{
    m_speed = value;
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Очищаем фон
    painter.fillRect(rect(), QColor(26, 26, 46));

    if (m_drawMode == 0) {
        drawGraph();
    } else {
        drawBall();
    }
}

// ==================== РИСОВАНИЕ ГРАФИКА ====================

void GLWidget::drawGraph()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    int margin = 60;
    int graphWidth = w - 2 * margin;
    int graphHeight = h - 2 * margin - 40;
    int centerX = w / 2;
    int centerY = h / 2 + 10;

    // Заголовок
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(20, 40, "График функции: y = sin(x) * curvature");
    painter.drawText(20, 65, "Параметр curvature: " + QString::number(m_curvature));

    // Оси координат
    painter.setPen(QPen(Qt::white, 2));

    // Ось X
    painter.drawLine(margin, centerY, w - margin, centerY);
    // Ось Y
    painter.drawLine(centerX, margin, centerX, h - margin);

    // Стрелки
    painter.drawLine(w - margin - 10, centerY - 5, w - margin, centerY);
    painter.drawLine(w - margin - 10, centerY + 5, w - margin, centerY);
    painter.drawLine(centerX - 5, margin + 10, centerX, margin);
    painter.drawLine(centerX + 5, margin + 10, centerX, margin);

    // Подписи осей
    painter.setFont(QFont("Arial", 12));
    painter.drawText(w - margin + 5, centerY + 5, "X");
    painter.drawText(centerX + 5, margin + 5, "Y");
    painter.drawText(centerX + 5, centerY + 20, "0");

    // Значения на осях
    painter.setFont(QFont("Arial", 10));
    painter.setPen(QPen(Qt::gray, 1));

    for (int i = -4; i <= 4; ++i) {
        if (i == 0) continue;
        int x = centerX + i * (graphWidth / 10);
        painter.drawLine(x, centerY - 3, x, centerY + 3);
        painter.drawText(x - 8, centerY + 18, QString::number(i));
    }

    for (int i = -3; i <= 3; ++i) {
        if (i == 0) continue;
        int y = centerY - i * (graphHeight / 8);
        painter.drawLine(centerX - 3, y, centerX + 3, y);
        painter.drawText(centerX - 30, y + 5, QString::number(i));
    }

    // Рисуем график функции
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(Qt::NoBrush);

    QPainterPath path;
    bool first = true;
    float scaleX = graphWidth / 8.0f;
    float scaleY = graphHeight / 6.0f;
    float curvatureScale = m_curvature / 50.0f;

    for (int i = 0; i <= graphWidth; ++i) {
        float x = (i - graphWidth / 2.0f) / scaleX;
        float y = sin(x * 2.0f) * curvatureScale * 0.5f;

        int screenX = margin + i;
        int screenY = centerY - y * scaleY;

        if (first) {
            path.moveTo(screenX, screenY);
            first = false;
        } else {
            path.lineTo(screenX, screenY);
        }
    }
    painter.drawPath(path);

    // Второй график для сравнения (косинус)
    painter.setPen(QPen(Qt::red, 2));
    QPainterPath path2;
    first = true;

    for (int i = 0; i <= graphWidth; ++i) {
        float x = (i - graphWidth / 2.0f) / scaleX;
        float y = cos(x * 2.0f) * curvatureScale * 0.5f;

        int screenX = margin + i;
        int screenY = centerY - y * scaleY;

        if (first) {
            path2.moveTo(screenX, screenY);
            first = false;
        } else {
            path2.lineTo(screenX, screenY);
        }
    }
    painter.drawPath(path2);

    // Легенда
    painter.setPen(QPen(Qt::green, 3));
    painter.drawLine(w - 150, h - 50, w - 120, h - 50);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 11));
    painter.drawText(w - 115, h - 45, "sin(x)");

    painter.setPen(QPen(Qt::red, 2));
    painter.drawLine(w - 150, h - 30, w - 120, h - 30);
    painter.setPen(Qt::white);
    painter.drawText(w - 115, h - 25, "cos(x)");
}

// ==================== РИСОВАНИЕ ШАРИКА ====================

void GLWidget::drawBall()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    int size = qMin(w, h) - 80;
    int startX = (w - size) / 2;
    int startY = (h - size) / 2;

    // Заголовок
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(20, 40, "Движение шарика в замкнутом контуре");
    painter.drawText(20, 65, "Положение: (" +
                                 QString::number(m_ballX, 'f', 2) + ", " +
                                 QString::number(m_ballY, 'f', 2) + ")");
    painter.drawText(20, 90, "Скорость: " + QString::number(m_speed, 'f', 1));

    // Рисуем контейнер (квадрат)
    painter.setPen(QPen(Qt::white, 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(startX, startY, size, size);

    // Преобразуем координаты шарика в экранные
    int ballScreenX = startX + size / 2 + m_ballX * size / 2;
    int ballScreenY = startY + size / 2 - m_ballY * size / 2;
    int ballRadius = size * m_ballRadius;

    // Рисуем шарик с градиентом
    QRadialGradient gradient(ballScreenX - ballRadius/3, ballScreenY - ballRadius/3, ballRadius);
    gradient.setColorAt(0, Qt::yellow);
    gradient.setColorAt(0.5, Qt::red);
    gradient.setColorAt(1, Qt::darkRed);

    painter.setBrush(QBrush(gradient));
    painter.setPen(QPen(Qt::white, 1));
    painter.drawEllipse(ballScreenX - ballRadius, ballScreenY - ballRadius,
                        ballRadius * 2, ballRadius * 2);

    // Блик на шарике
    painter.setBrush(QBrush(QColor(255, 255, 255, 100)));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(ballScreenX - ballRadius/2, ballScreenY - ballRadius/2,
                        ballRadius/2, ballRadius/3);

    // Информация внизу
    painter.setPen(Qt::gray);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(20, h - 20, "Шарик отскакивает от стенок контура");
}