#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTimer;
class MovingLine;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void miss();
    void hit();
    void frame();

    void on_pushButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer* fps;
    MovingLine *w;
};

#endif // MAINWINDOW_H
