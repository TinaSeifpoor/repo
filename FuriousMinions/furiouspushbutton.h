#ifndef FURIOUSPUSHBUTTON_H
#define FURIOUSPUSHBUTTON_H

#include <QWidget>
class QPushButton;
class FuriousPushButton : public QWidget
{
    Q_OBJECT
    QPushButton* __button;
public:
    explicit FuriousPushButton(QWidget *parent = 0);
    ~FuriousPushButton();
    void mousePressEvent(QMouseEvent *);
    bool isChecked() const;
signals:

public slots:
    void setChecked(bool checked);
};

#endif // FURIOUSPUSHBUTTON_H
