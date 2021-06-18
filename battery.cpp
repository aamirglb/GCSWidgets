/*
 * Copyright (c) 2019, ADASI
 * All rights reserved.
 * This file contains proprietary information.
 * This file shall not be duplicated, used, modified,
 * or disclosed in whole or in part without
 * the express written consent of ADASI.
 *
 * Author Name: Mohammad Aamir Ali
 * $Id:  $
 * $HeadURL:  $
 * $LastChangedRevision:  $
 * $LastChangedDate:  $
 * $LastChangedBy: $
 */

#include "battery.h"
#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include <QFont>

Battery::Battery(QWidget *parent) : QWidget(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(500);
    connect(m_timer, &QTimer::timeout, this, &Battery::blink);
//    QPalette pal = palette();
//    pal.setColor(QPalette::Background, Qt::white);
//    setAutoFillBackground(true);
//    setPalette(pal);
}

QSize Battery::sizeHint() const
{
    return QSize(m_width, m_height);
}

QSize Battery::minimumSizeHint() const
{
    return QSize(m_width, m_height);
}

void Battery::setValue(int newValue)
{
    if(m_value != newValue)
    {
        m_value = newValue;
        update();
    }

    // Setup blinking
    if( m_value <= 10 )
    {
        m_timer->start();
    }
    else {
        m_timer->stop();
        m_visible = true;
    }
}

void Battery::blink()
{
    if(m_visible)
        m_visible = false;
    else
        m_visible = true;
    update();
}

void Battery::setBoarderColor(QString color)
{
    m_boarderColor = color;
    if(color == "gray" && m_timer->isActive())
    {
        m_visible = true;
        m_timer->stop();
    }
    update();
}

void Battery::paintEvent(QPaintEvent *)
{
    if(!m_visible)
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    QPainterPath path;
    path.addRoundedRect(QRectF(2, 1, m_width-7, m_height-2), 3, 10);
    path.addRoundedRect(QRectF(m_width-5, (m_height/4), 4, (m_height-2)/2), 2, 2);
    painter.setPen(QPen(QColor(m_boarderColor), 2));
    painter.drawPath(path);
    painter.restore();

    if(m_value == -1)
    {
        QFont font = painter.font();
        font.setBold(true);
        font.setPixelSize(11);
        painter.setPen(QPen(Qt::white));
        painter.setFont(font);
        painter.drawText(QRectF(1, 1, m_width, m_height), Qt::AlignCenter, QString("---"));
    }
    else {
        // Map value to percentage, inner rect width is 29
        int32_t fillWidth = (m_value * (m_width - 12)) / 100;
        QColor color;
        if(m_value > 15)
            color = QColor("lime");
        else if(m_value > 10)
            color = QColor("orange");
        else
            color = QColor("red");

        painter.save();
        painter.setPen(QPen(Qt::NoPen));
        painter.setBrush(QBrush(color));
        painter.drawRect(QRectF(4, 4, fillWidth, m_height-8));
        //painter.drawRect(QRectF(3, 3, fillWidth, 14));

//        painter.setBrush(QBrush(Qt::black));
//        painter.drawRect(QRectF(fillWidth+1, 2, 41-fillWidth, 16));
        painter.restore();

        QColor fontColor;
        if(m_value >= 50)
            fontColor = Qt::black;
        else {
            fontColor = Qt::white;
        }
        QFont font = painter.font();
        font.setBold(true);
        font.setPixelSize(10);
        painter.setPen(QPen(fontColor));
//        painter.setPen(QPen(QColor("Orange")));
        painter.setFont(font);
        painter.drawText(QRectF(0, 0, m_width, m_height), Qt::AlignCenter, QString("%1%").arg(m_value));
//        painter.setPen(QPen(Qt::black));
//        painter.drawText(QRectF(2, 1, 40, 16), Qt::AlignCenter, QString("%1%").arg(m_value));

    }
}




