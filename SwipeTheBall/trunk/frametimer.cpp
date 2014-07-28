#include "frametimer.h"

FrameTimer::FrameTimer():isSingleShot(false),frameCount(0),frameLimit(0)
{
}

FrameTimer *FrameTimer::singleShot(int frameLimit, QString name)
{
    FrameTimer* f = new FrameTimer();
    f->setSingleShot(true);
    f->setFrameLimit(frameLimit);
    f->setObjectName(name);
    return f;
}

void FrameTimer::setSingleShot(bool singleShot)
{
    isSingleShot = singleShot;
}

void FrameTimer::setFrameLimit(uint frameLimit)
{
    this->frameLimit = frameLimit;
}

void FrameTimer::frame()
{
    if (++frameCount>= frameLimit){
        emit timeout(this->objectName());
        if (isSingleShot) {
            deleteLater();
        }
    }
}
