#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB
#include <QFont>
#include <QFontDialog>
#include <QTabWidget>
#include <QtWidgets>
#include <QHBoxLayout>

CodeEditor *editor = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  currentFile = "";

  ui->setupUi(this);

	int windowWidth = settings.value("windowWidth", 1300).toInt();
	int windowHeight = settings.value("windowHeight", 650).toInt();
	MainWindow::resize(windowWidth, windowHeight);

	// Setting up initial tab
  newTab();
  connect(editor, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
  currentDir = files.getHomeDir();

	// Setting up file directories
	fileDirectory = new Filedirectory(this);
	//Set up for folder directory model
	ui->treeView->setModel(fileDirectory->dmodel());
	QModelIndex index = fileDirectory->dmodel()->index(fileDirectory->getPath(), 0);
	ui->treeView->setRootIndex(index);
	for (int i = 1; i < fileDirectory->dmodel()->columnCount(); i++)
		ui->treeView->hideColumn(i);
	//Set up for file display
	ui->listView->setModel(fileDirectory->fmodel());
	index = fileDirectory->fmodel()->index(fileDirectory->getPath(), 0);
	ui->listView->setRootIndex(index);

	// Setting Up FindWordWindow and Set it connection
	findWindow = new FindWordWindow(this);
	connect(this, SIGNAL(sendText(QString)), findWindow, SLOT(setText(QString)));

	// Setting up for status bar
	statusBarLabels = new QLabel(this);

// Disable menu actions for unavailable features
#if !QT_CONFIG(printer)
    ui->actionPrint->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif
}

MainWindow::~MainWindow()
{
	delete ui;
}

/*
	LINE & SYNTAX HIGHLIGHTING
*/

void MainWindow::highlightCurrentLine()
{
    if (editor != nullptr)
    {
      QList<QTextEdit::ExtraSelection> extraSelections;
      QTextEdit::ExtraSelection selection;

      QColor lineColor = QColor(Qt::cyan).lighter(160);

      selection.format.setBackground(lineColor);
      selection.format.setProperty(QTextFormat::FullWidthSelection, true);
      selection.cursor = editor->textCursor();
      selection.cursor.clearSelection();
      extraSelections.append(selection);

      editor->setExtraSelections(extraSelections);
		  setupSyntaxHighlighter();
    }
}

void MainWindow::setupSyntaxHighlighter()
{
    syntaxHighlighter = new SyntaxHighlighter(editor->document());
}

/*
	TABS
*/

void MainWindow::newTab()
{
	if (ui->tabWidget->count() < 100)
	{
		/* this names tabs as "New File (#)" based on position  
		   rather than number of new files made, fix later */
      ui->tabWidget->addTab(new CodeEditor, 
		  QString("New File %0").arg(ui->tabWidget->count() + 1));
		  ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
		  ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), "");
		  currentFile = "";

		  editor->setWordWrapMode(QTextOption::NoWrap);
	}
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (ui->tabWidget->count() < 2)
        newTab();

    ui->tabWidget->setCurrentIndex(index);

    // sets new current tab
    if (index > 0)
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(index - 1));
    else
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(index + 1));

    delete ui->tabWidget->widget(index);
    currentFile = editor->getFilePath();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    editor = qobject_cast<CodeEditor*>(ui->tabWidget->widget(index));

    connect(editor, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    currentFile = editor->getFilePath();

    highlightCurrentLine();

	  if (currentFile != "")
		    followUpActions();
	  /*else
	  {
		  // implement followUpActions for a no file tab switch
	  }*/
}

/*
	FILES
*/

QString MainWindow::getFileType(QString file)
{
    QStringList dotSplit = file.split(".");

    if (dotSplit.length() > 1)
        return dotSplit.last();
    else
        return "";
}

void MainWindow::open(QString file)
{
    if (file != "")
    {
        if (currentFile != "" || editor->toPlainText() != "")
            newTab();

        currentFile = file;
        QString fileType = getFileType(file);
        editor->setPlainText(files.read(currentFile));
        editor->setFilePath(currentFile);
        editor->setFileType(fileType);

        if (currentFile.length() >= 21)
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), currentFile.right(21));
        else
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), currentFile);

        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), currentFile);

		    followUpActions();
    }
}

