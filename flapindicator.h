#ifndef FLAPINDICATOR_H
#define FLAPINDICATOR_H

#include <QWidget>

class FlapIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit FlapIndicator(QWidget *parent = nullptr);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void setFlapAngle(int32_t angle);

private:
    int32_t    m_width  {60};
    int32_t    m_height {60};
    int32_t    m_flapAngle {-10};
};

#endif // FLAPINDICATOR_H
