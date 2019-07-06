#include "testplugin.h"

QStringList Testplugin::color() const
{
    return {tr("Red"), tr("Green"),
                tr("Blue"), tr("Purple")};
}

QColor Testplugin::changeColor(const QString& colorSelection)
{
    // test func
    qDebug() << "Color change installed.";

    QColor original = QColor(Qt::cyan).lighter(160);
    QColor result = original;

    if (colorSelection == tr("Red"))
        result = QColor(Qt::red).lighter(160);
    if (colorSelection == tr("Green"))
        result = QColor(Qt::green).lighter(160);
    if (colorSelection == tr("Blue"))
        result = QColor(Qt::blue).lighter(160);
    if (colorSelection == tr("Purple"))
        result = QColor(Qt::magenta).lighter(160);

    return result;
}

void Testplugin::dllDebug() const
{
    qDebug() << "Hey, from your dll.";
}

unsigned int Testplugin::version() const
{
    return 101;
}
