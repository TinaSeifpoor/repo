#include "animationfactory.h"
#include "swipeanimation.h"
#include "maulanimation.h"
#include "frametimer.h"
AnimationFactory::AnimationFactory(QGraphicsScene *scene):
    scene(scene)
{

}

void AnimationFactory::swipe(QLineF line)
{
    FrameTimer* timer = FrameTimer::singleShot(10);
    connect(this, SIGNAL(frame()), timer, SLOT(frame()));
    connect(timer, SIGNAL(timeout(QString)), new SwipeAnimation(line,scene),SLOT(deleteLine()));
}

void AnimationFactory::maul(QRegion reg)
{
    FrameTimer* timer = FrameTimer::singleShot(10);
    connect(this, SIGNAL(frame()), timer, SLOT(frame()));
    connect(timer, SIGNAL(timeout(QString)), new MaulAnimation(reg,scene),SLOT(deleteLine()));
}
