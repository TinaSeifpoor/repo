#ifndef COMMON_H
#define COMMON_H
#include <QStringList>
// Constants

//const QStringList imageExtentions() <<
//struct ImageExtentions {
//    ImageExtentions(QStringList extentionList) : extentions(extentions) {}
//    QStringList extentions;
//};
const QStringList extentions = QStringList() << "*.jpg" <<"*.tif";
const QString datasetDescriptorFileName = "data.txt";
const QString instanceUniqueIDHeader = "filename";
const QString classNameHeader = "Scientific Name";
const QString classIDHeader = "label";
const QString instanceUniqueIDSeperatorTakeBetween = "-";
const QString instanceUniqueIDSeperatorTakeEach = ",";
const QString instanceSeperator = "\r\n";
const QString headerSeperator = "\t";
#endif // COMMON_H
