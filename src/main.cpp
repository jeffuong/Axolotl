#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
//#include <iostream>
//#include <fstream>
#include <QIcon>
#include <QSplashScreen>
#include <QTimer>

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

	// show where saved files go
	/*std::ofstream outfile("test.txt");
	outfile << "my text here!" << std::endl;
	outfile.close();*/

    return a.exec();
}
