#include "questhub.h"
#include <QGridLayout>
#include "questselectionwidget.h"
#include "globalvariables.h"
#include "furiouspushbutton.h"
#include <QApplication>
#include <QLabel>

FuriousPushButton* genFuriousButtonIconText(QString iconPath, QString text, QWidget* parent=0);

QuestHub::QuestHub(QWidget *parent): QWidget(parent),
    hubRank(1),
    nextButton(genFuriousButtonIconText(":/icons/arrows/15/resources/15x15/arrow-up.gif",QApplication::tr("Venture to next area!"),this)),
    previousButton(genFuriousButtonIconText(":/icons/arrows/15/resources/15x15/arrow-down.gif",QApplication::tr("Go back to previous area!"),this))
{
    setLayout(new QGridLayout());
    layout()->setMargin(4);
    layout()->addWidget(nextButton);
    layout()->addWidget(previousButton);
    nextButton->setShown(false);
    previousButton->setShown(false);
    layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Preferred, QSizePolicy::Expanding));

    connect(nextButton, SIGNAL(clicked()), SLOT(nextRank()));
    connect(previousButton, SIGNAL(clicked()), SLOT(prevRank()));
    GlobalVariables::setNextLevelNotifier(nextButton, SLOT(setShown(bool)));
}

QuestHub::~QuestHub()
{

}

void QuestHub::addQuest(Quest quest)
{
    addQuestSelectionWidget(new QuestSelectionWidget(quest,this));
}

void QuestHub::addQuest()
{
    addQuest(Quest(hubRank));
}

void QuestHub::addQuestSelectionWidget(QuestSelectionWidget *qsw)
{
    qsw->setParent(this);
    QLayoutItem* item = layout()->takeAt(layout()->count()-1);
    layout()->addWidget(qsw);
    layout()->addItem(item);
}

QuestSelectionWidget *QuestHub::getQuestSelectionWidget()
{
    foreach (QuestSelectionWidget* qsw, findChildren<QuestSelectionWidget*>()) {
        if (qsw->isChecked()) {
            return qsw;
        }
    }
    return 0;
}

QVariantHash QuestHub::toHash() const
{
    QVariantHash questHubHash;
    questHubHash.insert("Rank", hubRank);
    QList<QuestSelectionWidget*> qswList = findChildren<QuestSelectionWidget*>();
    for (int i=0; i<qswList.count();++i) {
        questHubHash.insert(QString::number(i),qswList.value(i)->toHash());
    }
    return questHubHash;
}

void QuestHub::fromHash(QVariantHash hash)
{
    hubRank = qMax(hash.take("Rank").toInt(),1);
    foreach (QVariant var, hash) {
        addQuestSelectionWidget(new QuestSelectionWidget(Quest::fromHash(var.toHash()),this));
    }
}

void QuestHub::setRank(Rank rank)
{
    clear();
    hubRank=rank;
    previousButton->setShown(hubRank>1);
    nextButton->setShown(GlobalVariables::questCount(hubRank)>=10);
    fillQuests();
}

void QuestHub::clear()
{
    foreach (QuestSelectionWidget* qsw, findChildren<QuestSelectionWidget*>())
        qsw->deleteLater();
}

void QuestHub::fillQuests()
{
    for (int i=0; i<3; ++i)
        addQuest(Quest(hubRank));
}

void QuestHub::nextRank()
{
    setRank(hubRank+1);
}

void QuestHub::prevRank()
{
    setRank(hubRank-1);
}

void QuestHub::questComplete(Quest quest)
{
    GlobalVariables::addQuest(quest.getRank());
    nextButton->setShown(GlobalVariables::questCount(hubRank)>=10);
}


FuriousPushButton* genFuriousButtonIconText(QString iconPath, QString text, QWidget* parent)
{
    FuriousPushButton* button = new FuriousPushButton(parent);
    button->setAutoExclusive(false);
    button->setCheckable(false);
    QLabel* icon = new QLabel(button);
    icon->setPixmap(QPixmap(iconPath));
    icon->setAlignment(Qt::AlignLeft);
    QLabel* label = new QLabel(button);
    label->setText(text);
    label->setAlignment(Qt::AlignRight);
    QGridLayout* layout = new QGridLayout(button);
    layout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed),0,0);
    layout->addWidget(label,0,1);
    layout->addWidget(icon,0,2);
    layout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed),0,3);
    button->setLayout(layout);
    return button;
}
