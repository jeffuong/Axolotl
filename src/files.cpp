#include "files.h"

#include "QFile"
#include "QDir"
#include "QTextStream"
#include "iostream"

Files::Files()
{
}

QString Files::read(QString fileName)
{
    QString fileContent = "";
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine() + "\n";
            fileContent += line;
        }
    }

    return fileContent;
}

void Files::write(QString fileName, QString fileContents)
{
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << fileContents;
    }
}

QString Files::getHomeDir()
{
    QString homeDir = QDir::homePath();
    return homeDir;
}

QString Files::getDir(QString filePath)
{
    int lastIndex = filePath.lastIndexOf("/");
    filePath.chop(filePath.length() - lastIndex);

    return filePath;
}
