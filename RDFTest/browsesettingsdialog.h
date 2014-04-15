#ifndef BROWSESETTINGSDIALOG_H
#define BROWSESETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class BrowseSettingsDialog;
}

class BrowseSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BrowseSettingsDialog(QString defaultLocation="", QWidget *parent = 0);
    ~BrowseSettingsDialog();

    QString filePath() const;
    
private slots:
    void on_pbSettingsBrowser_clicked();

private:
    Ui::BrowseSettingsDialog *ui;
};

#endif // BROWSESETTINGSDIALOG_H
