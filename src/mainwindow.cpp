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

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->plainTextEdit); // normal editor, no numLines
    this->setCentralWidget(editor); // editor w/ number lines
	setWindowTitle("Notefad");
	

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

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
	editor->setPlainText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    editor->setPlainText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName;

    // if there is no filename, makes one
    if (currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    }
    else
        fileName = currentFile;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = editor->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = editor->toPlainText();
    out << text;
    file.close();
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

QString MainWindow::filePath() const
{
    return currentFile;
}

TabWidget* MainWindow::tabWidget() const 
{
	return tabEditors;
}