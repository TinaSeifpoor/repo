#ifndef IMAGELISTVIEW_H
#define IMAGELISTVIEW_H

#include <QListWidget>
class ImageWindow;
class ImageObject;
class ClassObject;
class InstanceListWidget;
namespace cv {
    class Mat;
    class KeyPoint;
}
class ImageListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ImageListWidget(QWidget *parent = 0);
    void setInstanceListWidget(InstanceListWidget* ilw);
    void setImageWindow(ImageWindow* iw);
    void add(QString imagePath);
    void add(ImageObject* im);

    ImageObject *getImage(int row);

public slots:
    void set(ClassObject* obj);
private slots:
    void on_currentRowChanged(int row);
    void on_copy_triggered();
    void on_paste_triggered();
    void on_itemChanged(QListWidgetItem *item);

private:
    void reload();
    InstanceListWidget* ilw;
    ImageWindow* iw;
    ClassObject *parent;
};

#endif // IMAGELISTVIEW_H
