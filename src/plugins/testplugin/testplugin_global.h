#ifndef TESTPLUGIN_GLOBAL_H
#define TESTPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>
//#include <windows.h>

#if defined(TESTPLUGIN_LIBRARY)
//#ifdef TESTPLUGIN_LIBRARY
#  define TESTPLUGINSHARED_EXPORT Q_DECL_EXPORT
//    #define TESTPLUGINSHARED_EXPORT __declspec(dllexport)
#else
#  define TESTPLUGINSHARED_EXPORT Q_DECL_IMPORT
//    #define TESTPLUGINSHARED_EXPORT __declspec(dllimport)
#endif

#endif // TESTPLUGIN_GLOBAL_H
