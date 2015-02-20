#ifndef SYNCHRONIZEDTIMER_H
#define SYNCHRONIZEDTIMER_H

#include <QObject>

class SynchronizedTimer : public QObject
{
    Q_OBJECT
    explicit SynchronizedTimer(QObject *parent = 0);
public:
    static SynchronizedTimer* getInstance();
    ~SynchronizedTimer();
signals:
    void epoch();
    void bigEpoch();
};

#endif // SYNCHRONIZEDTIMER_H
