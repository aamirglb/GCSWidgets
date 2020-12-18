#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Dial;
class FlapIndicator;
class FuelIndicator;
class QGridLayout;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget      *ui;
    Dial            *m_rpmDial;
    FlapIndicator   *m_flap;
    FuelIndicator   *m_fuel;

    QGridLayout     *m_grid{};

    // Test variables
    int32_t         m_rpm{0};
    int32_t         m_flapValue{0};
};
#endif // WIDGET_H
