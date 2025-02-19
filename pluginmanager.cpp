#include "pluginmanager.h"
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
}

void PluginManager::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            PluginInterface *pluginInterface = qobject_cast<PluginInterface*>(plugin);
            if (pluginInterface) {
                plugins.append(pluginInterface);
                pluginInterface->initialize();
                qDebug() << "Loaded plugin:" << pluginInterface->name();
            }
        }
    }
}

QStringList PluginManager::availablePlugins() const
{
    QStringList pluginNames;
    foreach (PluginInterface *plugin, plugins) {
        pluginNames.append(plugin->name());
    }
    return pluginNames;
}
