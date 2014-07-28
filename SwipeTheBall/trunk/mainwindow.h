#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTimer;
class Ball;
class Attack;
class AnimationFactory;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void frameSignalToSend();
    void frameSignalReceive();
    void regularHit(QPointF pos);

private slots:
    void miss();
    void hit();
    void frame();
    void on_pushButton_toggled(bool checked);
    void genBall(int count=1);
    void removeBall(qint16 idx);

private:
    Ui::MainWindow *ui;
    QTimer* fps;
    QList<Ball*> balls;
    QList<qint16> availableBalls;
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    Attack* attack;
    AnimationFactory* animationFactory;

    struct Settings {
        int ballVanishMinTime;
        int ballVanishTime;
        int minRadius;
        int radius;
        int minHealth;
        int health;
        int maulDamage;
        int swipeDamage;
        int ballChance;
        double maulRadius;
        double swipeLength1;
        double swipeLength2;
    } gameSettings;
};

#endif // MAINWINDOW_H
