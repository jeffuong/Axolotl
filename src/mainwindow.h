#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTabBar>

#include "codeeditor.h"
#include "files.h"
#include "syntaxhighlighter.h"

namespace Ui 
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void openWith(QString);
    ~MainWindow();

private slots:

    QString getFileType(QString file);

    void newTab();

    void open(QString file);

    void save();

    void highlightCurrentLine();

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

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

private:
    void setupSyntaxHighlighter();

    Ui::MainWindow *ui;
    QString currentFile;
    Files files;
    QSettings settings;
    QString currentDir;
    SyntaxHighlighter *syntaxHighlighter;
	//QTabBar *tabBar; // can turn tabs to this later on
};

#endif // MAINWINDOW_H
