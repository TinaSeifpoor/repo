#ifndef CONTROL_H
#define CONTROL_H
#include <QObject>
#include "imagecontainer.h"
class Control : public QObject
{
    Q_OBJECT
public:
    Control();

public slots:
    void setImage(QString fileString);
signals:
    void showImageNKeypoints(Image,KeyPoints);

private:
    ImageContainer* imageContainer;

};

#endif // CONTROL_H
