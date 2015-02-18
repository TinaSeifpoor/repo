#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
#include "minion.h"
#include "quest.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
//    void questComplete(Minion minion, Quest quest);
    void showGuidance(QString title, QString text);

private slots:
    void on_pbGo_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
