#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class ImageDropLabel;
class FisherFaceRecognizer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void trainingDataChanged();
    void reevaluateMale();
    void reevaluateFemale();

private:
    void reevaluate(ImageDropLabel* widget, int expected);
    Ui::MainWindow *ui;
    FisherFaceRecognizer*recognizer;
};

#endif // MAINWINDOW_H
