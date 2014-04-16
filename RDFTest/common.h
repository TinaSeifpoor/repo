#ifndef COMMON_H
#define COMMON_H
#include "opencv2/opencv.hpp"
typedef std::vector<cv::KeyPoint> KeyPoints;
typedef cv::Mat Image;

QByteArray mat2ByteArray(const cv::Mat &image)
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

cv::Mat byteArray2Mat(const QByteArray & byteArray)
{
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
#endif // COMMON_H
