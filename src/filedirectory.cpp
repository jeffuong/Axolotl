#include "filedirectory.h"

#include <QKeyEvent>

Filedirectory::Filedirectory(QWidget *parent) :
	QListView(parent)
{
	sPath = "/home";
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