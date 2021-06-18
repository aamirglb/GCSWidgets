#ifndef WINDDIRDIAL_H
#define WINDDIRDIAL_H

#include <QWidget>
class QTimer;
class WindDirDial : public QWidget
{
    Q_OBJECT
public:
    explicit WindDirDial(QWidget *parent = nullptr);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    void setWidth(int32_t w);
    int32_t getWidth() const;

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void setWindDirection(double dir);

private:
    double    m_windDir{45};
    int32_t   m_width{160};
    int32_t   m_height{m_width};
    int32_t   m_arrowLen{};
    QTimer    *timer;
};

#endif // WINDDIRDIAL_H
