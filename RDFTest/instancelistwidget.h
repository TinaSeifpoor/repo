#ifndef INSTANCELISTVIEW_H
#define INSTANCELISTVIEW_H

#include <QListWidget>
class ImageObject;
class ImageWindow;
class InstanceListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit InstanceListWidget(QWidget *parent = 0);
    void set(ImageObject* im);
    void setImageWindow(ImageWindow* iw);

signals:
    
public slots:
private slots:
    void on_selectItem(int row);
private:
    ImageWindow* iw;
};

#endif // INSTANCELISTVIEW_H
