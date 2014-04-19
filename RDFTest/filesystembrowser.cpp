#include "filesystembrowser.h"
#include "ui_filesystembrowser.h"
#include <QMessageBox>
#include <QFileSystemModel>
QList<QFileInfo> recursiveImageFiles(QFileInfo baseDirInfo);

FileSystemBrowser::FileSystemBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSystemBrowser)
{
    ui->setupUi(this);
    QAction* addAllAction = new QAction(this);
    addAllAction->setShortcut(Qt::CTRL + Qt::Key_A);
    this->addAction(addAllAction);
    connect(addAllAction, SIGNAL(triggered()), this, SLOT(on_addAllAction_triggered()));
    QFileSystemModel *model = new QFileSystemModel;

    model->setNameFilters(QStringList() << "*.png" <<  "*.jpg" <<  "*.bmp");
    ui->tvFileSystem->setModel(model);
    QFileInfo f(ui->lePath->text());
    ui->lePath->setText(f.absoluteFilePath());
    ui->tvFileSystem->setRootIndex(model->index(f.absoluteFilePath()));
    ui->tvFileSystem->setSortingEnabled(true);

    ui->tvFileSystem->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tvFileSystem->setExpandsOnDoubleClick(true);
}

FileSystemBrowser::~FileSystemBrowser()
{
    delete ui;
}

void FileSystemBrowser::setPath(QString path)
{
    ui->lePath->setText(path);
    emit ui->lePath->editingFinished();
}

void FileSystemBrowser::on_tvFileSystem_doubleClicked(const QModelIndex &index)
{
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>(ui->tvFileSystem->model());
    QString filePath = model->filePath(index);
    QFileInfo fileInfo(filePath);
    if (fileInfo.isFile()) {
        emit imageSelected(filePath);
    } else {
        ui->lePath->setText(fileInfo.absoluteFilePath());
    }
}

void FileSystemBrowser::on_lePath_editingFinished()
{
    QFileInfo f(ui->lePath->text());
    if (!f.exists()) {
        QMessageBox::warning(this, "Path not found!", QString("Specified path not found\n%1").arg(f.absoluteFilePath()));
        return;
    }
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>(ui->tvFileSystem->model());
    delete model;
    QString path = f.absoluteFilePath();
    model = new QFileSystemModel;
    model->setNameFilters(QStringList() << "*.png" <<  "*.jpg" <<  "*.bmp");
    if (f.isDir()) {
        model->setRootPath(path);
    } else {
        emit imageSelected(path);
        model->setRootPath(f.absolutePath());
    }
    ui->tvFileSystem->setModel(model);
    ui->tvFileSystem->setRootIndex(model->index(model->rootPath()));
}

void FileSystemBrowser::on_lePath_returnPressed()
{
    this->on_lePath_editingFinished();
}

void FileSystemBrowser::on_addAllAction_triggered()
{
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>(ui->tvFileSystem->model());
    QFileInfo addAllFileInfo = model->fileInfo(ui->tvFileSystem->currentIndex());
    if (!addAllFileInfo.exists())
        return;
    if (addAllFileInfo.isFile()) {
        emit imageSelected(addAllFileInfo.absoluteFilePath());
    } else {
        QList<QFileInfo> filesToAdd = recursiveImageFiles(addAllFileInfo);
        foreach (QFileInfo fileToAdd, filesToAdd) {
            emit imageSelected(fileToAdd.absoluteFilePath());
        }
    }
}

QList<QFileInfo> recursiveImageFiles(QFileInfo baseDirInfo) {
    QDir baseDir(baseDirInfo.absoluteFilePath());
    QList<QFileInfo> out = baseDir.entryInfoList(QStringList() << "*.png" << "*.jpg" << "*.bmp",QDir::Files);
    QList<QFileInfo> subDirs = baseDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QFileInfo subDir, subDirs)
        out << recursiveImageFiles(subDir);
    return out;
}

