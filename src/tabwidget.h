#ifndef TABWIDGET_H
#define TABWIDGET_H

#include "tabbar.h"

#include <QTabWidget>

class MainWindow;
class CodeEditor;
class FileTab;

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
	virtual ~TabWidget() = default;

    int addTab(FileTab *widget, const QString& label);
    int insertTab(int index, FileTab *widget, const QString& label);
    bool removeTab(int index, bool memoryCleared);

    void changeTitle(int index, const QString& newTitle, const QString& toolTip = QString());

    CodeEditor *currentEditor() const;
    FileTab *currentTab() const;

    int editorIndex(CodeEditor *editor) const;
    CodeEditor *editorAt(int index) const;
    FileTab *tabAt(int index) const;

    QList<CodeEditor*> editors() const;
    QList<FileTab*> tabs() const;

    TabBar *tabBar() const;

public slots:
    bool closeTab(int index);
    void closeCurrentTab();
    void closeAllTabs();
    void closeAllButCurrentTab();
    void goNextTab();
    void goPrevTab();

    void tabVisible(FileTab *tab);

protected:
    void createConnections();

private slots:
    void tabRequestedVisibility();

private:
    //void indentTabText(int index); // indent for icons, add later
    void prepareNewTab(int index);

};

inline TabBar *TabWidget::tabBar() const
{
    return static_cast<TabBar*>(QTabWidget::tabBar());
}

#endif // TABWIDGET_H
