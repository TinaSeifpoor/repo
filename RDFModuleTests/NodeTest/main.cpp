#include <QCoreApplication>
#include <ctime>
#include <QDir>
#include "sourcetest.h"
#include "featurestest.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(time(0));

    FeaturesTest f;
    QDir dir("D:/allPaintings");
    SourceTest s(dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::Unsorted),&f);
    SourceTest* bagged = dynamic_cast<SourceTest*>(s.baggedSamples(0.5,0.5));
    return 0;
}
