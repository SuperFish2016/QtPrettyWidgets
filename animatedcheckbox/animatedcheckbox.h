#ifndef ANIMATEDCHECKBOX_H
#define ANIMATEDCHECKBOX_H

#include <QCheckBox>

class QLabel;

class AnimatedCheckBox : public QCheckBox {
public:
    AnimatedCheckBox(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *indicator;
};

#endif // ANIMATEDCHECKBOX_H
