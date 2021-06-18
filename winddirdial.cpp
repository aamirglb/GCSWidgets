#include "winddirdial.h"
#include <QPainter>
#include <cmath>
#include <QTimer>

WindDirDial::WindDirDial(QWidget *parent) : QWidget(parent)
{
    // Set arrow length to 30% of the width
    m_arrowLen = static_cast<int32_t>(m_width * .3);
    timer = new QTimer;
    connect(timer, &QTimer::timeout, [this, dir=0.0]() mutable {
        this->setWindDirection(dir);
        dir += 1;
    });
//    timer->start(50);
}

QSize WindDirDial::sizeHint() const
{
    return QSize(m_width, m_width);
}

QSize WindDirDial::minimumSizeHint() const
{
    return QSize(m_width, m_width);
}

void WindDirDial::setWidth(int32_t w)
{
    m_width = w;
    m_height = w;
    m_arrowLen = static_cast<int32_t>(m_width * .3);
}

int32_t WindDirDial::getWidth() const
{
    return m_width;
}


void WindDirDial::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);

    painter.setViewport(0, 0, m_width, m_height);
    painter.setWindow(-m_width/2, -m_height/2, m_width, m_height);
//    painter.drawRect(-m_width/2, -m_height/2, m_width, m_height);

    painter.save();
    painter.setBrush(QColor(250, 235, 215));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPointF(0, 0), m_arrowLen, m_arrowLen);
    painter.restore();

    painter.save();
    QPen thickPen(Qt::white, 2);
    QPen thinPen(Qt::white, 0.5);

    painter.setPen(thickPen);
    for(auto i = 0; i < 8; ++i) {
        painter.drawLine(0, -m_arrowLen - 2, 0, -m_arrowLen - 6);
        painter.rotate(45);
    }
    painter.restore();

    painter.save();
    painter.setPen(thinPen);
    for(auto i = 0; i < 72; ++i) {
        painter.rotate(5);
        painter.drawLine(0, -m_arrowLen-2, 0, -m_arrowLen - 4);
    }
    painter.restore();

    painter.setPen(QPen(Qt::white));
    painter.drawText(-10, -m_arrowLen-26, 20, 20, Qt::AlignCenter, "N");
    painter.drawText(-10, m_arrowLen+6,  20, 20, Qt::AlignCenter, "S");
    painter.drawText(m_arrowLen+6, -10, 20, 20, Qt::AlignCenter, "E");
    painter.drawText(-m_arrowLen-26, -10, 20, 20, Qt::AlignCenter, "W");

    painter.setPen(QPen(QColor(200, 100, 30), 4));
    painter.drawEllipse(QPointF(0, 0), m_arrowLen+26, m_arrowLen+26);

    painter.save();
    painter.setPen(Qt::NoPen);
    double x {0.7}, y{0.3};

    // draw arrow now
    QPalette pal;
    painter.rotate(m_windDir);

//    QPainterPath path1;
//    path1.lineTo(x*m_arrowLen, 0.0);
//    path1.lineTo(m_arrowLen, y*m_arrowLen);
//    painter.setBrush(pal.brush(QPalette::ColorGroup::Active, QPalette::Light));
//    painter.drawPath(path1);

//    QPainterPath path2;
//    path2.lineTo(x*m_arrowLen, 0);
//    path2.lineTo(m_arrowLen, -y*m_arrowLen);
//    painter.setBrush(pal.brush(QPalette::ColorGroup::Active, QPalette::Dark));
//    painter.drawPath(path2);

    QPainterPath path3;
    path3.lineTo(0, -x*m_arrowLen);
    path3.lineTo(y*m_arrowLen, -m_arrowLen);
    painter.setBrush(pal.brush(QPalette::ColorGroup::Active, QPalette::Shadow));
    painter.drawPath(path3);

    QPainterPath path4;
    path4.lineTo(0, -x*m_arrowLen);
    path4.lineTo(-y*m_arrowLen, -m_arrowLen);
    painter.setBrush(pal.brush(QPalette::ColorGroup::Active, QPalette::Dark));
    painter.drawPath(path4);

    painter.restore();
}

void WindDirDial::setWindDirection(double dir)
{
    if(abs(m_windDir - dir) > 0.1){
        if(dir < 0) {
            dir += 360;
        }
        m_windDir = dir;
        update();
    }
}
