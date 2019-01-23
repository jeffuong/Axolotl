#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "findwordwindow.h"
#include "codeeditor.h"
#include "files.h"

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


signals:
	void sendText(const QString);

private:
    Ui::MainWindow *ui;
    QString currentFile;
    Files files;
    QSettings settings;
    QString currentDir;

	FindWordWindow *findWindow;
	std::vector<unsigned int> m_wordPos;
	void keyPressEvent(QKeyEvent*);
};

#endif // MAINWINDOW_H
