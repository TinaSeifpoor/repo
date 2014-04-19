#include "xml.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QBuffer>
#include <QFileInfo>
#include <QDataStream>
#include <QRegExp>
#define macroPrependChar "_"

static bool writeHash(const QVariantHash &data, QXmlStreamWriter& out, int deepnessLevel)
{
    QList<QString> keyList = data.keys();
    qSort(keyList);
    QRegExp numberCheck("\\d*");
    foreach (QString keyName, keyList)
    {
        QString xmlKeyName = keyName;
        if (numberCheck.exactMatch(xmlKeyName.left(1))) {
            xmlKeyName = xmlKeyName.prepend(macroPrependChar);
        }
        for (int j=0; j<deepnessLevel; ++j)
            out.writeCharacters("\t");

        QVariant temp = data[keyName];
        out.writeStartElement(xmlKeyName);
        QString typeName = QVariant::typeToName(temp.type());
        out.writeAttribute("type", typeName);

        switch (temp.type())
        {
        default:
        {
            out.writeCharacters( "This variant type is not supported");
            out.writeEndElement();
            break;
        }
        case QVariant::Bool://intentional fall-through
        case QVariant::Int:
        case QVariant::Double:
        case QVariant::String:
        {
            out.writeCharacters(temp.toString());
            out.writeEndElement();
            break;
        }
        case QVariant::Hash:
        {
            deepnessLevel++;
            out.writeCharacters("\n");
            QVariantHash tempHash = temp.toHash();
            writeHash(tempHash, out, deepnessLevel);//recursive
            deepnessLevel--;

            for (int j=0; j<deepnessLevel; ++j)
                out.writeCharacters("\t");

            out.writeEndElement();
            break;
        }
        }
        out.writeCharacters("\n");


    }
    return true;
}

bool XML::writeXMLData(QString &dataText, const QVariantHash &data)
{
    int deepnessLevel = 1;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);

    if (buffer.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QXmlStreamWriter out(&buffer);

        out.writeStartDocument();
        out.writeCharacters("\n");
        out.writeStartElement("RDFXml");
        out.writeCharacters("\n");

        writeHash(data, out, deepnessLevel);

        out.writeEndElement();
        buffer.close();
        dataText = byteArray;
        return true;
    }
    return false;
}

bool XML::writeXMLData(QFileInfo fileInfo, const QVariantHash &data)
{
    QFile outFile(fileInfo.filePath());

    if (outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QDataStream out(&outFile);
        QString dataText;
        writeXMLData(dataText, data);
        out << dataText;
        outFile.close();
        return true;
    }
    return false;

}

bool XML::readXMLData(QFileInfo fileInfo, QVariantHash *data)
{
    QFile inFile(fileInfo.filePath());

    if (inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString dataText = inFile.readAll();
        inFile.close();
        return readXMLData(dataText, data);
    }
    return false;
}

static bool readHash(QVariantHash* data, QXmlStreamReader &in, const QString hashName)
{

    while (!in.atEnd())
    {
        in.readNext();
        QString keyName = in.name().toString();
        if (keyName.startsWith(macroPrependChar) && keyName.length()>1) {
            keyName.remove(0,1);
        }
        if (in.isStartElement())
        {
            QXmlStreamAttributes attributes = in.attributes();
            QString typeName = attributes.at(0).value().toString();

            if (attributes.size() == 1 && attributes.at(0).name() == "type")
            {
                in.readNext();
                if (in.isCharacters())
                {
                    switch (QVariant::nameToType(qPrintable(typeName)))
                    {
                    default:
                        return false;
                    case QVariant::String:
                        (*data)[keyName] = in.text().toString();
                        in.readNext();
                        break;
                    case QVariant::Int:
                        (*data)[keyName] = in.text().toString().toInt();
                        in.readNext();
                        break;
                    case QVariant::Double:
                        (*data)[keyName] = in.text().toString().toDouble();
                        in.readNext();
                        break;
                    case QVariant::Bool:
                    {
                        if (in.text().toString() == "true")
                            (*data)[keyName] = true;
                        else
                            (*data)[keyName] = false;

                        in.readNext();

                        break;
                    }
                    case QVariant::Hash:
                    {
                        QVariantHash temp;
                        readHash(&temp, in, keyName);
                        (*data)[keyName] = temp;
                        break;
                    }
                    }
                }
                else
                    return false;
            }
            else
                return false;
        }
        QString name = in.name().toString();
        if (name.startsWith(macroPrependChar) && name.length()>1) {
            name.remove(0,1);
        }
        if (in.isEndElement() &&  name == hashName)
            break;
    }
    return true;
}

bool XML::readXMLData(QString dataText, QVariantHash *data)
{
    data->clear();

    QByteArray byteArray = dataText.toLatin1();
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::ReadOnly);

    QXmlStreamReader in(&buffer);

    in.readNext();//xml doc start
    in.readNext();//first node

    if (in.name().toString() != "RDFXml")
        return false;

    readHash(data, in, in.name().toString());
    buffer.close();
    return true;
}
