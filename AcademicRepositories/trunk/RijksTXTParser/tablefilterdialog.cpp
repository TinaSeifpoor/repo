#include "tablefilterdialog.h"
#include "ui_tablefilterdialog.h"
#include <QTableWidget>
#include <QTimer>
TableFilterDialog::TableFilterDialog(QTableWidget* tw, QStringList featureNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableFilterDialog),
    tw(tw),
    timer(new QTimer())
{
    ui->setupUi(this);
    int nHeaders = featureNames.count();
    for (int i=0; i<nHeaders;++i)
        ui->cbFeatureNames->addItem(featureNames.value(i));
    timer->setInterval(20);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), SLOT(updateFilter()));
    connect(ui->lwItems, SIGNAL(itemSelectionChanged()), timer, SLOT(start()));
}

TableFilterDialog::~TableFilterDialog()
{
    delete ui;
}

void TableFilterDialog::on_cbFeatureNames_activated(int index)
{
    ui->lwItems->clear();
    allItems.clear();
    for (int i=0; i<tw->rowCount(); ++i) {
        allItems << tw->item(i, index)->text();
    }
    QStringList items = allItems;
    items.removeDuplicates();
    foreach (QString item ,items) {
        ui->lwItems->addItem(item);
    }
}

void TableFilterDialog::updateFilter()
{

    for (int i=0; i<allItems.count(); ++i) {
        QString itemText = allItems.value(i);
        bool filtered=true;
        foreach (QListWidgetItem* item, ui->lwItems->selectedItems()) {
            QString filter = item->text();
            if (itemText.contains(filter)) {
                filtered=false;
                break;
            }
        }
        if (filtered)
            tw->hideRow(i);
        else
            tw->showRow(i);
    }

}

void TableFilterDialog::on_lwItems_itemSelectionChanged()
{
    timer->start();

}
