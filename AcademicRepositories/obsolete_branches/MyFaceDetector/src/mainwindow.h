#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include "imagewindow.h"
#include <EvaluationListModel.h>
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
    void showImage(cv::Mat im);
    void loadForest(QFileInfo forest);
    void testForest(QFileInfoList imageFiles);

public slots:
    void showLog(QString text);
    void showLog(const char* c);
    void showLog(std::string s);
    void evaluation(QList<EvaluationModel> hfe);

private slots:
    void on_pushButtonLoadForest_released();
    void on_pushButtonSelectImage_released();
    void on_listViewLoadedImages_doubleClicked(const QModelIndex &index);

    void on_pushButtonClearLoadedImages_released();

    void on_lineEditTh_editingFinished();

private:
    Ui::MainWindow *ui;

    QFileInfoList loadedImages;
    QStringList imageExtentionFilter;

    QFileInfoList loadFolderImage(QDir folder);
    QList<EvaluationModel> hfe;
    QFile* logFile;
    double sum;
    int positiveCount;
};

#endif // MAINWINDOW_H
