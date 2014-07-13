#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTimer;
class MovingLine;
class QSignalMapper;
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
    void mouseClick(QPointF pos);

private slots:
    void miss(int);
    void hit(int);
    void frame();
    void on_pushButton_toggled(bool checked);
    void genBall();

private:
    Ui::MainWindow *ui;
    QTimer* fps;
    QSignalMapper* ballHitMapper, *ballMissMapper;
    QList<MovingLine*> lines;
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    int ballChance;
};

#endif // MAINWINDOW_H
