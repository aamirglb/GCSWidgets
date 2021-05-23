#include "speedfan.h"
#include <QTimer>
#include <QPainter>
#include <QPainterPath>

using namespace std::literals;

SpeedFan::SpeedFan(QWidget *parent) :
    QWidget(parent),
    m_timer(new QTimer)
{
    m_timer->setInterval(100ms);
    connect(m_timer, &QTimer::timeout, this, &SpeedFan::timerHandler);
    m_timer->start();
}

QSize SpeedFan::sizeHint() const
{
    return QSize(m_width, m_height);
}

QSize SpeedFan::minimumSizeHint() const
{
    return QSize(m_width, m_height);
}

void SpeedFan::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Set (0, 0) at the center of widget
    painter.setViewport(0, 0, m_width+4, m_height+4);
    painter.setWindow((-m_width/2)-2, (-m_height/2)-2, m_width+4, m_height+4);

    painter.setPen(Qt::white);
    painter.drawEllipse((-m_width/2)-2, (-m_height/2)-2, m_width+4, m_height+4);

    painter.save();
    // draw 3 blades at 120 deg offset of each other
    painter.rotate(m_angle * m_direction);
    drawFanBlade(painter, 1);
    drawFanBlade(painter, 2);
    drawFanBlade(painter, 3);
    painter.restore();

//    painter.setPen(Qt::NoPen);
    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::black));
    auto rect = QRectF(-20, -20, 40, 40);
    painter.drawEllipse(rect);

    QFont f = painter.font();
    f.setPixelSize(12);
    f.setBold(true);
    painter.setFont(f);
    if(!m_timeout) {
        painter.setPen(QColor("lime"));
    } else {
        painter.setPen(QColor("gray"));
    }

//    painter.drawText(rect.adjusted(0, -10, 0, 0), Qt::AlignCenter, QString("%1").arg(m_angle));
    painter.drawText(rect.adjusted(0, -10, 0, 0), Qt::AlignCenter, QString("%1").arg(m_speed));
    f.setPixelSize(9);
    painter.setFont(f);
    painter.drawText(rect.adjusted(0, 5, 0, 0), Qt::AlignCenter, QString("\nkts"));
}

void SpeedFan::timerHandler()
{
    m_angle += 9*1;
    if(m_angle >= 360) {
        m_angle = 0;
        m_direction *= -1;
    }
    update();
}

void SpeedFan::setSpeed(int32_t spd)
{
    m_speed = spd;
}

void SpeedFan::setDirection(int32_t dir)
{
    m_direction = dir;
}

void SpeedFan::setTimeout(bool timeout)
{
    m_timeout = timeout;
}

void SpeedFan::drawFanBlade(QPainter &painter, int32_t bladeNo)
{
    painter.save();
    painter.rotate((bladeNo-1)*120);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
//    painter.setBrush(QColor(250, 235, 215));

    QPainterPath myPath;
    myPath.moveTo(QPointF(m_width/2, 0));
    myPath.arcTo(QRect((m_width/2)-40, -20, 40, 40), 0, -90);
    myPath.arcTo(QRect(-10, -10, 20, 20), 270, -180);
    myPath.arcTo(QRect((m_width/2)-40, -20, 40, 40), 90, -90);
    myPath.closeSubpath();
    painter.drawPath(myPath);

    painter.restore();
}
