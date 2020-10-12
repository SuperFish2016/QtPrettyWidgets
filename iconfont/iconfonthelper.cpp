#include "iconfonthelper.h"
#include <QMutex>
#include <QFile>
#include <QFileInfo>
#include <QFontDatabase>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
IconFontHelper* IconFontHelper::instance_ = nullptr;
IconFontHelper::IconFontHelper()
{
    QString ttfFile = ":/iconfont/font-awesome.ttf";
    QString cssFile = ":/iconfont/font-awesome.css";
    int fId = QFontDatabase::addApplicationFont(ttfFile);
    QStringList fontFamily = QFontDatabase::applicationFontFamilies(fId);
    Q_ASSERT(fontFamily.size() > 0);
    iconFont_.setFamily(fontFamily.at(0));
    Q_ASSERT(QFileInfo(cssFile).exists());
    QFile fontCssFile(cssFile);
    if(fontCssFile.open(QFile::Text | QFile::ReadOnly))
    {
        while(!fontCssFile.atEnd())
        {
            QString line = fontCssFile.readLine();
            if(line.contains(".fa-") && line.contains(":before"))
            {
                QString nextLine = fontCssFile.readLine();
                if(nextLine.contains("content"))
                {
                    QString key = line.split(':')[0].remove(".fa-");
                    QString content = nextLine.split(':')[1].simplified().remove(";").remove("\"").remove("\\");
                    iconUnicodeMap.insert(key, content);
                }
            }
        }
    }
}

void IconFontHelper::setIcon(QWidget *widget, const QString &iconName, int iconSize, const QColor& iconColor)
{
    iconFont_.setPointSize(iconSize);
    if(widget)
    {
        widget->setFont(iconFont_);
        if(iconColor.isValid())
            widget->setStyleSheet(QString("color:%1").arg(iconColor.name()));
    }
    QLabel* label = qobject_cast<QLabel*>(widget);
    if(label)
    {
        label->setText(iconUnicode(iconName));
    }
    QAbstractButton* button = qobject_cast<QAbstractButton*>(widget);
    if(button)
    {
        button->setText(iconUnicode(iconName));
    }
}

IconFontHelper* IconFontHelper::instance()
{
    if(instance_ == nullptr)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(instance_ == nullptr)
        {
            instance_ = new IconFontHelper;
        }
    }
    return instance_;
}

QChar IconFontHelper::iconUnicode(const QString &iconName)
{
    for(auto iter = iconUnicodeMap.begin(); iter != iconUnicodeMap.end(); iter++)
    {
        if(iter.key() == iconName)
        {
            bool ok;
            QString content = iter.value();
            QChar c = QString(content).toInt(&ok, 16);
            return c;
        }
    }
}
