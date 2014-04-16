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
    void add(ImageObject *im);
    ImageObject *getImage(int row);

public slots:
    void set(ClassObject* obj);
private slots:
    void on_doubleClicked(QModelIndex index);
private:
    InstanceListWidget* ilw;
    ImageWindow* iw;
};

#endif // IMAGELISTVIEW_H
