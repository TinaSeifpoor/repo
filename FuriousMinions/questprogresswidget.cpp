#include "questprogresswidget.h"
#include <QPropertyAnimation>
#include "minion.h"
#include "quest.h"
class QuestProgressWidgetPrivate
{
public:
    Quest quest;
    Minion minion;
};

QuestProgressWidget::QuestProgressWidget(Minion minion, Quest quest, QWidget *parent):
    QPushButton(parent),
    d(new QuestProgressWidgetPrivate())
{
    d->quest = quest;
    d->minion = minion;
    setText(QString("%1\n%2").arg(minion.getName(),QString("Time: %1 Affinities: (%2)").arg(quest.getTime()/1000).arg(affinityStringList(quest.getAffinities()).join(", "))));
}

QuestProgressWidget::~QuestProgressWidget()
{
    delete d;
}
