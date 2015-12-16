#include "imagemover.h"
#include "imageresultviewer.h"
#include "visionitem.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QSettings>
#include <QShortcut>
#include "ui_imagemover.h"
#include <QSignalMapper>
class ImageMoverPrivate
{
public:
    QSignalMapper shortcutMapper;
};

ImageMover::ImageMover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageMover),
    d(new ImageMoverPrivate)
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

    connect(ui->le, SIGNAL(editingFinished()), SLOT(leChanged()));
    connect(&d->shortcutMapper, SIGNAL(mapped(QObject*)), SLOT(sendTriggered(QObject*)));
}

ImageMover::~ImageMover()
{
    delete ui;
    delete d;
}

void ImageMover::setPath(QString path)
{
    ui->le->setText(path);
    leChanged();
}

void ImageMover::setShortcut(QKeySequence shortcut, QObject *receiver)
{
    QShortcut* sc = new QShortcut(ui->irv);
    sc->setKey(shortcut);
    sc->setContext(Qt::WidgetShortcut);
    connect(sc, SIGNAL(activated()), &d->shortcutMapper, SLOT(map()));
    connect(sc, SIGNAL(activatedAmbiguously()), &d->shortcutMapper, SLOT(map()));
    d->shortcutMapper.setMapping(sc,receiver);
}

void ImageMover::leChanged()
{
    QString path = ui->le->text();
    QSettings settings;
    settings.beginGroup("Movers");
    settings.beginGroup(objectName());
    settings.setValue("Path", path);
    ui->irv->setDir(path);
}

void ImageMover::received(VisionItem *item)
{
    ui->irv->received(item);
}

void ImageMover::sendTriggered(QObject *receiver)
{
    if (ImageMover* other = dynamic_cast<ImageMover*>(receiver)) {
        foreach (VisionItem* item, ui->irv->selectedVisionItems())
            other->received(item);
    }
}

QString ImageMover::path() const
{
    return ui->le->text();
}
