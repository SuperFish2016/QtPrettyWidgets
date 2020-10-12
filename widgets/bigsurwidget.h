#ifndef BIGSURSTYLEWIDGET_H
#define BIGSURSTYLEWIDGET_H

#include <QWidget>
#define BG_COLOR QColor(31, 181, 231)
#define SHADOW_COLOR QColor("#444444")
class QPainter;

class BigSurWidget : public QWidget
{
public:
    BigSurWidget(const QColor& backgroundColor = BG_COLOR, const QColor& shadowColor = SHADOW_COLOR, QWidget* parent = 0);
    // The valid range of opacity is from 1.0(completely opaque) to 0.0(completely transparent);
    void setOpacity(float opacity);
    // Set widget background color;
    void setBackgroundColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent*);
private:
    QColor m_backgroundColor;
    float  m_opacity = 1.0;
};

#endif // BIGSURSTYLEWIDGET_H
