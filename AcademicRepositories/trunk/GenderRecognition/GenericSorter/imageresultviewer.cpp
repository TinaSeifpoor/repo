#include "imageresultviewer.h"
#include "visionitem.h"
#include <QShortcut>
ImageResultViewer::ImageResultViewer(QWidget *parent) :
    QListWidget(parent)
{
    setIconSize(QSize(200,200));
    setAcceptDrops(false);
    dir = QDir::current();
    new QShortcut(Qt::Key_A, this, SLOT(sendLeftTriggered()), SLOT(sendLeftTriggered()), Qt::WidgetShortcut);
    new QShortcut(Qt::Key_D, this, SLOT(sendRightTriggered()), SLOT(sendRightTriggered()), Qt::WidgetShortcut);
}

ImageResultViewer::~ImageResultViewer()
{
}

void ImageResultViewer::setDir(QString path)
{
    dir = QDir(path);
    if (!dir.exists())
        dir.mkpath(dir.path());
}

void ImageResultViewer::sendLeft(QListWidgetItem* widgetItem)
{
    widgetItem->setBackgroundColor(VisionItem::leftColor());
    VisionItem* item = items.key(widgetItem);
    emit sendLeftSignal(item);
    if (behaviour&RemoveOnSend) {
        QString potentialFilepath = dir.filePath(item->FileInfo().fileName());
        QFile::remove(potentialFilepath);
        items.remove(item);
        setSelectionMode(SingleSelection);
        delete widgetItem;
        setSelectionMode(ExtendedSelection);
    }
}

void ImageResultViewer::sendRight(QListWidgetItem* widgetItem)
{
    widgetItem->setBackgroundColor(VisionItem::rightColor());
    VisionItem* item = items.key(widgetItem);
    emit sendRightSignal(item);
    if (behaviour&RemoveOnSend) {
        QString potentialFilepath = dir.filePath(item->FileInfo().fileName());
        QFile::remove(potentialFilepath);
        items.remove(item);
        setSelectionMode(SingleSelection);
        delete widgetItem;
        setSelectionMode(ExtendedSelection);
    }
}

void ImageResultViewer::setBehaviourEnum(BehaviourEnum val)
{
    behaviour=val;
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
    widgetItem->setBackgroundColor(VisionItem::centerColor());
    items.insert(item, widgetItem);
    if (behaviour&CopyOnReceive) {
        QString from = item->FileInfo().filePath();
        QString to   = dir.filePath(item->FileInfo().fileName());
        if (QFile::copy(from, to)) {
            qDebug("Success: %s to %s", from.toLatin1().constData(), to.toLatin1().constData());
        } else {
            qWarning("Failed: %s to %s", from.toLatin1().constData(), to.toLatin1().constData());
        }
    }
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

