#include <QCoreApplication>
#include "sourcetest.h"
//#include "featuretest.h"

#include <ctime>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(time(0));
//    FeatureTest f;
    SourceTest s(QFileInfoList());

    return 0;
}
