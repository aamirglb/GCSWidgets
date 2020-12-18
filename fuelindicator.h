#ifndef FUELINDICATOR_H
#define FUELINDICATOR_H

#include <QWidget>

class FuelIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FuelIndicator(QWidget *parent = nullptr);
    using Range = std::pair<int32_t, int32_t>;

    void setNormalRange(Range range)  { m_normal = range; }
    void setCautionRange(Range range) { m_caution = range; }
    void setWarningRange(Range range) { m_warning = range; }

protected:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void paintEvent(QPaintEvent *) override;

public slots:
    void setMaxFuel(double maxFuelInKg);
    void setFuel(double fuel);

private:
    QString getColor(double value);

private:
    int32_t   m_width         {120};
    int32_t   m_height        {80};
    double    m_fuel          {50};    // in kg
    double    m_maxFuel       {100};  // in kg
    Range     m_caution;
    Range     m_warning;
    Range     m_normal;
};

#endif // FUELINDICATOR_H
