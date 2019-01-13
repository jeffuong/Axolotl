#include "tabbar.h"

#include <QMouseEvent>
#include <QStyle>
#include <QToolButton>
#include <QApplication>

TabBar::TabBar(QWidget *parent) : QTabBar(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
}

void TabBar::setTabControl(int index)
{
    auto buttonPosition = static_cast<ButtonPosition>(style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition,
                                                                         nullptr, this));
    auto *closeButton = new QToolButton(this);

    closeButton->setToolTip("Close This Tab");
    closeButton->setText("Close Tab");

    connect(closeButton, &QToolButton::clicked, this, &TabBar::closeTabButton);
    setTabButton(index, buttonPosition, closeButton);
}

void TabBar::closeTabButton()
{
    auto *closeButton = qobject_cast<QAbstractButton*>(sender());
    auto buttonPosition = static_cast<ButtonPosition>(style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition,
                                                                         nullptr, this));

    if (closeButton != nullptr)
    {
        for (int i = 0; i < count(); i++)
        {
            if (tabButton(i, buttonPosition) == closeButton)
                emit tabCloseRequested(i);
        }
    }
}

void TabBar::wheelEvent(QWheelEvent *event)
{
    const int index = currentIndex();
    const int tabCount = count();

    if (tabCount > 1)
    {
        if (event->delta() > 0) // delta for wheel degrees
            // scroll to left tab
            setCurrentIndex(index == 0 ? tabCount - 1 : index - 1);

        else if (event->delta() < 0)
            // scroll to right tab
            setCurrentIndex(index == tabCount - 1 ? 0 : index + 1);
    }
}

void TabBar::mousePressEvent(QMouseEvent *event)
{
    QTabBar::mousePressEvent(event);
    const int tabIndex = tabAt(event->pos());

    // check if clicked on tab or an empty space
    if (tabIndex >= 0)
    {
        if (event->button() == Qt::MouseButton::MiddleButton)
            emit tabCloseRequested(tabIndex);
    }
}

void TabBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    QTabBar::mousePressEvent(event);
    const int tabIndex = tabAt(event->pos());

    if (tabIndex >= 0)
    {
        if (event->button() == Qt::MouseButton::LeftButton + Qt::MouseButton::LeftButton)
            emit tabCloseRequested(tabIndex);

    }
    else if (event->button() == Qt::MouseButton::LeftButton)
        emit emptySpaceDoubleClick();
}









