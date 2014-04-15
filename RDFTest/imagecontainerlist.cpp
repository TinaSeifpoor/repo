#include "imagecontainerlist.h"

ImageContainerList::ImageContainerList(QWidget *parent, QStringList list) :
    QTreeView(parent),
    systemModel(new QFileSystemModel)
{
    QDir d = QDir::currentPath();
    d.cdUp();
    this->setModel(this->systemModel);
    this->setRootIndex(this->systemModel->setRootPath(d.path()));
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(clicked_slot(QModelIndex)));
}

ImageContainerList::~ImageContainerList()
{
}

void ImageContainerList::clicked_slot(const QModelIndex &index)
{
    qDebug(this->systemModel->filePath(index).toLatin1().constData());
    emit itemSelected(systemModel->filePath(index));
}
