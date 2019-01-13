#include "filetab.h"
#include "tabwidget.h"

#include <QWidget>

FileTab::FileTab(TabWidget *tabWidget) : QWidget(tabWidget), tabWidg(tabWidget) {}

int FileTab::index() const
{
    return tabWidg == nullptr ? -1 : tabWidg->indexOf(static_cast<QWidget*>(const_cast<FileTab*>(this)));
}

void FileTab::visibilityReq()
{
    emit visibilityRequested();
}
