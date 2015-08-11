#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class FaceCropper;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void refreshFaces();

protected:
    void dropEvent(QDropEvent *e);
    void dragEnterEvent(QDragEnterEvent *e);
private slots:
    void on_dbScalingFactor_valueChanged(double arg1);

    void on_dbMinNeighbors_valueChanged(int arg1);

    void on_dbMinSize_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    FaceCropper*faceCropper;
};

#endif // MAINWINDOW_H
