#ifndef FILESYSTEMBROWSER_H
#define FILESYSTEMBROWSER_H

#include <QWidget>

namespace Ui {
class FileSystemBrowser;
}

class FileSystemBrowser : public QWidget
{
    Q_OBJECT
    
public:
    explicit FileSystemBrowser(QWidget *parent = 0);
    ~FileSystemBrowser();

signals:
    void imageSelected(QString);
private slots:
    void on_tvFileSystem_doubleClicked(const QModelIndex &index);

    void on_lePath_editingFinished();

    void on_lePath_returnPressed();

private:
    Ui::FileSystemBrowser *ui;
};

#endif // FILESYSTEMBROWSER_H
