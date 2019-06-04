#ifndef FILEDIRECTORY_H
#define FILEDIRECTORY_H

#include <QDialog>
#include <QFileSystemModel>

class Filedirectory : public QDialog
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
