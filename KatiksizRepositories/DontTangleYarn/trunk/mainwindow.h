#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Ball;
class Attack;
class AnimationFactory;
class ScoreBoard;
class QTimer;
class QGraphicsTextItem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void initMainWindow();
    ~MainWindow();

signals:
    void frameSignalToSend();
    void frameSignalReceive();
    void regularHit(QPointF pos);

public slots:
    void newBall(Ball* ball);
private slots:
    void miss();
    void hit(double health);
    void genBall(int count=1);
    void removeBall(double, qint16 idx);

private:
    Ui::MainWindow *ui;
    QTimer* fps;
    QList<Ball*> balls;
    QList<qint16> availableBalls;
    void mouseReleaseEvent(QMouseEvent *ev);
    bool eventFilter(QObject *obj, QEvent *ev);
    void pause();
    void resume();
    void resizeEvent(QResizeEvent *);
    Attack* attack;
    AnimationFactory* animationFactory;
    ScoreBoard* score;
    bool resetGameAtResume;
    struct Settings {
        int minRadius;
        int radius;
        double maulRadius;
    } gameSettings;
    bool init;
    bool isPaused;
};

#endif // MAINWINDOW_H
