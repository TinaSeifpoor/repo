#ifndef SPLITDATA_H
#define SPLITDATA_H

#include <QFileInfoList>
#include <QStringList>
class SplitData
{
public:
    explicit SplitData(QString filepath, QStringList filter = QStringList());
    QFileInfoList files() const;
    QFileInfoList operator () () const;

protected:
    void load(QFileInfo info, QStringList filter);
private:
    QFileInfoList __fileList;
};

#endif // SPLITDATA_H
