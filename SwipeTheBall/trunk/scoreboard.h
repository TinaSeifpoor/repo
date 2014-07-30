#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class QGraphicsTextItem;
class QGraphicsScene;
class QPoint;
class QRectF;
class ScoreBoard
{
public:
    ScoreBoard(QGraphicsScene* scene);
    void addScore(int score);
    QRectF boundingRect();
private:
    QGraphicsTextItem* scoreOuter;
    QGraphicsTextItem* scoreInner;
    void moveToCenter(QGraphicsTextItem *item) const;
    double score;

};

#endif // SCOREBOARD_H
