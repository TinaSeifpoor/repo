#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visionitem.h"
#include "imagemover.h"

#include <QDir>
#include <QSettings>
#include <QDockWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    QSettings settings;
    QList<QDockWidget*> dockwidgets = findChildren<QDockWidget*>();
    foreach (QDockWidget* subwindow, dockwidgets) {
        QString key = subwindow->windowTitle();
        settings.beginGroup(key);
        settings.setValue("DockWidgetPosition",(int)dockWidgetArea(subwindow));
        settings.setValue("Path", dynamic_cast<ImageMover*>(subwindow->widget())->path());
        settings.endGroup();
    }
    QString key = "Center";
    settings.beginGroup(key);
    settings.setValue("Path", findChild<ImageMover*>("Center")->path());
    delete ui;
}

void MainWindow::init()
{
    QHash<QString, ImageMover*> movers;
    QSettings settings;
    // create dock widgets
    settings.beginGroup("Movers");
    foreach (QString key, settings.childGroups()) {
        settings.beginGroup(key);
        ImageMover* mover = new ImageMover(this);
        movers.insert(key, mover);
        mover->setObjectName(key);
        mover->setPath(settings.value("Path",QDir::currentPath()).toString());
        if (key!="Center") {
            QDockWidget* subwindow = new QDockWidget(this);
            subwindow->setAllowedAreas(Qt::DockWidgetArea_Mask);
            subwindow->setWindowTitle(key);
            subwindow->setWidget(mover);
            addDockWidget((Qt::DockWidgetArea)settings.value("DockWidgetPosition",1).toInt(),subwindow);
        } else {
            ui->gridLayout->addWidget(mover);
        }
        settings.endGroup();
    }

    foreach (QString key, settings.childGroups()) {
        settings.beginGroup(key);
        ImageMover* mover = movers.value(key);
        settings.endGroup();
        foreach (QString subKey, settings.childGroups()) {
            settings.beginGroup(subKey);
            QString shortcutKey = settings.value("Shortcut").toString();
            if (!shortcutKey.isEmpty()) {
                ImageMover* targetMover;
                if (subKey==key) {
                    targetMover =  movers.value("Center");
                } else {
                    targetMover = movers.value(subKey);
                }
                mover->setShortcut(shortcutKey, targetMover);
            }
            settings.endGroup();
        }
    }
}

void MainWindow::on_actionClear_Revert_all_triggered()
{
    QSettings settings;
    settings.clear();
    if (settings.childGroups().isEmpty()) {
        settings.beginGroup("Movers");
        settings.beginGroup("Top");
        settings.setValue("Shortcut",   "W");
        settings.endGroup();
        settings.beginGroup("Left");
        settings.setValue("Shortcut",   "A");
        settings.endGroup();
        settings.beginGroup("Bottom");
        settings.setValue("Shortcut",   "S");
        settings.endGroup();
        settings.beginGroup("Right");
        settings.setValue("Shortcut",   "D");
        settings.endGroup();
        settings.beginGroup("Center");
        settings.setValue("Path", QDir::currentPath());
        settings.endGroup();
        settings.endGroup();
    }
    qApp->quit();
}
