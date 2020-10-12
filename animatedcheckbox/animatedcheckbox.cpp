#include "AnimatedCheckBox.h"

#include <QStyle>
#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

AnimatedCheckBox::AnimatedCheckBox(QWidget *parent) : QCheckBox (parent) {
    indicator = new QLabel(this);

    this->setMinimumHeight(30);
    this->setContentsMargins(2, 2, 2, 2);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setProperty("class", "AnimatedCheckBox");
    indicator->setProperty("class", "AnimatedCheckBoxIndicator");

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.9);
    indicator->setGraphicsEffect(effect);

    qApp->setStyleSheet(R"(
                        .AnimatedCheckBox[checked=true ] { background: rgb(0,137,231) }
                        .AnimatedCheckBox[checked=false] { background: gray }
                        .AnimatedCheckBoxIndicator { background: rgb(240,240,240) })");

    QPropertyAnimation *animation = new QPropertyAnimation(indicator, "pos", this);
    connect(this, &QCheckBox::toggled, [=] {
        int b = this->contentsMargins().left();
        int x = this->isChecked() ? this->width() - indicator->width() - b : b;
        int y = b;

        animation->stop();
        animation->setDuration(200);
        animation->setEndValue(QPoint(x, y));
        animation->setEasingCurve(QEasingCurve::InOutCubic);
        animation->start();

        this->style()->polish(this);
    });
}

void AnimatedCheckBox::paintEvent(QPaintEvent *) {}

void AnimatedCheckBox::resizeEvent(QResizeEvent *) {
    int b = this->contentsMargins().left();
    int x = this->isChecked() ? this->width() - indicator->width() - b : b;
    int y = b;
    int w = height() - b - b;
    int h = w;
    indicator->setGeometry(x, y, w, h);

    this->setMinimumWidth(height() * 2);

    this->setStyleSheet(QString(".AnimatedCheckBox { border-radius: %1px } .AnimatedCheckBoxIndicator { border-radius: %2px }")
                        .arg(this->height() / 2)
                        .arg(indicator->height() / 2));
}

void AnimatedCheckBox::mousePressEvent(QMouseEvent *event) {
    event->accept();
    setChecked(!isChecked());
}
