#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QStringList>
#include "plugininterface.h"

class PluginManager : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject *parent = nullptr);
    void loadPlugins();
    QStringList availablePlugins() const;

private:
    QList<PluginInterface*> plugins;
};

#endif // PLUGINMANAGER_H
