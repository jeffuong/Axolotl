#include "mainwindow.h"
//#include "plugins\testplugin\testplugin.h"
#include "plugininterfaces.h"

#include <windows.h> 
#include <stdio.h> 
#include <vector>
#include <tchar.h>

#include <QApplication>
#include <QtWidgets>
#include <iostream>
//#include <fstream>
#include <QIcon>
#include <QSplashScreen>
#include <QTimer>

#include <iostream>
#include <fstream>

typedef VOID(*DLLPROC) (LPTSTR);

void getPlugin(std::vector<HINSTANCE>& dll);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/imgs/imgs/axolotl.png"));
	splash->show();

    MainWindow w;

	QTimer::singleShot(2500, splash, SLOT(close()));
	QTimer::singleShot(2500, &w, SLOT(show()));
	//w.show();

	a.setWindowIcon(QIcon(":/imgs/imgs/axolotl.png"));
	w.setWindowTitle("Axolotl");

	// plugin testing

	//https://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll
	//typedef PluginInterfaces* (__cdecl *PluginInterfacesFactory)();

	//HINSTANCE dllHandle = LoadLibrary(TEXT("testplugin.dll"));
	//if (!dllHandle) 
	//{
	//	std::cerr << "Cannot load dll\n";
	//	return 2;
	//}

	//// get function from dll
	//PluginInterfacesFactory factoryFunction = reinterpret_cast<PluginInterfacesFactory>
	//	(GetProcAddress(dllHandle, "version"));
	//if (!factoryFunction)
	//{
	//	std::cerr << "Cannot load function from Testplugin dll\n";
	//	FreeLibrary(dllHandle);
	//	return 1;
	//}

	//// ask factory for a new obj implementing the PluginInterfaces
	//// interface
	//PluginInterfaces* instance = factoryFunction();

	//// play w obj
	//unsigned int ver = instance->version();
	//std::cout << "Version = " << ver << endl;

	//// destroy explicitly 
	//instance->destr();
	//FreeLibrary(dllHandle);

	// ---

	HINSTANCE hinstDLL;
	DLLPROC HelloWorld;
	BOOL fFreeDLL;

	hinstDLL = LoadLibrary("testplugin.dll");

 	//hinstDLL = LoadLibrary(TEXT("C:/Users/Erics/Documents/Notefad/build/src/testplugin.dll"));

	if (!hinstDLL) 
	{
		std::cerr << "Cannot load dll\n";
		system("pause");
		return 2;
	}

	if (hinstDLL != NULL)
	{
		HelloWorld = (DLLPROC)GetProcAddress(hinstDLL, "HelloWorld");

		if (HelloWorld != NULL)
			(HelloWorld);

		fFreeDLL = FreeLibrary(hinstDLL);
	}

	/*std::vector<HINSTANCE> plugin;
	try 
	{
		getPlugin(plugin);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
		system("pause");
		return 1;
	}*/

	// show where saved files go
	/*std::ofstream outfile("test.txt");
	outfile << "my text here!" << std::endl;
	outfile.close();*/

    return a.exec();
}

void getPlugin(std::vector<HINSTANCE>& dll)
{
	WIN32_FIND_DATA fileData;
	HANDLE fileHandle = FindFirstFile(R"(..\plugins\*.dll)", &fileData);

	//check if we could find any plugin
	if (fileHandle == (void*)ERROR_INVALID_HANDLE ||
		fileHandle == (void*)ERROR_FILE_NOT_FOUND)
		std::cout << "There are no plugin\n";
	else
	{
		do
		{
			typedef std::string(__cdecl *NameProc)(void);

			HINSTANCE mod = LoadLibrary((R"(..\plugins)" + std::string(fileData.cFileName)).c_str());

			if (!mod)
			{
				for (HINSTANCE hInst : dll)
					FreeLibrary(hInst);
				throw std::runtime_error("Library" + std::string(fileData.cFileName) + " wasn't loaded successfully!");
			}

			dll.push_back(mod);
		} while (FindNextFile(fileHandle, &fileData));
	}

	FindClose(fileHandle);
}