#ifndef THEMESWITCHER_H
#define THEMESWITCHER_H

#include <QObject>
#include <QString>

class ThemeSwitcher : public QObject
{
    Q_OBJECT

public:
    explicit ThemeSwitcher(QObject *parent = nullptr);

public slots:
    void switchTheme(const QString &themeName);

signals:
    void themeChanged(const QString &themePath);
};

#endif // THEMESWITCHER_H
