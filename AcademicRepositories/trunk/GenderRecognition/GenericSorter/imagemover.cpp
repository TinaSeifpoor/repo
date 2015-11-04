#include "imagemover.h"
#include "imageresultviewer.h"
#include "visionitem.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QSettings>
ImageMover::ImageMover(QWidget *parent) : QWidget(parent),
    irv(new ImageResultViewer(this)),
    le(new QLineEdit(this))
{
    irv->setWordWrap(true);
    irv->setMovement(QListView::Static);
    irv->setViewMode(QListView::IconMode);
    irv->setUniformItemSizes(true);
    irv->setSortingEnabled(true);
    irv->setEditTriggers(QListView::NoEditTriggers);
    irv->setDragDropMode(QListView::NoDragDrop);
    irv->setResizeMode(QListView::Adjust);
    irv->setSelectionMode(QAbstractItemView::ExtendedSelection);
    irv->setIconSize(QSize(200,200));
    irv->setAcceptDrops(false);

    connect(this, SIGNAL(received(VisionItem*)), irv, SLOT(received(VisionItem*)));
    connect(irv, SIGNAL(sendLeftSignal(VisionItem*)), SIGNAL(sendLeftSignal(VisionItem*)));
    connect(irv, SIGNAL(sendRightSignal(VisionItem*)), SIGNAL(sendRightSignal(VisionItem*)));

    connect(le, SIGNAL(editingFinished()), SLOT(leChanged()));


    QGridLayout* gLayout = new QGridLayout(this);
    setLayout(gLayout);
    gLayout->addWidget(le,0,0,1,1);
    gLayout->addWidget(irv,1,0,1,1);
}

void ImageMover::setPath(QString path)
{
    le->setText(path);
    leChanged();
}

void ImageMover::leChanged()
{
    QString path = this->le->text();
    QSettings settings;
    settings.setValue(objectName().append("DirPath"), path);
    irv->setDir(path);
}

