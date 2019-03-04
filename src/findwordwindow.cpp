#include "findwordwindow.h"
#include "ui_findwordwindow.h"

FindWordWindow::FindWordWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindWordWindow)
{
    ui->setupUi(this);
	setWindowTitle("Find Word");

	//setting up connection for parent window(MainWindow)
	connect(this, SIGNAL(sendButtonPressTrigger(const QString)), parent, SLOT(buttonPressed(const QString)));
	connect(this, SIGNAL(sendFindWord(const QString)), parent, SLOT(highLightWord(const QString)));
	connect(this, SIGNAL(sendToReplace(const QString, const QString)),
			parent, SLOT(replaceWord(const QString, const QString)));

	//setting up button connection within findwordwindow
	connect(ui->exitButton, &QPushButton::clicked, this, &FindWordWindow::exitOnPress);
	connect(ui->findWordButton, &QPushButton::released, this, &FindWordWindow::findWordOnRelease);
	connect(ui->nextButton, &QPushButton::released, this, &FindWordWindow::nextOnRelease);
	connect(ui->previousButton, &QPushButton::released, this, &FindWordWindow::prevOnRelease);
	connect(ui->replaceAllButton, &QPushButton::released, this, &FindWordWindow::replaceWordOnRelease);
}

FindWordWindow::~FindWordWindow()
{
    delete ui;

}

void FindWordWindow::findWordOnRelease()
{
	emit sendFindWord(ui->wordToFind->toPlainText());
}

void FindWordWindow::replaceWordOnRelease()
{
	emit sendToReplace(ui->wordToFind->toPlainText(), ui->replaceWordText->toPlainText());
}

void FindWordWindow::nextOnRelease()
{
	emit sendButtonPressTrigger("next");
}

void FindWordWindow::prevOnRelease()
{
	emit sendButtonPressTrigger("prev");
}

void FindWordWindow::exitOnPress()
{
	emit sendButtonPressTrigger("exit");
	this->close();
}

void FindWordWindow::setText(const QString &text)
{
	m_Text = text;
}

