#ifndef FRAMETIMER_H
#define FRAMETIMER_H

#include <QObject>
class FrameTimer : public QObject
{
    Q_OBJECT
public:
    FrameTimer();
    static FrameTimer* singleShot(int frameLimit, QString name = QString());
    void setSingleShot(bool singleShot);
    void setFrameLimit(uint frameLimit);
public slots:
    void frame();
signals:
    void timeout(QString);
private:
    bool isSingleShot;
    uint frameCount;
    uint frameLimit;
};

#endif // FRAMETIMER_H
