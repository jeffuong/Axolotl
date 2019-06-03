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

private:
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
	QString sPath;
};

#endif // FILEDIRECTORY_H
