#ifndef CIHANDATA_H
#define CIHANDATA_H
#include "cihan_global.h"


#include <QFileInfoList>
#include <QStringList>
namespace cv{
class Mat;
}
namespace CihanLib {
class FaceLandmark;
class CIHANLIBRARYSHARED_EXPORT CData
{
public:
    explicit CData(QString filepath, QStringList filter = QStringList());
    CData();
    CData(const CData& other);
    QFileInfoList files() const;
    QFileInfoList operator () () const;
    QFileInfo operator [] (int index) const;
    template <typename type>
    const CData& operator >> (type& fileInfo) const;
    const CData& operator >> (QFileInfo& fileInfo) const;
    const CData& operator >> (FaceLandmark& faceLandmark) const;
    const CData& operator >> (cv::Mat& image) const;

protected:
    void load(QFileInfo info, QStringList filter);
private:
    QFileInfoList __fileList;

    mutable QFileInfoList::const_iterator __it;
};
}
#endif // CIHANDATA_H
