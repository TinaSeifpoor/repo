#include "imagemover.h"
#include "imageresultviewer.h"
#include "visionitem.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QSettings>
#include <QShortcut>
#include "ui_imagemover.h"
ImageMover::ImageMover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageMover)
{
    ui->setupUi(this);
    ui->irv->setWordWrap(true);
    ui->irv->setMovement(QListView::Static);
    ui->irv->setViewMode(QListView::IconMode);
    ui->irv->setUniformItemSizes(true);
    ui->irv->setSortingEnabled(true);
    ui->irv->setEditTriggers(QListView::NoEditTriggers);
    ui->irv->setDragDropMode(QListView::NoDragDrop);
    ui->irv->setResizeMode(QListView::Adjust);
    ui->irv->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->irv->setAcceptDrops(false);

    connect(this, SIGNAL(received(VisionItem*)), ui->irv, SLOT(received(VisionItem*)));
    connect(ui->irv, SIGNAL(sendLeftSignal(VisionItem*)), SIGNAL(sendLeftSignal(VisionItem*)));
    connect(ui->irv, SIGNAL(sendRightSignal(VisionItem*)), SIGNAL(sendRightSignal(VisionItem*)));

    connect(ui->le, SIGNAL(editingFinished()), SLOT(leChanged()));
}

ImageMover::~ImageMover()
{
    delete ui;
}

void ImageMover::setPath(QString path)
{
    ui->le->setText(path);
    leChanged();
}

void ImageMover::leChanged()
{
    QString path = ui->le->text();
    QSettings settings;
    settings.beginGroup(objectName());
    settings.setValue("Path", path);
    ui->irv->setDir(path);
}


void ImageMover::setRightShortcut(QKeySequence rightShortcut)
{
    new QShortcut(rightShortcut, ui->irv, SLOT(sendRightTriggered()), SLOT(sendRightTriggered()), Qt::WidgetShortcut);
}

void ImageMover::setLeftShortcut(QKeySequence leftShortcut)
{
    new QShortcut(leftShortcut, ui->irv, SLOT(sendLeftTriggered()), SLOT(sendLeftTriggered()), Qt::WidgetShortcut);

}
