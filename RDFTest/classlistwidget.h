#ifndef CLASSLISTVIEW_H
#define CLASSLISTVIEW_H

#include <QListWidget>
#include "classobject.h"
#include "imagelistwidget.h"
class ClassListWidget : public QListWidget
{
    Q_OBJECT
public:
    ClassListWidget(QWidget* parent);
    void addClass(QString className);
    void addClass(ClassObject* classObj);
    void setImageListWidget(ImageListWidget* ilw);

public slots:
    void addImage(QString imagePath);

private slots:
    void on_doubleClicked(QModelIndex index);
    void on_copy_triggered();
    void on_paste_triggered();
    void on_remove_triggered();
    void on_addClass_triggered();
    void on_itemChanged(QListWidgetItem* item);

private:
    ClassObject* getClass(const QModelIndex &index);
    ClassObject* getClass(int row);
    int getRowFromName(QString className);
    ImageListWidget *imageListWidget;
    InstanceListWidget *instanceListWidget;
    QStringList classNameList;
};

#endif // CLASSLISTVIEW_H
