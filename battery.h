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

#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>
class QTimer;

class Battery : public QWidget
{
    Q_OBJECT
public:
    explicit Battery(QWidget *parent = nullptr);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:

public slots:
    void setValue(int newValue);
    void blink();
    void setBoarderColor(QString color);

protected:
    void paintEvent(QPaintEvent *);

private:
    int32_t   m_width {100};
    int32_t   m_height {40};
    int32_t   m_value {-1};
    bool      m_visible{true};
    QString   m_boarderColor {"white"};
    QTimer    *m_timer {nullptr};
};

#endif // BATTERY_H
