#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSettings>
#include "browsesettingsdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    control(new Control())
{
    ui->setupUi(this);
    connect (ui->wImageContainerList, SIGNAL(itemSelected(QString)), this->control, SLOT(setImage(QString)));
    connect (this->control, SIGNAL(showImageNKeypoints(Image,KeyPoints)), ui->lblImageWindow, SLOT(showImageNKeypoints(Image,KeyPoints)));
    QSettings settings("TestSoftware", "TestCompany");
    ui->leFolderBrowser->setText(settings.value("imageFolder", "../../images").toString());
    ui->lwClasses->setImageListWidget(ui->lwImages);
    ui->lwImages->setImageWindow(ui->lblImageWindow);
    ui->lwImages->setInstanceListWidget(ui->lwInstances);
    ui->lwClasses->addClass("1");
    ui->lwClasses->addClass("2");
}

MainWindow::~MainWindow()
{
    QSettings settings("TestSoftware", "TestCompany");
    settings.setValue("imageFolder",ui->leFolderBrowser->text());
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

void MainWindow::on_wImageContainerList_itemSelected(QString imagePath)
{
    ui->lwImages->add(imagePath);
}


void MainWindow::on_actionLoad_triggered()
{
    BrowseSettingsDialog browser;
    if (browser.exec()==QDialog::Accepted) {
        QSettings settings(browser.filePath(), QSettings::IniFormat);
    }
}