void MainWindow::save()
{
    if (currentFile == "")
        on_actionSave_as_triggered();
	  else
	  {
		    files.write(currentFile, editor->toPlainText());
		    ui->statusBar->showMessage("Saved", 2000);
	  }
}

/*
	MENU ACTIONS & MISC.
*/

void MainWindow::followUpActions()
{
	// follow up ui actions for save as, tab changing, open, etc.

	currentDir = files.getDir(currentFile);
	// for folder directory to populate when opening new files
	fileDirectory->changePath(currentDir);
	fileDirectory->dmodel()->setRootPath(currentDir);
	QModelIndex index = fileDirectory->dmodel()->index(fileDirectory->getPath(), 0);
	ui->treeView->setRootIndex(index);

	// not necessary, but keeps the bottom fileDir a bit more consise
	fileDirectory->fmodel()->setRootPath(currentDir);
	index = fileDirectory->fmodel()->index(fileDirectory->getPath(), 0);
	ui->listView->setRootIndex(index);

	// status bar file types (permanent category)
	QString fileType = getFileType(currentFile);
	statusBarLabels->setText(fileType.toUpper());
	ui->statusBar->addPermanentWidget(statusBarLabels);

	// line counts (normal category) 
	// impl later
}

void MainWindow::on_actionNew_triggered()
{
    MainWindow::newTab();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), currentDir, tr("All (*)"));
    open(file);
}

void MainWindow::on_actionSave_triggered()
{
    MainWindow::save();
}

void MainWindow::on_actionSave_as_triggered()
{
    currentFile = QFileDialog::getSaveFileName(this, tr("Save as"), currentDir, tr("ALL (*)"));
    QString fileType = getFileType(currentFile);

    if (currentFile != "")
    {
        files.write(currentFile, editor->toPlainText());

        editor->setFilePath(currentFile);
        editor->setFileType(fileType);

        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), currentFile.right(21));
        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), currentFile);
		
		    ui->statusBar->showMessage("Saved", 2000);

		    followUpActions();
    }
}

void MainWindow::on_actionPrint_triggered()
{
#if QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);

    if (dialog.exec() == QDialog::Rejected)
        return;

#endif // QT_CONFIG(printdialog)
    editor->print(&printDev);
#endif // QT_CONFIG(printer)
}

void MainWindow::on_actionExit_2_triggered()
{
    //QCoreApplication::quit();
	// Changing this to a hide button
	ui->mainToolBar->hide();
}

void MainWindow::on_actionCopy_triggered()
{
#if QT_CONFIG(clipboard)
    editor->copy();
#endif
}

void MainWindow::on_actionPaste_triggered()
{
#if QT_CONFIG(clipboard)
    editor->paste();
#endif
}

void MainWindow::on_actionCut_triggered()
{
#if QT_CONFIG(clipboard)
    editor->cut();
#endif
}

void MainWindow::on_actionUndo_triggered()
{
    editor->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    editor->redo();
}

void MainWindow::on_actionFont_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);

    if (fontSelected)
        editor->setFont(font);
}

void MainWindow::openWith(QString file)
{
	open(file);
}

void MainWindow::keyPressEvent(QKeyEvent* keyInputs)
{

	if (keyInputs->matches(QKeySequence::Find))
		findWindow->show();

}

void MainWindow::findButtonPressed()
{


	emit sendText(editor->toPlainText());
	/*qDebug() << m_wordPos.size();
	if (m_wordPos.size() > 0)
	qDebug() << m_wordPos[0];*/
}

void MainWindow::setWordPos(const std::vector<unsigned int> pos)
{
	m_wordPos = pos;
}

void MainWindow::highLightWord(const QString word)
{
	QList<QTextEdit::ExtraSelection> extraSelections;
	QColor lineColor = QColor(Qt::yellow).lighter(160);
	if (editor != nullptr)
	{
		editor->moveCursor(QTextCursor::Start);
		while (editor->find(word))
		{
			QTextEdit::ExtraSelection selection;
			selection.format.setBackground(lineColor);
			selection.cursor = editor->textCursor();
			extraSelections.append(selection);
		}
	}

	editor->setExtraSelections(extraSelections);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
	QString sPath = fileDirectory->dmodel()->fileInfo(index).absoluteFilePath();
	ui->listView->setRootIndex(fileDirectory->fmodel()->setRootPath(sPath));
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
	QString file = fileDirectory->fmodel()->fileInfo(index).absoluteFilePath();
	open(file);
}