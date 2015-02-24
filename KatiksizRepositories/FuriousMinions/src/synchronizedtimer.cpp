#include "synchronizedtimer.h"
#include <QTimer>
SynchronizedTimer *syncTimer=0;
QTimer* epochTimer=0;
QTimer* bigEpochTimer=0;
SynchronizedTimer::SynchronizedTimer(QObject *parent) : QObject(parent)
{
    epochTimer = new QTimer(this);
    connect(epochTimer, SIGNAL(timeout()), SIGNAL(epoch()));
    epochTimer->setSingleShot(false);
    epochTimer->start(100);
    bigEpochTimer = new QTimer(this);
    connect(bigEpochTimer, SIGNAL(timeout()), SIGNAL(bigEpoch()));
    bigEpochTimer->setSingleShot(false);
    bigEpochTimer->start(30000);
}

SynchronizedTimer *SynchronizedTimer::getInstance()
{
    if (!syncTimer)
        syncTimer = new SynchronizedTimer();
    return syncTimer;
}

SynchronizedTimer::~SynchronizedTimer()
{
    syncTimer = 0;
    if (epochTimer)
        epochTimer->deleteLater();
    if (bigEpochTimer)
        bigEpochTimer->deleteLater();
}

