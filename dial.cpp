#include "dial.h"

#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QKeyEvent>

Dial::Dial(int32_t w, int32_t h, QWidget *parent) :
    QWidget(parent),
    m_width(w),
    m_height(h)
{
}

void Dial::setCautionRange(int32_t min, int32_t max)
{
    m_cautionMin = min;
    m_cautionMax = max;
}

void Dial::setCaution1Range(int32_t min, int32_t max)
{
    m_caution1Min = min;
    m_caution1Max = max;
}

void Dial::setWarningRange(int32_t min, int32_t max)
{
    m_warningMin = min;
    m_warningMax = max;
    m_maxValue   = max;
}

void Dial::setNormalRange(int32_t min, int32_t max)
{
    m_normalMin = min;
    m_normalMax = max;
}

void Dial::setRange(int32_t min, int32_t max)
{
    Q_UNUSED(min)
    m_maxValue = max;
}

QSize Dial::sizeHint() const
{
//    return QSize(120*2, 120*2);
    return QSize(m_width*2, (m_height*2)-40);
}

QSize Dial::minimumSizeHint() const
{
    return QSize(m_width*2, (m_height*2)-40);
}

void Dial::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
//    painter.drawRect(0, 0, m_width*2, m_height*2);

    painter.setViewport( m_width/2, m_height/2, m_width*2, m_height*2);
    painter.setWindow(-m_width/2, -m_height/2, m_width*2, m_height*2);

    // TODO: should be made fixed
    // Compute percentage of different arc
//    auto warning1 = m_warningMax - m_warningMin;
//    auto caution1 = m_cautionMax - m_cautionMin;
//    auto normal   = m_normalMax - m_normalMin;
//    auto caution2 = m_caution2Max - m_caution2Min;

    auto arcLen = 360 - 150;
    // compute arc start and end angle for different ranges
    // start angle of the arc is at 3 o'clock
    auto wAngle  = ((m_warningMax - m_warningMin) * arcLen / m_maxValue) + 1;
    auto cAngle  = ((m_cautionMax - m_cautionMin) * arcLen / m_maxValue) + 1;
    auto nAngle  = ((m_normalMax - m_normalMin)   * arcLen / m_maxValue);
    auto c2Angle = ((m_caution1Max - m_caution1Min)   * arcLen / m_maxValue);

    drawFilledArc(&painter,
                  0,
                  wAngle,
                  m_minorRadius,
                  m_majorRadius,
                  "red");

    drawFilledArc(&painter,
                  wAngle,
                  (wAngle + cAngle),
                  m_minorRadius,
                  m_majorRadius,
                  "orange");

    drawFilledArc(&painter,
                  (wAngle + cAngle),
                  (wAngle + cAngle + nAngle),
                  m_minorRadius,
                  m_majorRadius,
                  "lime");

    drawFilledArc(&painter,
                  (wAngle + cAngle + nAngle),
                  (wAngle + cAngle + nAngle + c2Angle),
                  m_minorRadius,
                  m_majorRadius,
                  "orange");

    painter.save();
    painter.rotate(m_angle);
    // Radius of the needle drawn from (0, 0)
    auto radius {m_minorRadius + 5};
    auto needleBaseWidth {5};
    QPainterPath needlePath;
    needlePath.moveTo(0, needleBaseWidth);
    needlePath.lineTo(radius, 0);
    needlePath.lineTo(0, -needleBaseWidth);
    needlePath.lineTo(0, needleBaseWidth);

    painter.setPen(QPen(Qt::NoPen));
    QPalette palette;
    painter.setBrush(palette.brush(QPalette::Active, QPalette::Light));
    painter.drawPath(needlePath);

    // Draw black circle as a hinge for needle
    painter.setBrush(Qt::red);
    painter.drawEllipse(-10, -10, 20, 20);
    painter.restore();

    // draw value text
    QFont f = painter.font();
    f.setPixelSize(static_cast<int32_t>(m_width*0.2));
    f.setBold(true);
    painter.setFont(f);

    QRect rect(5, 15, m_width-15, 20);
    painter.setPen(QPen(getColor(m_value)));
    painter.setBrush(Qt::black);
    painter.drawRect(rect);

    painter.drawText(rect, Qt::AlignRight, QString("%1 ").arg(m_value));
}

void Dial::setValue(int32_t value)
{
    if(m_value != value && value <= m_maxValue) {
        m_value = value;
        m_angle = (150 + (210 * m_value) / m_maxValue) + 1;
        update();
    }
}

void Dial::setRotationAngle(int32_t angle)
{
    if(m_angle != angle) {
        m_angle = angle;
        update();
    }
}

void Dial::drawFilledArc(QPainter *painter, int32_t startAngle,
                         int32_t endAngle, int32_t minRadius,
                         int32_t majRadius, QString color)
{
    // convert deg to radian
    auto start = (startAngle * M_PI) / 180.0;
    auto end   = (endAngle   * M_PI) / 180.0;

    auto minBoundingRect = QRectF(-minRadius, -minRadius, minRadius*2, minRadius*2);
    auto majBoundingRect = QRectF(-majRadius, -majRadius, majRadius*2, majRadius*2);

    QPainterPath arcPath;
    arcPath.moveTo(minRadius * std::cos(-start), minRadius * std::sin(-start));
    arcPath.lineTo(majRadius * std::cos(-start), majRadius * std::sin(-start));

    auto arcLenght = endAngle - startAngle;
    arcPath.arcTo(majBoundingRect, startAngle, arcLenght);
    arcPath.lineTo(minRadius * std::cos(-end), minRadius * std::sin(-end));
    arcPath.arcTo(minBoundingRect, endAngle, -arcLenght);
    arcPath.closeSubpath();

    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QColor(color));
    painter->drawPath(arcPath);
}

QString Dial::getColor(int32_t value)
{
    if(value >= m_caution1Min && value <= m_caution1Max) {
        return "orange";
    } else if( value >= m_normalMin && value <= m_normalMax) {
        return "lime";
    } else if(value >= m_cautionMin && value <= m_cautionMax) {
        return "orange";
    } else if(value >= m_warningMin && value <= m_warningMax) {
        return "red";
    } else {
        return "";
    }
}


