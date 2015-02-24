#include "furiouspushbutton.h"
#include <QPushButton>
class FuriousPushButtonPrivate
{
public:
    QPushButton* button;
};

FuriousPushButton::FuriousPushButton(QWidget *parent) : QFrame(parent), d(new FuriousPushButtonPrivate)
{
    d->button = new QPushButton(parent);
    d->button->setCheckable(true);
    d->button->setAutoExclusive(true);
    d->button->setHidden(true);
    connect(d->button, SIGNAL(toggled(bool)), SLOT(setChecked(bool)));
    setLineWidth(2);
    setChecked(d->button->isChecked());
}

FuriousPushButton::~FuriousPushButton()
{

}

void FuriousPushButton::mousePressEvent(QMouseEvent *)
{
    d->button->toggle();
    emit clicked();
}

bool FuriousPushButton::isChecked() const
{
    return d->button->isChecked();
}

void FuriousPushButton::setAutoExclusive(bool s)
{
    d->button->setAutoExclusive(s);
}

void FuriousPushButton::setCheckable(bool s)
{
    d->button->setCheckable(s);
}

void FuriousPushButton::setChecked(bool checked)
{
    if (checked) {
        setFrameStyle(QFrame::Panel|QFrame::Sunken);
    } else {
        setFrameStyle(QFrame::Panel|QFrame::Raised);
    }
}

void FuriousPushButton::setShown(bool isShown)
{
    setHidden(!isShown);
}

