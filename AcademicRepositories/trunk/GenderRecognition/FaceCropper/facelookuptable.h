#ifndef FACELOOKUPTABLE_H
#define FACELOOKUPTABLE_H
#include <QHash>
class QFileInfo;
class QRect;
class QFile;
class FaceLookupTable
{
public:
    FaceLookupTable();
    void addFile(QFileInfo input, QList<QRect> destRects, QFileInfo destFileInfo, double scaleBackFactor);
    QHash<QFileInfo, QPair<QRect, QFileInfo> > lookupTable;
    void save();
    QFile* streamFile;
};

#endif // FACELOOKUPTABLE_H
