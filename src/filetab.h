#ifndef FILETAB_H
#define FILETAB_H

#include <QWidget>
#include <QList>
#include <QMenu>

class CodeEditor;
class TabWidget;

class FileTab : public QWidget
{
    Q_OBJECT

public:
    explicit FileTab(TabWidget *tabWidget);

    virtual QMenu* contextMenu() const = 0;
	virtual CodeEditor *currentEditor() const = 0;

    virtual QString title() const = 0;
    virtual QString toolTip() const = 0;

    int index() const; // return tab index in tabwidget, -1 if tab not in tabwidget

public slots:
    void visibilityReq();

signals:
    void titleChange(QString newTitle, QString toolTip);
    void visibilityRequested();

private:
    TabWidget *tabWidg;
};

#endif // FILETAB_H
