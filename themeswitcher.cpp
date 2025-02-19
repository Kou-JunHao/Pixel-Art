#include "themeswitcher.h"
#include <QFile>
#include <QDir>

ThemeSwitcher::ThemeSwitcher(QObject *parent) : QObject(parent)
{
}

void ThemeSwitcher::switchTheme(const QString &themeName)
{
    QString themePath = QString(":/themes/%1.qss").arg(themeName);
    if (QFile::exists(themePath)) {
        emit themeChanged(themePath);
    }
}
