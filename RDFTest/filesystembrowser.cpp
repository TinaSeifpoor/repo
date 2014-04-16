#include "filesystembrowser.h"
#include "ui_filesystembrowser.h"
#include <QFileSystemModel>
#include <QMessageBox>
FileSystemBrowser::FileSystemBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSystemBrowser)
{
    ui->setupUi(this);
    QFileSystemModel *model = new QFileSystemModel;
    model->setFilter(QDir::NoDotAndDotDot|QDir::Dirs|QDir::Files);
    model->setNameFilters(QStringList() << "Images (*.png *.jpg *.bmp)");
    model->setRootPath(ui->lePath->text());
    ui->tvFileSystem->setModel(model);
//    ui->tvFileSystem->setSortingEnabled(true);
    ui->tvFileSystem->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tvFileSystem->setExpandsOnDoubleClick(true);
}

FileSystemBrowser::~FileSystemBrowser()
{
    delete ui;
}

void FileSystemBrowser::on_tvFileSystem_doubleClicked(const QModelIndex &index)
{
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>(ui->tvFileSystem->model());
    QString filePath = model->filePath(index);
    QFileInfo fileInfo(filePath);
    if (fileInfo.isFile()) {
        emit imageSelected(filePath);
    }
}

void FileSystemBrowser::on_lePath_editingFinished()
{
    QString path = ui->lePath->text();
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>(ui->tvFileSystem->model());
    QModelIndex modelIndex = model->index(path);
    if (model->fileInfo(modelIndex).exists()) {
        if (model->isDir(modelIndex)) {
            ui->tvFileSystem->expand(modelIndex);
        }
        ui->tvFileSystem->scrollTo(modelIndex,QAbstractItemView::PositionAtTop);
        ui->tvFileSystem->setCurrentIndex(modelIndex);
    }
    else {
        QMessageBox::warning(this, "Path not found!", QString("Specified path not found\n%1").arg(path));
    }
}

void FileSystemBrowser::on_lePath_returnPressed()
{
    this->on_lePath_editingFinished();
}
