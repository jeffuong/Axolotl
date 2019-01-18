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
    //this->setCentralWidget(editor);

	// setting layout
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(ui->tabWidget);
	centralWidget()->setLayout(layout);

	int windowWidth = settings.value("windowWidth", 700).toInt();
	int windowHeight = settings.value("windowHeight", 500).toInt();
	MainWindow::resize(windowWidth, windowHeight);

	// setting up initial tab
    newTab();
    connect(editor, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
	setupSyntaxHighlighter();
	editor->setFocus();
    highlightCurrentLine();

    currentDir = files.getHomeDir();

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
	LINE HIGHLIGHTER
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
   // if (editor != nullptr)
   // {
        syntaxHighlighter = new SyntaxHighlighter(editor->document());

		QFile file("mainwindow.h");
		if (file.open(QFile::ReadOnly | QFile::Text))
			editor->setPlainText(file.readAll());
   // }
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
        currentDir = files.getDir(currentFile);
    }
}

void MainWindow::save()
{
    if (currentFile == "")
        on_actionSave_as_triggered();
    else
        files.write(currentFile, editor->toPlainText());
}

/*
	MENU ACTIONS & MISC.
*/

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
    QCoreApplication::quit();
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
