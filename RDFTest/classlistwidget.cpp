#include "classlistwidget.h"
#include <QAction>
#include <QClipboard>
#include <QApplication>
#include <QDataStream>
#include <QBuffer>
#include "xml.h"
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
    this->setEditTriggers(QListWidget::EditKeyPressed);
    QAction* copy = new QAction(this);
    QAction* paste = new QAction(this);
    QAction* remove = new QAction(this);
    QAction* addClass = new QAction(this);
    copy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    paste->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    remove->setShortcut(QKeySequence(Qt::Key_Delete));
    addClass->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    this->addAction(copy);
    this->addAction(paste);
    this->addAction(remove);
    this->addAction(addClass);
    connect (copy, SIGNAL(triggered()), this, SLOT(on_copy_triggered()));
    connect (paste, SIGNAL(triggered()), this, SLOT(on_paste_triggered()));
    connect (remove, SIGNAL(triggered()), this, SLOT(on_remove_triggered()));
    connect (addClass, SIGNAL(triggered()), this, SLOT(on_addClass_triggered()));
    connect (this, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(on_itemChanged(QListWidgetItem*)));
    connect (this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_doubleClicked(QModelIndex)));
}

void ClassListWidget::addClass(QString className)
{
    if (this->classNameList.contains(className)) {
        className.append("_");
        this->addClass(className);
    } else {
        this->classNameList << className;
        ClassObjectWidgetItem* it = new ClassObjectWidgetItem(new ClassObject(className));
        it->setFlags(it->flags() | Qt::ItemIsEditable);
        this->addItem(it);
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
        ClassObjectWidgetItem* it = new ClassObjectWidgetItem(classObj);
        it->setFlags(it->flags() | Qt::ItemIsEditable);
        this->addItem(it);
    }
}

void ClassListWidget::on_doubleClicked(QModelIndex index)
{
    this->imageListWidget->set(this->getClass(index.row()));
}

void ClassListWidget::on_copy_triggered()
{
    QList<QListWidgetItem*> items = this->selectedItems();
    if(!items.isEmpty()) {
        QVariantHash data;
        foreach (QListWidgetItem* item, items) {
            ClassObject* obj = static_cast<ClassObjectWidgetItem*>(item)->get();
            data.unite(obj->toHash());
        }
        QString dataText;
        XML::writeXMLData(dataText, data);
        QApplication::clipboard()->setText(dataText);
     }
}

void ClassListWidget::on_paste_triggered()
{
    QString string = QApplication::clipboard()->text();
    QVariantHash data;
    XML::readXMLData(string, &data);
    if (!data.isEmpty()) {
        QStringList keyList = data.keys();
        foreach (QString key, keyList) {
            ClassObject* obj = new ClassObject(data.value(key).toHash());
            this->addClass(obj);
        }
    }
}

void ClassListWidget::on_remove_triggered()
{
    QList<QListWidgetItem*> items = this->selectedItems();

    if(!items.isEmpty()) {
        this->classNameList.removeOne(items.first()->text());
        delete items.first();
    }
}

void ClassListWidget::on_addClass_triggered()
{
    this->addClass("1");
}

void ClassListWidget::on_itemChanged(QListWidgetItem *item)
{
    ClassObject* obj = static_cast<ClassObjectWidgetItem*>(item)->get();
    obj->setName(item->text());
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
