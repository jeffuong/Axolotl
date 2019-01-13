#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "codeeditor.h"
#include "tabwidget.h"

namespace Ui 
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    QString filePath() const;

	TabWidget* tabWidget() const;
    CodeEditor *editor = new CodeEditor;

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
	TabWidget* tabEditors;
};

#endif // MAINWINDOW_H
