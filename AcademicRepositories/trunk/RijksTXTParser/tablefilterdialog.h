#ifndef TABLEFILTERDIALOG_H
#define TABLEFILTERDIALOG_H

#include <QDialog>
#include <QTableWidget>
namespace Ui {
class TableFilterDialog;
}

class TableFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableFilterDialog(QTableWidget* tw, QStringList featureNames, QWidget *parent = 0);
    ~TableFilterDialog();


private slots:
    void on_cbFeatureNames_activated(int index);

    void updateFilter();

    void on_lwItems_itemSelectionChanged();

private:
    Ui::TableFilterDialog *ui;
    QTableWidget* tw;
    QStringList allItems;
    QTimer* timer;
};

#endif // TABLEFILTERDIALOG_H
