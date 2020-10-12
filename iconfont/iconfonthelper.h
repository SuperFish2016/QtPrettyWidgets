#ifndef FONTAWESOMEICONS_H
#define FONTAWESOMEICONS_H

#include <QFont>
#include <QMap>
#include <QColor>
#include <QPushButton>
#include <QPainter>
#include <QStylePainter>
#include <QDebug>
class IconFontHelper
{
public:
    static IconFontHelper* instance();
    // only label and button are supported for now.
    void setIcon(QWidget* widget, const QString& iconName, int iconSize, const QColor& iconColor = QColor());
private:
    QChar iconUnicode(const QString& iconName);
private:
    IconFontHelper();
    IconFontHelper(const IconFontHelper&) = delete;
    IconFontHelper& operator=(const IconFontHelper&) = delete;

    static IconFontHelper* instance_;
    QFont iconFont_;
public:
    QMap<QString, QString> iconUnicodeMap;
};



#endif // FONTAWESOMEICONS_H
