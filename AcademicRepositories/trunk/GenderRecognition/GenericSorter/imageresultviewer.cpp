#include "imageresultviewer.h"
#include "visionitem.h"
#include <QShortcut>
#include <QWheelEvent>

ImageResultViewer::ImageResultViewer(QWidget *parent) :
    QListWidget(parent)
{
    new QShortcut(Qt::Key_F5, this, SLOT(refresh()), SLOT(refresh()), Qt::WidgetShortcut);
}

ImageResultViewer::~ImageResultViewer()
{
}

void ImageResultViewer::setDir(QString path)
{
    if (QDir(path)!=__dir) {
        __dir = QDir(path);
        if (!__dir.exists())
            __dir.mkpath(__dir.path());
        refresh();
    }
}

QDir ImageResultViewer::dir() const
{
    return __dir;
}

void ImageResultViewer::clear()
{
    foreach (VisionItem* item, items.keys()) {
        delete items.value(item);
        delete item;
    }
    items.clear();
}

QList<VisionItem*> ImageResultViewer::selectedVisionItems()
{
    QList<VisionItem*> visionItems;
    foreach(QListWidgetItem * widgetItem,selectedItems()) {
        VisionItem* item = items.key(widgetItem);
        items.remove(item);
        visionItems << item;
        setSelectionMode(SingleSelection);
        delete widgetItem;
        setSelectionMode(ExtendedSelection);
    }
    return visionItems;
}

void ImageResultViewer::refresh()
{
    clear();
    foreach (QFileInfo info, __dir.entryInfoList(QDir::Files)) {
        VisionItem* item = new VisionItem(info);
        QListWidgetItem* widgetItem = new QListWidgetItem(item->Icon(), item->Name(), this);
        items.insert(item, widgetItem);
    }
}

void ImageResultViewer::wheelEvent(QWheelEvent* w)
{
    if (w->modifiers()&Qt::ControlModifier) {
        int sizeInt = iconSize().width();
        sizeInt=qMax(sizeInt+w->delta(),20);
        setIconSize(QSize(sizeInt,sizeInt));
        w->accept();
    } else {
        QListWidget::wheelEvent(w);
    }
}

void ImageResultViewer::received(VisionItem* item)
{
    QListWidgetItem* widgetItem=0;
    if (!items.contains(item)) {
        widgetItem = new QListWidgetItem(item->Icon(), item->Name(), this);
    } else {
        widgetItem = items.value(item);
        widgetItem->setIcon(item->Icon());
        widgetItem->setText(item->Name());
    }
    item->moveTo(__dir.path());
    items.insert(item, widgetItem);
    scrollToItem(widgetItem, QAbstractItemView::EnsureVisible);
}
