#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "control.h"
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
    void on_actionNew_triggered();
    void on_actionSave_as_triggered();
    void on_actionLoad_triggered();
    void on_actionExit_triggered();
    void on_wImageContainerList_itemSelected(QString imagePath);

private:
    Ui::MainWindow *ui;
    Control *control;
    QString currentClassesFilePath;
};

#endif // MAINWINDOW_H
