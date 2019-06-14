#include "findwordwindow.h"
#include "ui_findwordwindow.h"

FindWordWindow::FindWordWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindWordWindow)
{
    ui->setupUi(this);
	setWindowTitle("Find Word");

	//setting up connection for parent window(MainWindow)
	connect(this, SIGNAL(sendWordPos(std::vector<unsigned int>)), parent, SLOT(setWordPos(std::vector<unsigned int>)));
	connect(this, SIGNAL(sendButtonPressTrigger()), parent, SLOT(findButtonPressed()));
	connect(this, SIGNAL(sendFindWord(const QString)), parent, SLOT(highLightWord(const QString)));

	//setting up button connection within findwordwindow
	connect(ui->exitButton, &QPushButton::clicked, this, &FindWordWindow::exitOnPress);
	connect(ui->findWordButton, &QPushButton::released, this, &FindWordWindow::findWordOnRelease);
}

FindWordWindow::~FindWordWindow()
{
    delete ui;

}



void FindWordWindow::findWordOnRelease()
{
	//Testing 
	/*std::vector<unsigned int> test = findWord(m_text, ui->wordToFind->toPlainText());
	QString posTest = "";
	for (unsigned int i = 0; i < test.size(); i++)
	{
	posTest.append(QString ::number(test[i]));
	posTest.append(" ");
	}
	ui->wordPosLabel->setText(posTest);*/
	emit sendButtonPressTrigger();
	emit sendWordPos(findWord(m_Text, ui->wordToFind->toPlainText()));
	emit sendFindWord(ui->wordToFind->toPlainText());
}

void FindWordWindow::exitOnPress()
{
	this->close();
}

void FindWordWindow::setText(const QString &text)
{
	m_Text = text;
}



std::vector<unsigned int> FindWordWindow::findWord(const QString textDoc, const QString word) const
{
	std::vector<unsigned int> wordPos;
	for (unsigned int it = 0; it < textDoc.size(); it++)
	{
		unsigned int fristLetterOfWord = it;
		QString tempWord = "";
		while (textDoc.at(it) != ' ' && it != textDoc.size() - 1)
		{
			tempWord.append(textDoc.at(it));
			it++;
		}
		if (it == textDoc.size() - 1)
			tempWord.append(textDoc.at(it));

		qDebug() << tempWord;
		if (word.toLower() == tempWord.toLower())
			wordPos.push_back(fristLetterOfWord);
	}

	return wordPos;
}

