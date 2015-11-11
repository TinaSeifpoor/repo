#include "cihandata.h"
#include <QDir>
#include <QFile>
CihanData::CihanData(QString filepath, QStringList filter)
{
    QFileInfo fileInfo(filepath);
    if (fileInfo.isDir())
        load(filepath, filter);
    else
        __fileList << fileInfo;
}

CihanData::CihanData()
{

}

CihanData::CihanData(const CihanData& other):
    __fileList(other.__fileList)
{

}

QFileInfoList CihanData::operator ()() const
{
    return __fileList;
}

QFileInfo CihanData::operator [](int index) const
{
    return __fileList.value(index);
}

void CihanData::load(QFileInfo info, QStringList filter)
{
    QDir dir(info.filePath());
    QFileInfoList subdirInfoList = dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    foreach (QFileInfo subdirInfo, subdirInfoList) {
        load(subdirInfo, filter);
    }
    __fileList << dir.entryInfoList(filter, QDir::Files);
}

