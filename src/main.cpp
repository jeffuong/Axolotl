#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv) 
{
  QApplication editorApp(argc, argv);
  MainWindow editor; 
  editor.show();
  
  return editorApp.exec();
}
