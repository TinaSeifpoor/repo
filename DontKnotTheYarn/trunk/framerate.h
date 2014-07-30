#ifndef FRAMERATE_H
#define FRAMERATE_H
#include <QTimer>
class FrameRate : public QTimer
{
public:
    FrameRate(int fps);
signals:
    void timeout();
private:
    int fps;
};

#endif // FRAMERATE_H
