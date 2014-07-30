#ifndef ANIMATIONFACTORY_H
#define ANIMATIONFACTORY_H

#include <QObject>
#include <QLineF>
#include <QRegion>
class QGraphicsScene;
class AnimationFactory: public QObject
{
    Q_OBJECT
public:
    AnimationFactory(QGraphicsScene* scene);

public slots:
    void swipe(QLineF line);
    void maul(QRegion reg);
signals:
    void frame();
private:
    QGraphicsScene* scene;
};

#endif // ANIMATIONFACTORY_H
