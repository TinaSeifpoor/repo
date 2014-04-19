#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSettings>
#include <QFileSystemModel>
#include "browsesettingsdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList args = QApplication::arguments();
    if (args.count()>1) {
        this->currentWorkFolder = args.at(1);
    } else {
        this->currentWorkFolder = "./data";
    }
    QDir dir(this->currentWorkFolder);
    dir.mkpath(this->currentWorkFolder);
    ui->wFileSystemBrowser->setPath(this->currentWorkFolder);

    connect (ui->wFileSystemBrowser, SIGNAL(imageSelected(QString)), ui->lwClasses, SLOT(addImage(QString)));
    ui->lwClasses->setImageListWidget(ui->lwImages);
    ui->lwImages->setImageWindow(ui->lblImageWindow);
    ui->lwImages->setInstanceListWidget(ui->lwInstances);
    ui->lwInstances->setImageWindow(ui->lblImageWindow);
    ui->lwClasses->addClass("1");
    ui->lwClasses->addClass("2");
}

MainWindow::~MainWindow()
{
    QSettings settings("TestSoftware", "TestCompany");
//    settings.setValue("imageFolder",ui->leFolderBrowser->text());
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    ui->lwClasses->clear();
}

void MainWindow::on_actionSave_as_triggered()
{
    QFile oldClassesFile(this->currentClassesFilePath);
    if (oldClassesFile.open(QFile::ReadOnly)) {
        QString newClassesFile = QFileDialog::getSaveFileName(this,"Save as...", this->currentClassesFilePath, "*.ini");
        if (!newClassesFile.isEmpty())
            oldClassesFile.copy(newClassesFile);
    }
}


void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionCopy_triggered()
{

}

void MainWindow::on_actionLoad_triggered()
{
    BrowseSettingsDialog browser;
    if (browser.exec()==QDialog::Accepted) {
        QSettings settings(browser.filePath(), QSettings::IniFormat);
    }
}
