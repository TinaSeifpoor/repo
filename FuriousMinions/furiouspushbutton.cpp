#include "furiouspushbutton.h"
#include <QPushButton>
FuriousPushButton::FuriousPushButton(QWidget *parent) : QWidget(parent), __button(new QPushButton(parent))
{
    __button->setCheckable(true);
    __button->setAutoExclusive(true);
    __button->setHidden(true);
    connect(__button, SIGNAL(toggled(bool)), SLOT(setChecked(bool)));
}

FuriousPushButton::~FuriousPushButton()
{

}

void FuriousPushButton::mousePressEvent(QMouseEvent *)
{
    __button->setChecked(!__button->isChecked());
}

bool FuriousPushButton::isChecked() const
{
    return __button->isChecked();
}

void FuriousPushButton::setChecked(bool checked)
{
    if (checked) {

    } else {

    }
}

