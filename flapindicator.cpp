#include "flapindicator.h"
#include <QPainter>

FlapIndicator::FlapIndicator(QWidget *parent) : QWidget(parent)
{
}

QSize FlapIndicator::sizeHint() const
{
    return QSize(m_width, m_height);
}

QSize FlapIndicator::minimumSizeHint() const
{
    return QSize(m_width, m_height);
}

void FlapIndicator::paintEvent(QPaintEvent * /* event */)
{
#if 0
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setViewport( m_width/2, m_height/2, m_width, m_height);
    painter.setWindow(-m_width/2, -m_height/2, m_width, m_height);
    painter.drawRect(-m_width, -m_height, m_width*2, m_height*2);

    const double x = 0.7;
    const double y = 0.3;
    int32_t length {50};
    int32_t width {20};

    QPalette pal;
    QPainterPath path1;
    QPainterPath path2;

    path1.lineTo(x*length, 0.0);
    path1.lineTo(length, y*length);

    path2.lineTo(x*length, 0.0);
    path2.lineTo(length, -y*length);

    painter.setPen(Qt::NoPen);
    painter.setBrush(pal.brush(QPalette::ColorGroup::Active, QPalette::Light));
//    painter.setBrush(QColor("white"));
    painter.drawPath(path1);
//    painter.setBrush(QColor("white"));
    painter.setBrush(pal.brush(QPalette::ColorGroup::Active, QPalette::Dark));
    painter.drawPath(path2);

#else
    QString s = "F\nL\nA\nP\nS";
    const double DegreesPerMinute = 9.0;
    const int32_t values[] = {20, 10, 0, -10, -20};
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

//    painter.drawRect(0, 0, m_width*2, m_height*2);
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);

    painter.setViewport( m_width/2, m_height/2, m_width, m_height);
    painter.setWindow(-m_width/2, -m_height/2, m_width, m_height);
//    painter.drawRect(-m_width, -m_height, m_width*2, m_height*2);

//    QPen thickPen(palette().foreground(), 4);
//    QPen thinPen(palette().foreground(), 0.5);
    QPen thickPen(Qt::white, 4);
    QPen thinPen(Qt::white, 0.5);

    QColor niceBlue(150, 150, 200);
    painter.setPen(thickPen);
    painter.setBrush(palette().foreground());

    painter.save();
    painter.translate(-20, 0);
    for (int i = 0; i <= 20; ++i) {
        if (i % 5 == 0) {
            painter.setPen(thickPen);
            painter.drawLine(0, -40, 0, -36);
            painter.drawText(-10, -60, 20, 20,
                             Qt::AlignCenter,
                             QString::number(values[i/5]));
        } else {
            painter.setPen(thinPen);
            painter.drawLine(0, -40, 0, -38);
        }
        painter.rotate(DegreesPerMinute);
    }
    painter.restore();

    painter.save();
    painter.translate(-20, 0);
    painter.rotate(DegreesPerMinute * -(m_flapAngle/2));
    // Radius of the needle drawn from (0, 0)
    auto radius {35};
    auto needleBaseWidth {5};
    QPainterPath needlePath;
    needlePath.moveTo(0, needleBaseWidth);
    needlePath.lineTo(radius, 0);
    needlePath.lineTo(0, -needleBaseWidth);
    needlePath.lineTo(0, needleBaseWidth);

    painter.setPen(QPen(Qt::NoPen));    
    painter.setBrush(QBrush(Qt::red));
    painter.drawPath(needlePath);
    painter.restore();

    // Draw black circle as a hinge for needle
    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(-25, -5, 10, 10);

    painter.setPen(QPen(Qt::white));
    painter.drawText(QRect(-55, -45, 20, 90), Qt::AlignCenter, s);


//    painter.save();
//    painter.rotate(11 * -(m_flapAngle/2));
//    QPainterPath cmdTriangle;
//    cmdTriangle.moveTo(35, 0);
//    cmdTriangle.lineTo(45, 5);
//    cmdTriangle.lineTo(45, -5);
//    painter.drawPath(cmdTriangle);
//    painter.restore();
#endif

}

void FlapIndicator::setFlapAngle(int32_t angle)
{
    if(m_flapAngle != angle) {
        m_flapAngle = angle;
        update();
    }
}
