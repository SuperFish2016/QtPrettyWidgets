#include "bigsurwidget.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>

BigSurWidget::BigSurWidget(const QColor& bgColor, const QColor& shadowColor, QWidget* parent)
    :QWidget(parent), m_backgroundColor(bgColor), m_opacity(1.0)
{
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0);
    effect->setColor(shadowColor);
    effect->setBlurRadius(15);
    this->setGraphicsEffect(effect);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void BigSurWidget::paintEvent(QPaintEvent *e)
{
    m_backgroundColor.setAlpha(m_opacity * 255);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_backgroundColor);
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 10, 10);
    QWidget::paintEvent(e);
}

void BigSurWidget::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    m_backgroundColor.setAlpha(m_opacity * 255);
    update();
}

void BigSurWidget::setOpacity(float o)
{
    m_opacity = o;
    update();
}
