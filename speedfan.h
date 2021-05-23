#ifndef SPEEDFAN_H
#define SPEEDFAN_H

#include <QWidget>
class QTimer;

class SpeedFan : public QWidget
{
    Q_OBJECT
public:
    explicit SpeedFan(QWidget *parent = nullptr);

protected:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    void paintEvent(QPaintEvent *event);

public slots:
    void timerHandler();
    void setSpeed(int32_t spd);
    void setDirection(int32_t dir);
    void setTimeout(bool timeout);

signals:

private:
    void drawFanBlade(QPainter &painter, int32_t bladeNo);

private:
    int32_t    m_angle{};
    int32_t    m_speed{};
    int32_t    m_width  {120};
    int32_t    m_height {120};
    int32_t    m_direction{1};
    bool       m_timeout{};
    QTimer     *m_timer;
};

#endif // SPEEDFAN_H
