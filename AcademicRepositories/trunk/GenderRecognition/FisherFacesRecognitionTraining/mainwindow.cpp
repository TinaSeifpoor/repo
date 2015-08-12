#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fisherfacerecognizer.h"
#include <QTime>
const int FEMALEINDEX=1;
const int MALEINDEX=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    recognizer(new FisherFaceRecognizer())
{
    ui->setupUi(this);
    connect(ui->lblMaleTraining, SIGNAL(dataChanged()), SLOT(trainingDataChanged()));
    connect(ui->lblFemaleTraining, SIGNAL(dataChanged()), SLOT(trainingDataChanged()));

    connect(ui->lblMaleTest, SIGNAL(dataChanged()), SLOT(reevaluateMale()));
    connect(ui->lblFemaleTest, SIGNAL(dataChanged()), SLOT(reevaluateFemale()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::trainingDataChanged()
{
    QList<QImage> maleTrainingImages = ui->lblMaleTraining->getImages();
    QVector<int> maleLabels;
    maleLabels.fill(MALEINDEX,maleTrainingImages.count());

    QList<QImage> femaleTrainingImages = ui->lblFemaleTraining->getImages();
    QVector<int> femaleLabels;
    femaleLabels.fill(FEMALEINDEX,femaleTrainingImages.count());

    if (maleTrainingImages.isEmpty()) {
        ui->listWidget->addItem(QString("%1: %2").arg(QTime::currentTime().toString("hh:mm"), "Need male images..."));
    }
    if (femaleTrainingImages.isEmpty()) {
        ui->listWidget->addItem(QString("%1: %2").arg(QTime::currentTime().toString("hh:mm"), "Need female images..."));
    }
    if (maleTrainingImages.isEmpty()||femaleTrainingImages.isEmpty())
        return;
    //
    QList<QImage> trainingImages;
    QVector<int> labels;
    trainingImages << maleTrainingImages << femaleTrainingImages;
    labels << maleLabels << femaleLabels;
    //
    ui->listWidget->addItem(QString("%1: %2").arg(QTime::currentTime().toString("hh:mm"), "Training..."));
    recognizer->trainFaces(trainingImages, labels);
    ui->listWidget->addItem(QString("%1: %2").arg(QTime::currentTime().toString("hh:mm"), "Training complete."));
    reevaluateMale();
    reevaluateFemale();
}

void MainWindow::reevaluateMale()
{
    ui->listWidget->addItem(QString("%1: %2").arg(QTime::currentTime().toString("hh:mm"), "Male"));
    reevaluate(ui->lblMaleTest,MALEINDEX);
    ui->listWidget->scrollToBottom();
}

void MainWindow::reevaluateFemale()
{
    ui->listWidget->addItem(QString("%1: %2").arg(QTime::currentTime().toString("hh:mm"), "Female"));
    reevaluate(ui->lblFemaleTest,FEMALEINDEX);
    ui->listWidget->scrollToBottom();
}

void MainWindow::reevaluate(ImageDropLabel* widget, int expected)
{
    QList<QImage> testImages = widget->getImages();
    if (testImages.isEmpty()) {
        ui->listWidget->addItem(QString("%1: %2").arg(QTime::currentTime().toString("hh:mm"), "No images for test"));
        return;
    }
    int truePositive=0;
    for (int i=0;i<testImages.count();++i) {
        if (recognizer->predictFace(testImages.at(i))==expected) ++truePositive;
    }
    double ratio = (double)truePositive /testImages.count();
    ui->listWidget->addItem(QString("%1: %2 %3").arg(QTime::currentTime().toString("hh:mm"), "Recognition rate: ").arg(ratio));
}
