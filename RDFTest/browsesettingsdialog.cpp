#include "browsesettingsdialog.h"
#include "ui_browsesettingsdialog.h"
#include <QFileDialog>
BrowseSettingsDialog::BrowseSettingsDialog(QString defaultLocation, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrowseSettingsDialog)
{
    ui->setupUi(this);
    ui->leSettingsBrowser->setText(defaultLocation);
}

BrowseSettingsDialog::~BrowseSettingsDialog()
{
    delete ui;
}

QString BrowseSettingsDialog::filePath() const
{
    return ui->leSettingsBrowser->text();
}

void BrowseSettingsDialog::on_pbSettingsBrowser_clicked()
{
    QFileDialog dialog(this);
    QFileInfo location = ui->leSettingsBrowser->text();
    if(location.isDir())
        dialog.setDirectory(ui->leSettingsBrowser->text());
    else
        dialog.setDirectory(location.dir().path());
    switch (dialog.exec()) {
    case QDialog::Accepted:
        ui->leSettingsBrowser->setText(dialog.selectedFiles().join(";"));
        break;
    case QDialog::Rejected:
        break;
    }

}
