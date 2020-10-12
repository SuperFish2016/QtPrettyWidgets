#ifndef CIRCLEICONBUTTON_H
#define CIRCLEICONBUTTON_H
#include <QPushButton>
#include <QColor>
class CircleIconButton : public QPushButton
{
    Q_OBJECT
public:
    CircleIconButton(const QString& iconName, int iconSize = 10,
                 const QSize& buttonSize = QSize(30, 30),
                 const QColor& backgroundColor = QColor(240,240,240),
                 const QColor& checkedBackgroundColor = QColor(0,137,231),
                 const QColor& foregroundColor = QColor(45,45,45),
                 const QColor& checkedForegroundColor = Qt::white,
                 QWidget* parent = nullptr);

    void setOpacity(float opacity);

protected:
    void paintEvent(QPaintEvent* e);

    void enterEvent(QEvent *event);

    void leaveEvent(QEvent *event);

private:
    QColor oriBackgroundColor_;
    QColor oriForegroundColor_;
    QColor backgroundColor_ ;
    QColor checkedBackgroundColor_ ;
    QColor foregroundColor_;
    QColor checkedForegroundColor_;

    float opacity_ = 0.8;
};
#endif // CIRCLEICONBUTTON_H
