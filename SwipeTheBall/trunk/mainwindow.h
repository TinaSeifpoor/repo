#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTimer;
class Ball;
class QSignalMapper;
class Attack;
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

    Attack* attack;
};

#endif // MAINWINDOW_H
