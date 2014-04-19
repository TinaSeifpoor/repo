#include <QString>
#include "common.h"
#include <QIODevice>
#include <QDataStream>
QString Common::mat2ByteArray(const Image &image)
{
    QByteArray byteArray;
    QDataStream stream( &byteArray, QIODevice::WriteOnly );
    stream << image.type();
    stream << image.rows;
    stream << image.cols;
    const size_t data_size = image.cols * image.rows * image.elemSize();
    QByteArray data = QByteArray::fromRawData( (const char*)image.ptr(), data_size );
    stream << data;
    return byteArray;
}

Image Common::byteArray2Mat(const QString &string)
{
    QByteArray byteArray = string.toLatin1();
    QDataStream stream(byteArray);
    int matType, rows, cols;
    QByteArray data;
    stream >> matType;
    stream >> rows;
    stream >> cols;
    stream >> data;
    cv::Mat mat( rows, cols, matType, (void*)data.data() );
    return mat.clone();
}
