#ifndef VISIONITEM_H
#define VISIONITEM_H
#include <QColor>
#include <QIcon>
#include <QFileInfo>

#define myproperty(name, type) \
    private: \
    type __##name;\
    public:  \
    void set##name(type name) {this->__##name = name;}\
    type name() const {return this->__##name;}



class VisionItem
{
    myproperty(Icon,QIcon)
    myproperty(Name,QString)
    myproperty(FileInfo,QFileInfo)
public:
    VisionItem(QFileInfo fileInfo);
    static inline QColor leftColor() {return Qt::blue;}
    static inline QColor rightColor() {return Qt::magenta;}
    static inline QColor centerColor() {return Qt::white;}
};

#endif // VISIONITEM_H
