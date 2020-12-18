#ifndef DIAL_H
#define DIAL_H

#include <QWidget>
#include <QPixmap>
#include <QPair>

class Dial : public QWidget
{
    Q_OBJECT
public:
    explicit Dial(int32_t w=80, int32_t h=80, QWidget *parent = nullptr);
    using Range = QPair<int32_t, int32_t>;

    void setRange(Range range) { setRange(range.first, range.second); }
    void setRange(int32_t min, int32_t max);

    void setCaution1Range(Range range) {setCaution1Range(range.first, range.second);}
    void setCaution1Range(int32_t min, int32_t max);

    void setCautionRange(Range range) {setCautionRange(range.first, range.second);}
    void setCautionRange(int32_t min, int32_t max);

    void setWarningRange(Range range) {setWarningRange(range.first, range.second);}
    void setWarningRange(int32_t min, int32_t max);

    void setNormalRange(Range range) {setNormalRange(range.first, range.second);}
    void setNormalRange(int32_t min, int32_t max);

    void preRenderFixedItems();

protected:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void paintEvent(QPaintEvent *) override;    

signals:

public slots:
    void setValue(int32_t value);
    void setRotationAngle(int32_t angle);

private:
    void drawFilledArc(QPainter *painter, int32_t startAngle,
                       int32_t endAngle, int32_t minRadius,
                       int32_t majRadius, QString color);
    QString getColor(int32_t value);

private:
    int32_t m_angle       {150};
    int32_t m_value       {};
    int32_t m_maxValue    {100};
    int32_t m_cautionMin  {};
    int32_t m_cautionMax  {};
    int32_t m_warningMin  {};
    int32_t m_warningMax  {};
    int32_t m_normalMin   {};
    int32_t m_normalMax   {};
    int32_t m_caution1Min {0};
    int32_t m_caution1Max {3000};
    int32_t m_width       {120};
    int32_t m_height      {100};
    int32_t m_minorRadius {m_width-25};
    int32_t m_majorRadius {m_width-10};

    QPixmap m_fixedArc;
};

#endif // DIAL_H
