#ifndef FINDWORDWINDOW_H
#define FINDWORDWINDOW_H

#include <iostream>
#include <vector>

#include <QDialog>
#include <QPushButton>
#include <QString>
#include <QDebug>

namespace Ui {
class FindWordWindow;
}

class FindWordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FindWordWindow(QWidget *parent = nullptr);
	std::vector<unsigned int> findWord(const QString, const QString) const;
    ~FindWordWindow();

public slots:
	void setText(const QString &text);

private slots:
	void findWordOnRelease();
	void exitOnPress();

signals:
	void sendWordPos(const std::vector<unsigned int>);
	void sendFindWord(const QString);
	void sendButtonPressTrigger();

private:
    Ui::FindWordWindow *ui;
	QString m_Text = "";
};

#endif // FINDWORDWINDOW_H
