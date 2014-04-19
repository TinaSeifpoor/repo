#ifndef INSTANCELISTVIEW_H
#define INSTANCELISTVIEW_H

#include <QListWidget>
class ImageObject;
class ImageWindow;
class InstanceObject;
class InstanceListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit InstanceListWidget(QWidget *parent = 0);
    void add(InstanceObject* obj);
    void set(ImageObject* im);
    void setImageWindow(ImageWindow* iw);

signals:
    
public slots:
private slots:
    void on_itemChanged(QListWidgetItem *item);
    void on_copy_triggered();
    void on_paste_triggered();
    void on_selectItem(int row);
private:
    ImageWindow* iw;
    ImageObject* parent;
};

#endif // INSTANCELISTVIEW_H
