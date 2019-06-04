#include "filedirectory.h"

#include <QKeyEvent>

Filedirectory::Filedirectory(QWidget *parent) :
	QDialog(parent)
{
	// for other OS's, check the link for paths
	// https://doc-snapshots.qt.io/qt5-5.11/qstandardpaths.html

	sPath = "C:/Users/<USER>"; // Windows path, can use "/home" too
	dirModel = new QFileSystemModel(this);
	dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dirModel->setRootPath(sPath);

	fileModel = new QFileSystemModel(this);
	fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
	fileModel->setRootPath(sPath);
}

QFileSystemModel* Filedirectory::dmodel() 
{
	return dirModel;
}

QFileSystemModel* Filedirectory::fmodel() 
{
	return fileModel;
}

void Filedirectory::changePath(const QString& path)
{
	sPath = path;
}

QString Filedirectory::getPath() const
{
	return sPath;
}

Filedirectory::~Filedirectory(){}