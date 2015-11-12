#include "cihandata.h"
#include "cihanlandmark.h"
#include <QDir>
#include <QFile>
#include "opencv2/opencv.hpp"
namespace CihanLib {
CData::CData(QString filepath, QStringList filter)
{
    QFileInfo fileInfo(filepath);
    if (fileInfo.isDir())
        load(filepath, filter);
    else
        __fileList << fileInfo;
    __it = __fileList.begin();
}

CData::CData()
{

}

CData::CData(const CData& other):
    __fileList(other.__fileList),
    __it(other.__it)
{

}

QFileInfoList CData::operator ()() const
{
    return __fileList;
}

QFileInfo CData::operator [](int index) const
{
    return __fileList.value(index);
}

const CData& CData::operator >>(QFileInfo& fileInfo) const
{
    if (!hasNext())
        __it = __fileList.begin();
    fileInfo = *__it;
    ++__it;
    return *this;
}

const CData&CData::operator >>(cv::Mat& image) const
{
    QFileInfo fileInfo;
    *this >> fileInfo;
    image = cv::imread(fileInfo.filePath().toStdString());
    return *this;
}

bool CData::hasNext() const
{
    return __it != __fileList.end();
}

void CData::load(QFileInfo info, QStringList filter)
{
    QDir dir(info.filePath());
    QFileInfoList subdirInfoList = dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    foreach (QFileInfo subdirInfo, subdirInfoList) {
        load(subdirInfo, filter);
    }
    __fileList << dir.entryInfoList(filter, QDir::Files);
}


template <typename type>
const CData&CData::operator >>(type& out) const
{
    QFileInfo fileInfo;
    *this >> fileInfo;
    out = type(fileInfo);
    return *this;
}
}
