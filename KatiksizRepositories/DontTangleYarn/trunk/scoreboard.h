#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class QGraphicsTextItem;
class QGraphicsRectItem;
class QGraphicsItem;
class QGraphicsScene;
class QPoint;
class QRectF;
class ScoreBoard
{
public:
    ScoreBoard(QGraphicsScene* scene);
    void addScore(int score);
    void reset();
    QRectF boundingRect();
private:
    QGraphicsTextItem* scoreGraphics;
    QGraphicsRectItem* scoreBackground;
    void moveToCenter(QGraphicsItem *item) const;
    int score;

};

#endif // SCOREBOARD_H
