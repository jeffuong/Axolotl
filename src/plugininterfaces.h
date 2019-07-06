#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>

QT_BEGIN_NAMESPACE
class QWidget;
class QString;
class QStringList;
class QColor;
QT_END_NAMESPACE

class PluginInterfaces
{
public:

	virtual ~PluginInterfaces() {}

	virtual void destr() = 0;
	virtual QStringList color() const = 0;
	virtual QColor changeColor(const QString& colorSelection) = 0;
	virtual void dllDebug() const = 0;
	virtual unsigned int version() const = 0;

};

QT_BEGIN_NAMESPACE
#define PluginInterfaces_iid "test.plugininterfaces"
Q_DECLARE_INTERFACE(PluginInterfaces, PluginInterfaces_iid)
QT_END_NAMESPACE

#endif 