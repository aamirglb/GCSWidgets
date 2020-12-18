#include "fuelindicator.h"

#include <QPainter>
#include <QtMath>
#include <QDebug>

FuelIndicator::FuelIndicator(QWidget *parent) : QWidget(parent)
{
}

QSize FuelIndicator::sizeHint() const
{
    return QSize(m_width, m_height);
}

QSize FuelIndicator::minimumSizeHint() const
{
    return QSize(m_width, m_height);
}

void FuelIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QBrush(QColor("white")), 2));

//    painter.drawRect(0, 0, m_width, m_height);
    QRectF outerRect(8, 30, 104, 24);
    painter.drawRect(outerRect);
    QPointF indicatorLines[] {
        QPointF(8,   29), QPointF(8,   24), // Empty Indicator
        QPointF(59,  29), QPointF(59,  24), // Half Indicator
        QPointF(112, 29), QPointF(112, 24), // Full Indicator
    };
    painter.drawLines(indicatorLines, 3);

    QFont f = painter.font();
    f.setBold(true);

    f.setPointSizeF(f.pointSize() * 1.25);
    painter.setFont(f);
    painter.drawText(QRectF(0, 5, 20, 20), Qt::AlignCenter, QString("E"));
    painter.drawText(QRectF(104, 5, 20, 20), Qt::AlignCenter, QString("F"));
    f.setPointSizeF(f.pointSize() * 0.7);
    painter.setFont(f);
    painter.drawText(QRectF(40, 5, 40, 20), Qt::AlignCenter, QString("1/2"));

    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor("lime"));
    painter.setBrush(QColor(getColor(m_fuel)));
    double percent = (m_fuel * 100) / m_maxFuel;
    painter.drawRect(10, 32, static_cast<int32_t>(percent), 20);

    f.setPointSizeF(f.pointSize() * 1.5);
    painter.setFont(f);
//    painter.setPen(QPen(QBrush(QColor("white")), 2));
    painter.setPen(QPen(QBrush(QColor(getColor(m_fuel))), 2));
    painter.drawText(QRect(8, 51, 108, 30), Qt::AlignCenter, QString("%1 ").arg(m_fuel, 0, 'f', 1));
    f.setPointSizeF(f.pointSize() * 0.7);
    painter.setFont(f);
    if(m_fuel < 10) {
        painter.drawText(QRect(52, 52, 108-44, 30), Qt::AlignCenter, QString("KG"));
    } else {
        painter.drawText(QRect(62, 52, 108-54, 30), Qt::AlignCenter, QString("KG"));
    }
}

void FuelIndicator::setMaxFuel(double maxFuelInKg)
{
    m_maxFuel = maxFuelInKg;
}

void FuelIndicator::setFuel(double fuel)
{
    if( qFabs(fuel - m_fuel) > 0.01 && fuel <= m_maxFuel) {
        m_fuel = fuel;
        update();
    }
}

QString FuelIndicator::getColor(double value)
{
    if(value >= m_normal.first && value <= m_normal.second) {
        return "lime";
    } else if( value >= m_caution.first && value <= m_caution.second ) {
        return "orange";
    } else if(value >= m_warning.first && value <= m_warning.second) {
        return "red";
    } else {
        return "lime";
    }
}
