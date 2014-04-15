#ifndef INSTANCELISTVIEW_H
#define INSTANCELISTVIEW_H

#include <QListWidget>
class ImageObject;
class InstanceListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit InstanceListWidget(QWidget *parent = 0);
    void set(ImageObject* im);
signals:
    
public slots:
    
};

#endif // INSTANCELISTVIEW_H
