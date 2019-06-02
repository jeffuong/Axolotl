#ifndef FILEDIRECTORY_H
#define FILEDIRECTORY_H

#include <QListView>
#include <QFileSystemModel>

class Filedirectory : public QListView
{
    Q_OBJECT

public:
    explicit Filedirectory(QWidget *parent = 0);

    QFileSystemModel* dmodel();
    QFileSystemModel* fmodel();
	void changePath(const QString& path);
	QString getPath() const;

   ~Filedirectory();

//protected:
    //virtual void keypressEvent(QKeyEvent* event);

//signals:
    //void rootIndexChange(const QModelIndex& index);

private:
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
	QString sPath;
};

#endif // FILEDIRECTORY_H
