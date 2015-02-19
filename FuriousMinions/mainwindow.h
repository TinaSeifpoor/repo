#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reward.h"
namespace Ui {
class MainWindow;
}
class Minion;
class Quest;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void questComplete(Reward reward);
    void showGuidance(QString title, QString text);

private slots:
    void on_pbGo_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
