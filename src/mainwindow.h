#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTabBar>

#include "findwordwindow.h"
#include "codeeditor.h"
#include "files.h"
#include "syntaxhighlighter.h"
#include "filedirectory.h"

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

public slots:
	void findButtonPressed();
	void setWordPos(const std::vector<unsigned int>);
	void highLightWord(const QString);

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

    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_doubleClicked(const QModelIndex &index);

signals:
	void sendText(const QString);

private:
    void setupSyntaxHighlighter();

    Ui::MainWindow *ui;
    QString currentFile;
    Files files;
    QSettings settings;
    QString currentDir;

	Filedirectory *fileDirectory;
	FindWordWindow *findWindow;
	std::vector<unsigned int> m_wordPos;
	void keyPressEvent(QKeyEvent*);
    SyntaxHighlighter *syntaxHighlighter;
	//QTabBar *tabBar; // can turn tabs to this later on
};

#endif // MAINWINDOW_H
