#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "codeeditor.h"

namespace Ui 
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_2_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionFont_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile;
	CodeEditor *editor = new CodeEditor;
};

#endif // MAINWINDOW_H
