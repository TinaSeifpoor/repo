#include "splitdata.h"
#include <QDir>
#include <QFile>
SplitData::SplitData(QString filepath, QStringList filter)
{
    QFileInfo fileInfo(filepath);
    if (fileInfo.isDir())
        load(filepath, filter);
    else
        __fileList << fileInfo;
}

SplitData::SplitData()
{

}

SplitData::SplitData(const SplitData& other):
    __fileList(other.__fileList)
{

}

QFileInfoList SplitData::operator ()() const
{
    return __fileList;
}

QFileInfo SplitData::operator [](int index) const
{
    return __fileList.value(index);
}

void SplitData::load(QFileInfo info, QStringList filter)
{
    QDir dir(info.filePath());
    QFileInfoList subdirInfoList = dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    foreach (QFileInfo subdirInfo, subdirInfoList) {
        load(subdirInfo, filter);
    }
    __fileList << dir.entryInfoList(filter, QDir::Files);
}

