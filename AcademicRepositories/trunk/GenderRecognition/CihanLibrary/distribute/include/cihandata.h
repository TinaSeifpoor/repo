#ifndef CIHANDATA_H
#define CIHANDATA_H
#include "cihan_global.h"


#include <QFileInfoList>
#include <QStringList>

class CIHANLIBRARYSHARED_EXPORT CihanData
{
public:
    explicit CihanData(QString filepath, QStringList filter = QStringList());
    CihanData();
    CihanData(const CihanData& other);
    QFileInfoList files() const;
    QFileInfoList operator () () const;
    QFileInfo operator [] (int index) const;

protected:
    void load(QFileInfo info, QStringList filter);
private:
    QFileInfoList __fileList;
};

#endif // CIHANDATA_H
