#include "imageresultviewer.h"
#include "visionitem.h"
#include <QShortcut>
ImageResultViewer::ImageResultViewer(QWidget *parent) :
    QListWidget(parent)
{
    new QShortcut(Qt::Key_A, this, SLOT(sendLeftTriggered()), SLOT(sendLeftTriggered()), Qt::WidgetShortcut);
    new QShortcut(Qt::Key_D, this, SLOT(sendRightTriggered()), SLOT(sendRightTriggered()), Qt::WidgetShortcut);
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

void ImageResultViewer::sendLeft(QListWidgetItem* widgetItem)
{
    VisionItem* item = items.key(widgetItem);
    emit sendLeftSignal(item);
    items.remove(item);
    setSelectionMode(SingleSelection);
    delete widgetItem;
    setSelectionMode(ExtendedSelection);
}

void ImageResultViewer::sendRight(QListWidgetItem* widgetItem)
{
    VisionItem* item = items.key(widgetItem);
    emit sendRightSignal(item);
    items.remove(item);
    setSelectionMode(SingleSelection);
    delete widgetItem;
    setSelectionMode(ExtendedSelection);
}

void ImageResultViewer::clear()
{
    foreach (QListWidgetItem* item, items.values()) {
        delete item;
    }
    items.clear();
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

void ImageResultViewer::sendLeftTriggered()
{
    foreach (QListWidgetItem* widgetItem, selectedItems()) {
        sendLeft(widgetItem);
    }
}

void ImageResultViewer::sendRightTriggered()
{
    foreach (QListWidgetItem* widgetItem, selectedItems()) {
        sendRight(widgetItem);
    }
}

