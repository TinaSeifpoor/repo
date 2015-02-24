#include "scoreboard.h"
#include <QGraphicsTextItem>
#include <QGraphicsScene>
ScoreBoard::ScoreBoard(QGraphicsScene *scene):
    score(0)
{
    scoreOuter = scene->addText("0",QFont("Helvetica [Cronyx]", 22));
    scoreOuter->setDefaultTextColor(QColor(0,0,0,255));
    this->moveToCenter(scoreOuter);
    scoreInner = scene->addText("0",QFont("Helvetica [Cronyx]", 21));
    scoreInner->setDefaultTextColor(QColor(255,255,255,255));
    this->moveToCenter(scoreInner);
}

void ScoreBoard::addScore(int score)
{
    this->score+=score;
    scoreOuter->setPlainText(QString::number(this->score));
    scoreInner->setPlainText(QString::number(this->score));
    this->moveToCenter(scoreInner);
    this->moveToCenter(scoreOuter);
}

QRectF ScoreBoard::boundingRect()
{
    QRectF b = scoreOuter->boundingRect();
    b.setTopLeft(scoreOuter->pos());
    b.setBottomRight(scoreOuter->pos()+scoreOuter->boundingRect().bottomRight());
    return b;
}

void ScoreBoard::moveToCenter(QGraphicsTextItem *item) const
{
    QRectF sceneRect = item->scene()->sceneRect();
    QPointF centerForScore(0,0);
    centerForScore.setX(sceneRect.width()/2);
    centerForScore.setY(40);
    QRectF rect = item->boundingRect();
    QPointF currentCenter(item->pos().x()+rect.width()/2,item->pos().y()+rect.height()/2);
    QPointF displacement = centerForScore-currentCenter;
    item->moveBy(displacement.x(), displacement.y());
}
