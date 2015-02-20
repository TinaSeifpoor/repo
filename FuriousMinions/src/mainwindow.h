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
    void showGuidance(QString title, QString text);
    void saveProgress();

private slots:
    void on_pbGo_clicked();

private:
    bool loadProgress();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
