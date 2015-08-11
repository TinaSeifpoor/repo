#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDropEvent>
#include <QFileInfo>
#include <QUrl>
#include <QImage>
#include <QImageReader>
#include "imagedisplayer.h"
#include "facecropper.h"
#include <QSettings>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("FaceCropper");
    QApplication::setApplicationVersion("0.1");
    QApplication::setOrganizationName("Katiksiz");
    MainWindow w;
    w.show();
    return a.exec();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    faceCropper(new FaceCropper())
{
    ui->setupUi(this);
    QSettings settings;
    ui->dbScalingFactor->setValue(settings.value("scalingFactor").toDouble());
    ui->dbMinSize->setValue(settings.value("minimumSize").toInt());
    ui->dbMinNeighbors->setValue(settings.value("minNeighbors").toInt());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshFaces()
{
    for (int i=0; i<ui->tabWidget->count(); ++i) {
        ImageDisplayer* displayer = dynamic_cast<ImageDisplayer*>(ui->tabWidget->widget(i));
        if (displayer) {
            QList<QImage> rightImages;
            faceCropper->crop(displayer->image, rightImages);
            displayer->setRightImages(rightImages);
        }
    }

}

void MainWindow::dropEvent(QDropEvent* e)
{
    ui->tabWidget->clear();
    foreach (QUrl url, e->mimeData()->urls()) {
        QFileInfo file(url.toLocalFile());
        foreach (QByteArray byte, QImageReader::supportedImageFormats()) {
            if (file.fileName().contains(byte)) {
                qDebug(file.filePath().toLatin1());
                QImage image(file.filePath());
                if (!image.isNull()) {
                    QImage normalImage = image.scaled(200,300,Qt::KeepAspectRatio);

                    QList<QImage> rightImages;
                    faceCropper->crop(normalImage, rightImages);
                    ui->tabWidget->addTab(new ImageDisplayer(normalImage, rightImages), file.fileName());
                }
            }
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* e)
{
    foreach (QUrl url, e->mimeData()->urls()) {
        QFileInfo file(url.toLocalFile());
        foreach (QByteArray byte, QImageReader::supportedImageFormats()) {
            if (file.fileName().contains(byte)) {
                e->accept();
                return;
            }
        }
    }
    qWarning("Can't read file!");
}

void MainWindow::on_dbScalingFactor_valueChanged(double arg1)
{
    faceCropper->setScalingFactor(arg1);
    refreshFaces();
}

void MainWindow::on_dbMinNeighbors_valueChanged(int arg1)
{
    faceCropper->setMinNeighbors(arg1);
    refreshFaces();
}

void MainWindow::on_dbMinSize_valueChanged(int arg1)
{
    faceCropper->setMinimumSize(arg1);
    refreshFaces();
}
