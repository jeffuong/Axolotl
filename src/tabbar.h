#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>

class TabBar : public QTabBar
{
    Q_OBJECT

public:
    explicit TabBar(QWidget *parent = nullptr);

    void setTabControl(int index);

    ~TabBar();

private slots:
    void closeTabButton();

private:
    void wheelEvent(QWheelEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void emptySpaceDoubleClick();
};

#endif // TABBAR_H
