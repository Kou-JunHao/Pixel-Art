#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <QString>

class PluginInterface
{
public:
    virtual ~PluginInterface() = default;
    virtual QString name() const = 0;
    virtual void initialize() = 0;
};

Q_DECLARE_INTERFACE(PluginInterface, "com.pixelartstudio.PluginInterface/1.0")

#endif // PLUGININTERFACE_H
