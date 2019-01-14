#ifndef FILES_H
#define FILES_H

#include "QString"

class Files
{
public:
    Files();

    QString read(QString fileName);
    void write(QString fileName, QString fileContents);

    void openFileManager(QString dir);

    QString getHomeDir();
    QString getDir(QString filePath);
};

#endif // FILES_H
