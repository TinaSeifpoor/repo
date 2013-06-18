#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QMessageBox>
#include <QStringListModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sum(0),
    logFile(new QFile("./log.txt"))
{
    ui->setupUi(this);
    imageExtentionFilter << "*.png" << "*.xpm" << "*.jpg" << "*.bmp" << "*.ppm";
    connect (this, SIGNAL(showImage(cv::Mat)), ui->labelImage, SLOT(showImage(cv::Mat)));
    logFile->open(QFile::ReadOnly);
    ui->listViewLoadedImages->setModel(new QStringListModel());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLog(const char *c){showLog(QString(c));}
void MainWindow::showLog(std::string s){showLog(QString::fromStdString(s));}

void MainWindow::evaluation(QList<EvaluationModel> hfe)
{
    this->hfe << hfe;
    QStringList sList = static_cast<QStringListModel* const>(ui->listViewLoadedImages->model())->stringList();
    foreach (EvaluationModel currHf, hfe)
    {
        sum+=currHf.AO;
        QString str = QString("%1 - (%2)").arg(currHf.imFileInfo.fileName()).arg(QString::number(currHf.AO));
        sList << str;
        if (currHf.AO>ui->lineEditTh->text().toDouble())
            positiveCount += 1;
        this->showLog(QString("Avg: %1, Perf: %2").arg(QString::number(sum/sList.count())).arg(QString::number(positiveCount/sList.count())));
        logFile->write(QString::number(currHf.AO).append("\n").toAscii());
    }
    delete ui->listViewLoadedImages->model();
    ui->listViewLoadedImages->setModel(new QStringListModel(sList));

}

void MainWindow::showLog(QString text)
{
    text.append("\n");
    text.prepend(QTime::currentTime().toString("[hh:mm:ss] "));
    ui->plainTextEditLog->moveCursor(QTextCursor::End);
    ui->plainTextEditLog->insertPlainText(text);
    ui->plainTextEditLog->moveCursor(QTextCursor::End);
}

void MainWindow::on_pushButtonLoadForest_released()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load Map", "../", QString("*.txt"));
    if (filename.isEmpty())
        return;
    QFileInfo forestFileInfo(filename);
    if (!forestFileInfo.exists())
    {
        QMessageBox::warning(0, "File not found", QString("Forest file \"%1\" not found!").arg(filename));
        return;
    }
    emit loadForest(forestFileInfo);
}

void MainWindow::on_pushButtonSelectImage_released()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Load Images", "../../", QString("Images (%1)").arg(imageExtentionFilter.join(" ")));
    if (filenames.isEmpty())
    {
        filenames << QFileDialog::getExistingDirectory(this, "Load Images", "../../");
    }
    if (filenames.isEmpty())
        return;
    foreach (QString filename, filenames)
    {
        QFileInfoList loadedImages;
        QFileInfo fileInfo(filename);
        if (fileInfo.isDir())
        {
            loadedImages << this->loadFolderImage(QDir(fileInfo.filePath()));
        }
        else
        {
            loadedImages << fileInfo;
            emit testForest(loadedImages);
        }
        this->loadedImages<<loadedImages;
    }
}

QFileInfoList MainWindow::loadFolderImage(QDir folder)
{
    QFileInfoList filenames = folder.entryInfoList(imageExtentionFilter, QDir::Files);
    emit testForest(filenames);
    QFileInfoList subdirs = folder.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    foreach (QFileInfo subdir, subdirs)
    {
        filenames << loadFolderImage(QDir(subdir.filePath()));
    }
    return filenames;
}

void MainWindow::on_listViewLoadedImages_doubleClicked(const QModelIndex &index)
{
    EvaluationModel currHfe = hfe.at(index.row());
    this->showImage(currHfe.imToShow);
}

void MainWindow::on_pushButtonClearLoadedImages_released()
{
    hfe.clear();
    delete ui->listViewLoadedImages->model();
    ui->listViewLoadedImages->setModel(new QStringListModel());
    logFile->reset();
    sum = 0;
}

void MainWindow::on_lineEditTh_editingFinished()
{

}

