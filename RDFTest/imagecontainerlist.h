#ifndef IMAGECONTAINERLIST_H
#define IMAGECONTAINERLIST_H

#include <QTreeView>
#include <QFileSystemModel>

class ImageContainerList : public QTreeView
{
    Q_OBJECT
    
public:
    explicit ImageContainerList(QWidget *parent = 0, QStringList list = QStringList());
    ~ImageContainerList();
signals:
    void itemSelected(QString item);

public slots:
    void clicked_slot(const QModelIndex & index);
private:
    QFileSystemModel *systemModel;
};

#endif // IMAGECONTAINERLIST_H
