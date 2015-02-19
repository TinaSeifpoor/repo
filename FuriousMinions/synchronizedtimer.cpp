#include "synchronizedtimer.h"
#include <QTimer>
SynchronizedTimer *sync=0;
QTimer* timer=0;
SynchronizedTimer::SynchronizedTimer(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SIGNAL(epoch()));
    timer->setSingleShot(false);
    timer->start(100);
}

SynchronizedTimer *SynchronizedTimer::getInstance()
{
    if (!sync)
        sync = new SynchronizedTimer();
    return sync;
}

SynchronizedTimer::~SynchronizedTimer()
{
    sync = 0;
}

