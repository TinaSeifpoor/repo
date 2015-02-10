#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load(QString pageTxt)
{
    qDebug(QUrl(pageTxt).toString().toLatin1());
    ui->webView->load(QUrl(pageTxt));
}
