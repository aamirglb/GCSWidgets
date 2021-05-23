#include "widget.h"
#include "ui_widget.h"

#include <utility>

#include <QGridLayout>
#include <QPair>
#include <QTimer>

#include "dial.h"
#include "flapindicator.h"
#include "fuelindicator.h"
#include "speedfan.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // set background color
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(25, 35, 45));
//    pal.setColor(QPalette::Foreground, QColor(15, 15, 15));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    m_grid = new QGridLayout;

    // RPM
    m_rpmDial = new Dial;
    m_rpmDial->setRange(0, 1000);
    m_rpmDial->setCaution1Range(0, 100);
    m_rpmDial->setNormalRange(101, 800);
    m_rpmDial->setCautionRange(801, 900);
    m_rpmDial->setWarningRange(901, 1000);

    // Flap
    m_flap = new FlapIndicator;

    // Fuel
    m_fuel = new FuelIndicator;
    auto fullRange = std::make_pair(0, 100);
    m_fuel->setMaxFuel(fullRange.second);
    m_fuel->setNormalRange({0, 70});
    m_fuel->setCautionRange({71, 90});
    m_fuel->setWarningRange({91, 100});

    // SpeedFan
    m_fan = new SpeedFan;

    m_grid->addWidget(m_rpmDial, 0, 0);
    m_grid->addWidget(m_flap,    0, 1);
    m_grid->addWidget(m_fuel,    0, 2);
    m_grid->addWidget(m_fan,     1, 0);
    this->setLayout(m_grid);

    QTimer *timer = new QTimer;
    timer->setInterval(10);

    QObject::connect(timer, &QTimer::timeout, [&, tick=0, delta=1, flapDelta = 1]() mutable {
        ++tick;

        // rpm
        if(m_rpm >= 1000) {
            delta = -1;
        } else if(m_rpm == 0) {
            delta = 1;
        }
        m_rpm += delta;
        m_rpmDial->setValue(m_rpm);

        // fuel
        m_fuel->setFuel(m_rpm * .1);

        // fan
        m_fan->setSpeed(m_rpm * .1);
        
        if( tick % 10 == 0 ) {

            if(m_flapValue > 20)
                flapDelta = -1;
            if(m_flapValue < -20)
                flapDelta = 1;
            m_flapValue += flapDelta;
            m_flap->setFlapAngle(m_flapValue);
        }

    });

    timer->start();

}

Widget::~Widget()
{
    delete ui;
}

