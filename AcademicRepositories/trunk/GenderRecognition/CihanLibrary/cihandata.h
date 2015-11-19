#ifndef CIHANDATA_H
#define CIHANDATA_H
#include "cihan_global.h"
#include <QStringList>
class QFileInfo;
typedef QList<QFileInfo> QFileInfoList;

namespace cv{
class Mat;
}
class CDataPrivate;
namespace CihanLib {
class CIHANLIBRARYSHARED_EXPORT CData
{
public:
    explicit CData(QString filepath, QStringList filter = QStringList());
    static QList<CData> multiData(int argc, const char *argv[]);
    CData();
    CData(const CData& other);
    ~CData();
    QFileInfoList files() const;
    QFileInfoList operator () () const;
    QFileInfo operator [] (int index) const;
    QString path() const;
    template <typename type>
    const CData& operator >> (type& out) const;
    const CData& operator >> (QFileInfo& fileInfo) const;
    const CData& operator >> (cv::Mat& image) const;
    bool hasNext() const;


protected:
    void load(QFileInfo info, QStringList filter);
private:
    CDataPrivate*d;
};
}
#endif // CIHANDATA_H
