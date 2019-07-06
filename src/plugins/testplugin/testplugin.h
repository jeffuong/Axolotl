#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include "testplugin_global.h"
#include "../../plugininterfaces.h"

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QColor>

class Testplugin : public QObject, public PluginInterfaces
//class TESTPLUGINSHARED_EXPORT Testplugin : public QObject, public PluginInterfaces
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "test.plugininterfaces" FILE "testplugin.json")
    Q_INTERFACES(PluginInterfaces)

public:
    ~Testplugin() override {}

    void destr() override { delete this; }
    QStringList color() const override;
    QColor changeColor(const QString& colorSelection) override;
    void dllDebug() const override;
    unsigned int version() const override;

};

//extern "C" TESTPLUGINSHARED_EXPORT PluginInterfaces* APIENTRY getTestplugin()
//{
//    PluginInterfaces* p = new Testplugin;
//
//    return p;
//}

//extern "C" __declspec(dllexport) PluginInterfaces* __cdecl create_TestPlugins()
//{
//    return new Testplugin;
//}

#endif // TESTPLUGIN_H
