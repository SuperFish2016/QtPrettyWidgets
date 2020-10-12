#include "circleiconbutton.h"
#include "iconfont/iconfonthelper.h"
CircleIconButton::CircleIconButton( const QString& iconName, int iconSize,
                                    const QSize& buttonSize,
                                    const QColor& backgroundColor,
                                    const QColor& checkedBackgroundColor,
                                    const QColor& foregroundColor,
                                    const QColor& checkedFackgroundColor,
                                    QWidget* parent)
      :QPushButton(parent),
      backgroundColor_(backgroundColor),
      checkedBackgroundColor_(checkedBackgroundColor),
      foregroundColor_(foregroundColor),
      checkedForegroundColor_(checkedFackgroundColor)
{
    oriBackgroundColor_ = backgroundColor_;
    oriForegroundColor_ = foregroundColor_;
    setCheckable(true);
    setChecked(false);
    connect(this, &CircleIconButton::clicked, [this](){
        backgroundColor_ = this->isChecked() ? checkedBackgroundColor_ : oriBackgroundColor_;
        foregroundColor_ = this->isChecked() ? checkedForegroundColor_ : oriForegroundColor_;
        update();
    });
    IconFontHelper::instance()->setIcon(this, iconName, iconSize);
    this->setFixedSize(buttonSize);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

void CircleIconButton::setOpacity(float opacity)
{
    opacity_ = opacity;
    update();
}

void CircleIconButton::paintEvent(QPaintEvent* e){
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    backgroundColor_.setAlpha(opacity_ * 255);
    painter.setBrush(backgroundColor_);
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    painter.drawEllipse(rect);
    painter.setPen(foregroundColor_);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, text());
}

void CircleIconButton::enterEvent(QEvent *e){
    if(isChecked())
        return QPushButton::enterEvent(e);
    backgroundColor_ = checkedBackgroundColor_;
    this->update();
    QPushButton::enterEvent(e);
}

void CircleIconButton::leaveEvent(QEvent *e)
{
    if(isChecked())
        return QPushButton::leaveEvent(e);
    backgroundColor_ = oriBackgroundColor_;
    this->update();
    QPushButton::leaveEvent(e);
}
