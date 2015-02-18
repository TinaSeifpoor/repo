#ifndef QUESTPROGRESSWIDGET_H
#define QUESTPROGRESSWIDGET_H

#include <QPushButton>
#include "minion.h"
#include "quest.h"
class QuestProgressWidgetPrivate;
class QuestProgressWidget : public QPushButton
{
    QuestProgressWidgetPrivate*d;
public:
    QuestProgressWidget(Minion minion, Quest quest, QWidget* parent=0);
    ~QuestProgressWidget();
};

#endif // QUESTPROGRESSWIDGET_H
