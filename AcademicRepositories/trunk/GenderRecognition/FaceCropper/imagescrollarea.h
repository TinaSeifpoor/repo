#ifndef IMAGESCROLLAREA_H
#define IMAGESCROLLAREA_H

#include <QScrollArea>
class QLabel;
class ImageScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    ImageScrollArea(QWidget* parent=0);
    ~ImageScrollArea();

    void addImage(QImage image);
    void clear();

private:
    QList<QLabel*> children;
};

#endif // IMAGESCROLLAREA_H
