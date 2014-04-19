#ifndef XML_H
#define XML_H

#include <QVariantHash>
class QFileInfo;
class XML
{
public:
    static bool writeXMLData(QString &dataText, const QVariantHash &data);
    static bool writeXMLData(QFileInfo fileInfo, const QVariantHash &data);
    static bool readXMLData(QFileInfo fileInfo, QVariantHash *data);
    static bool readXMLData(QString dataText, QVariantHash *data);
};

#endif // XML_H
