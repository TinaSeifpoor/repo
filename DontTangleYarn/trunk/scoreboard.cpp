#include "scoreboard.h"
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QPen>
ScoreBoard::ScoreBoard(QGraphicsScene *scene):
    score(0)
{
    scoreGraphics = scene->addText("0",QFont("Helvetica [Cronyx]", 22));
    scoreGraphics->setDefaultTextColor(QColor(255,255,255,255));
    QPen pen;
    pen.setStyle(Qt::NoPen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0,0,0,100));
    this->moveToCenter(scoreGraphics);
    scoreBackground = scene->addRect(scoreGraphics->boundingRect(),pen,brush);
    this->moveToCenter(scoreBackground);
//    scoreInner = scene->addText("0",QFont("Helvetica [Cronyx]", 21));
//    scoreInner->setDefaultTextColor(QColor(255,255,255,255));
//    this->moveToCenter(scoreInner);
}

void ScoreBoard::addScore(int score)
{
    this->score+=score;
    scoreGraphics->setPlainText(QString::number(this->score));
    this->moveToCenter(scoreGraphics);
    scoreBackground->setRect(scoreGraphics->boundingRect());
    this->moveToCenter(scoreBackground);
}

void ScoreBoard::reset()
{
    this->score = 0;
    this->addScore(0);
}

QRectF ScoreBoard::boundingRect()
{
    QRectF b = scoreGraphics->boundingRect();
    b.setTopLeft(scoreGraphics->pos());
    b.setBottomRight(scoreGraphics->pos()+scoreGraphics->boundingRect().bottomRight());
    return b;
}

void ScoreBoard::moveToCenter(QGraphicsItem *item) const
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
