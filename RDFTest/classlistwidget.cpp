#include "classlistwidget.h"
#include <QAction>
#include <QClipboard>
#include <QApplication>
#include <QDataStream>
#include <QBuffer>
class ClassObjectWidgetItem:public QListWidgetItem {
    ClassObject* classObject;
public:
    ClassObject* get() const {return this->classObject;}
    void addImage(const QString imagePath) {
        classObject->addImage(imagePath);
    }

    ClassObjectWidgetItem(ClassObject* classObject):classObject(classObject){this->setText(this->classObject->name());}
};

ClassListWidget::ClassListWidget(QWidget *parent):
    QListWidget(parent)
{
    QAction* copy = new QAction(this);
    QAction* paste = new QAction(this);
    copy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    paste->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    this->addAction(copy);
    this->addAction(paste);
    connect (copy, SIGNAL(triggered()), this, SLOT(on_copy_triggered()));
    connect (paste, SIGNAL(triggered()), this, SLOT(on_paste_triggered()));

    connect (this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_doubleClicked(QModelIndex)));
}

void ClassListWidget::addClass(QString className)
{
    if (this->classNameList.contains(className)) {
        className.append("_");
        this->addClass(className);
    } else {
        this->classNameList << className;
        this->addItem(new ClassObjectWidgetItem(new ClassObject(className)));
    }
}

void ClassListWidget::addClass(ClassObject *classObj)
{
    if (this->classNameList.contains(classObj->name())) {
        QString newName = classObj->name();
        newName.append("_");
        classObj->setName(newName);
        this->addClass(classObj);
    } else {
        this->classNameList << classObj->name();
        this->addItem(new ClassObjectWidgetItem(classObj));
    }
}

void ClassListWidget::on_doubleClicked(QModelIndex index)
{
    this->imageListWidget->set(this->getClass(index.row()));
}

void ClassListWidget::on_copy_triggered()
{
    if(!this->selectedItems().isEmpty()) {
        QVariantHash data;
        foreach (QListWidgetItem* item, this->selectedItems()) {
            ClassObject* obj = static_cast<ClassObjectWidgetItem*>(item)->get();
            data.unite(obj->toIni());
        }
        QByteArray byteArray;
        {
               QBuffer buffer(&byteArray);
               buffer.open(QIODevice::WriteOnly);

               QDataStream out(&buffer);
               out << data;
//               if (out.status()==QDataStream::Ok) {
//                   qDebug("test2");
//               }
        }
        QString string(byteArray.toBase64());

//        qDebug(nData.keys().first().toLatin1().constData());
        QApplication::clipboard()->setText(string);
    }
}

void ClassListWidget::on_paste_triggered()
{
    QString string = QApplication::clipboard()->text();
    QByteArray byteArray = QByteArray::fromBase64(string.toUtf8());
    QVariantHash data;
    {
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::ReadOnly);

        QDataStream in(&buffer);
        in >> data;
    }
    if (!data.isEmpty()) {
        QStringList keyList = data.keys();
        foreach (QString key, keyList) {
            ClassObject* obj = new ClassObject(data.value(key).toHash());
            this->addClass(obj);
        }
    }
}

ClassObject *ClassListWidget::getClass(const QModelIndex &index)
{
    return this->getClass(index.row());
}

ClassObject* ClassListWidget::getClass(int row)
{
    ClassObjectWidgetItem* item = static_cast<ClassObjectWidgetItem*>(this->item(row));
    return item->get();
}

int ClassListWidget::getRowFromName(QString className)
{
    int nItems = this->count();
    for (int idxItem=0; idxItem<nItems; ++idxItem)
    {
        ClassObjectWidgetItem* i = static_cast<ClassObjectWidgetItem*>(this->item(idxItem));
        if (i->get()->name()==className)
        {
            return idxItem;
        }
    }
    return -1;
}


void ClassListWidget::setImageListWidget(ImageListWidget *ilw)
{
    this->imageListWidget = ilw;
}

void ClassListWidget::addImage(QString imagePath)
{
    if (this->count()<1) {
        this->addClass("1");
    }
    if (this->selectedItems().isEmpty()) {
        this->setCurrentIndex(this->indexFromItem(this->item(0)));
    }
    ClassObjectWidgetItem* item = static_cast<ClassObjectWidgetItem*>(this->selectedItems().first());

    item->addImage(imagePath);
    this->imageListWidget->set(item->get());
}
