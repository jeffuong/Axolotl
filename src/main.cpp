#include "mainwindow.h"
#include "codeeditor.h"

#include <QApplication>
#include <QtWidgets>
//#include <iostream>
//#include <fstream>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	a.setWindowIcon(QIcon(":/imgs/imgs/testimage.png"));

    w.show();

	// show where saved files go
	/*std::ofstream outfile("test.txt");
	outfile << "my text here!" << std::endl;
	outfile.close();*/

    return a.exec();
}
