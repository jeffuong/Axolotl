#include "tabwidget.h"
#include "filetab.h"
#include "mainwindow.h"

#include <QToolButton>
#include <QFile>
#include <QFileInfo>

TabWidget::TabWidget(QWidget* parent) : QTabWidget(parent)
{
    setTabBar(new TabBar(this));
    setUsesScrollButtons(true);
    setMovable(true);
    createConnections();
}

void TabWidget::createConnections()
{
    connect(tabBar(), &TabBar::tabCloseRequested, this, &TabWidget::closeTab);
    //connect(tabBar(), &TabBar::customContextMenuRequested, this, &TabWidget::tabContextMenu);
}

bool TabWidget::removeTab(int index, bool memoryCleared)
{
    auto widg = widget(index);
    bool widgClosed = widg != nullptr &&
                      widg->close();

    if (widgClosed)
    {
        if (memoryCleared)
            widg->deleteLater();
    }

    return widgClosed;
}

bool TabWidget::closeTab(int index)
{
    return removeTab(index, true);
}

void TabWidget::closeCurrentTab()
{
	if (currentIndex() >= 0)
		closeTab(currentIndex());
}

void TabWidget::goNextTab()
{
    // last tab case
    if (currentIndex() == count() - 1)
        setCurrentIndex(0);
    else
       setCurrentIndex(currentIndex() + 1);
}

void TabWidget::goPrevTab()
{
    // first tab case
    if (currentIndex() == 0)
        setCurrentIndex(count() - 1);
    else
        setCurrentIndex(currentIndex() - 1);
}

void TabWidget::closeAllTabs()
{
    for (int i = count() - 1; i >= 0; i--)
        closeTab(i);
}

void TabWidget::closeAllButCurrentTab()
{
    int currntIndex = currentIndex();

    for (int i = count() - 1; i >= 0; i--)
    {
        if (i != currntIndex)
        {
            if (i < currntIndex)
            {
                currntIndex--;
            }
        }

        closeTab(i);
    }
}

CodeEditor *TabWidget::currentEditor() const
{
    return editorAt(currentIndex());
}

FileTab *TabWidget::currentTab() const
{
    return tabAt(currentIndex());
}

int TabWidget::editorIndex(CodeEditor *editor) const
{
    int i = 0;

    for (FileTab *tab : tabs())
    {
        if (tab->currentEditor() == editor)
            return i;
        else
            i++;
    }

    return -1;
}

CodeEditor *TabWidget::editorAt(int index) const
{
    FileTab *tab = tabAt(index);

    return tab != nullptr ? tab->currentEditor() : nullptr;
}

FileTab *TabWidget::tabAt(int index) const
{
    if (index < 0 || index >= count())
        return nullptr;
    else
        return qobject_cast<FileTab*>(widget(index));
}

QList<CodeEditor*> TabWidget::editors() const
{
    QList<CodeEditor*> editors;

    for (int i = 0; i < count(); i++)
    {
        CodeEditor *editrAt = editorAt(i);

        if (editrAt != nullptr)
            editors.append(editrAt);
    }

    return editors;
}

QList<FileTab*> TabWidget::tabs() const {
  QList<FileTab*> tabs;

  for (int i = 0; i < count(); i++) {
    FileTab* tbAt = tabAt(i);

    if (tbAt != nullptr) {
      tabs.append(tbAt);
    }
  }

  return tabs;
}

void TabWidget::tabVisible(FileTab *tab)
{
	if (tab != nullptr)
		setCurrentWidget(tab);
}

void TabWidget::tabRequestedVisibility()
{
    tabVisible(qobject_cast<FileTab*>(sender()));
}

void TabWidget::prepareNewTab(int index)
{
    tabBar()->setTabControl(index);
    //indentTabText(index);
    connect(tabAt(index), &FileTab::visibilityRequested, this, &TabWidget::tabRequestedVisibility);
}

int TabWidget::addTab(FileTab *widget, const QString &label)
{
    const int index = QTabWidget::addTab(widget, label);

    prepareNewTab(index);

    return index;
}

int TabWidget::insertTab(int index, FileTab *widget, const QString &label)
{
    const int tabIndex = QTabWidget::insertTab(index, widget, label);

    prepareNewTab(index);

    return tabIndex;
}

void TabWidget::changeTitle(int index, const QString &newTitle, const QString &toolTip)
{
    setTabText(index, newTitle);
    setTabToolTip(index, toolTip);
    //indentTabText(index);
}


