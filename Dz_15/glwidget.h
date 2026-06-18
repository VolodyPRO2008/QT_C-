#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>  // ← ЭТО НУЖНО ДОБАВИТЬ!
#include <cmath>

class GLWidget : public QWidget  // ← УБРАЛ ЛИШНИЙ * ПОСЛЕ QWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

    void setDrawMode(int mode);
    void setCurvature(int value);
    void setRotateX(int value);
    void setRotateY(int value);
    void setAngle(int value);
    void setSpeed(int value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawGraph();
    void drawBall();

    int m_drawMode;
    float m_curvature;
    float m_rotateX;
    float m_rotateY;
    float m_angle;
    float m_speed;

    // Для шарика
    float m_ballX;
    float m_ballY;
    float m_ballSpeedX;
    float m_ballSpeedY;
    float m_ballRadius;
    float m_containerSize;
    QTimer *m_timer;
};

#endif // GLWIDGET_H