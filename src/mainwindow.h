#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTabBar>
#include <QLabel>
#include <QDir>
#include <QStringList>

#include "findwordwindow.h"
#include "codeeditor.h"
#include "files.h"
#include "syntaxhighlighter.h"
#include "filedirectory.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
QT_END_NAMESPACE

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
	void setWordPos(const std::vector<unsigned int>&);
	void highLightWord(const QString);

private slots:

    QString getFileType(QString file);
    void newTab();
    void open(QString file);
    void save();
	void followUpActions();
    void highlightCurrentLine();
	//void highlightCurrentLine(const QColor& setColor); // default cyan
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
    void on_actionAbout_Axoltl_triggered();
	void aboutPlugins();
    void on_actionAbout_Plugins_triggered();
	void applyTests();

signals:
	void sendText(const QString);

private:
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
	QLabel *statusBarLabels;
	
	QDir pluginsDir;
	QStringList pluginFileNames;
	QMenu *testerMenu = nullptr;
	QAction *aboutPluginsAct = nullptr;

	typedef void (MainWindow::*Member)();
	void loadPlugins();
	void createTesterMenu();
	void populateMenus(QObject *plugin);
	void addToMenu(QObject *plugin, const QStringList &texts, QMenu *menu,
		Member member);
	QColor lineColor = QColor(Qt::cyan).lighter(160); // plug color testing
};

#endif // MAINWINDOW_H
