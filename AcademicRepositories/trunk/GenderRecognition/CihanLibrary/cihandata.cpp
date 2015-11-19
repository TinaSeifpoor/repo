#include "cihandata.h"
#include "cihanlandmark.h"
#include <QDir>
#include <QFile>
#include "opencv2/opencv.hpp"
class CDataPrivate
{
public:
    QFileInfoList __fileList;
    QFileInfoList::const_iterator __it;
};
namespace CihanLib {

CData::CData(QString filepath, QStringList filter):
    d(new CDataPrivate())
{
    QFileInfo fileInfo(filepath);
    if (fileInfo.isDir())
        load(filepath, filter);
    else
        d->__fileList << fileInfo;
    d->__it = d->__fileList.begin();
}

QList<CData> CData::multiData(int argc, const char* argv[])
{
    QList<CData> multiCData;
    for (int i=1; i<argc;++i) {
        multiCData << CData(argv[i]);
    }
    return multiCData;
}

CData::CData():
    d(new CDataPrivate())
{

}

CData::CData(const CData& other):
    d(new CDataPrivate())
{
    d->__fileList = other.d->__fileList;
    d->__it = other.d->__it;
}

CData::~CData()
{
    delete d;
}

QFileInfoList CData::operator ()() const
{
    return d->__fileList;
}

QFileInfo CData::operator [](int index) const
{
    return d->__fileList.value(index);
}

QString CData::path() const
{
    if (!d->__fileList.isEmpty())
        return d->__fileList.first().path();
}

const CData& CData::operator >>(QFileInfo& fileInfo) const
{
    if (!hasNext())
        d->__it = d->__fileList.begin();
    fileInfo = *d->__it;
    ++d->__it;
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
    return d->__it != d->__fileList.end();
}

void CData::load(QFileInfo info, QStringList filter)
{
    QDir dir(info.filePath());
    QFileInfoList subdirInfoList = dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    foreach (QFileInfo subdirInfo, subdirInfoList) {
        load(subdirInfo, filter);
    }
    d->__fileList << dir.entryInfoList(filter, QDir::Files);
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
