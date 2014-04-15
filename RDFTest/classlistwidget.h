#ifndef CLASSLISTVIEW_H
#define CLASSLISTVIEW_H

#include <QListWidget>
#include "classobject.h"
#include "imagelistwidget.h"
class ClassListWidget : public QListWidget
{
public:
    ClassListWidget(QWidget* parent);
    void addClass(QString className);
    void removeClass(ClassObject className);
    void setImageListWidget(ImageListWidget* ilw);

private slots:
    void on_doubleClicked(const QModelIndex &index);

private:
    ClassObject* getClass(const QModelIndex &index);
    ClassObject* getClass(int row);
    int getRowFromName(QString className);
    ImageListWidget *imageListWidget;
    InstanceListWidget *instanceListWidget;
};

#endif // CLASSLISTVIEW_H
