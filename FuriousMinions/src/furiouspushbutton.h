#ifndef FURIOUSPUSHBUTTON_H
#define FURIOUSPUSHBUTTON_H

#include <QFrame>
class FuriousPushButtonPrivate;
class FuriousPushButton : public QFrame
{
    Q_OBJECT
    FuriousPushButtonPrivate* d;
    virtual void mousePressEvent(QMouseEvent *);
public:
    explicit FuriousPushButton(QWidget *parent = 0);
    ~FuriousPushButton();
    bool isChecked() const;
    void setAutoExclusive(bool s);
    void setCheckable(bool s);
signals:
    void clicked();
public slots:
    void setChecked(bool checked);
    void setShown(bool isShown);
};

#endif // FURIOUSPUSHBUTTON_H
