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
    QSettings settings;
    if (settings.childGroups().isEmpty()) {
        settings.beginGroup("Original");
        settings.setValue("LeftShotcut", "A");
        settings.setValue("LeftShortcutReceiver", "Left");
        settings.setValue("RightShortcut", "D");
        settings.setValue("RightShortcutReceiver", "Right");
        settings.endGroup();
        settings.beginGroup("Left");
        settings.setValue("LeftShotcut", "A");
        settings.setValue("LeftShortcutReceiver", "Original");
        settings.setValue("RightShortcut", "D");
        settings.setValue("RightShortcutReceiver", "Right");
        settings.endGroup();
        settings.beginGroup("Right");
        settings.setValue("LeftShotcut", "A");
        settings.setValue("LeftShortcutReceiver", "Left");
        settings.setValue("RightShortcut", "D");
        settings.setValue("RightShortcutReceiver", "Original");
        settings.endGroup();
    }

    // create mdi windows
    QHash<QString, ImageMover*> movers;
    foreach (QString key, settings.childGroups()) {
        settings.beginGroup(key);
        ImageMover* mover = new ImageMover(this);
        movers.insert(key, mover);
        mover->setObjectName(key);
        mover->setPath(settings.value("Path",QDir::current().path()).toString());
        mover->setLeftShortcut(settings.value("LeftShortcut", "A").toString());
        mover->setRightShortcut(settings.value("RightShortcut", "D").toString());


        QDockWidget* subwindow = new QDockWidget(this);
        subwindow->setAllowedAreas(Qt::DockWidgetArea_Mask);
        subwindow->setWindowTitle(key);
        subwindow->setWidget(mover);
        addDockWidget((Qt::DockWidgetArea)settings.value("DockWidgetPosition").toInt(),subwindow);
        settings.endGroup();
    }

    foreach (QString key, settings.childGroups()) {
        settings.beginGroup(key);
        ImageMover* baseMover = movers.value(key);
        ImageMover* leftMover = movers.value(settings.value("LeftShortcutReceiver").toString(),0);
        leftMover->connect(baseMover, SIGNAL(sendLeftSignal(VisionItem*)), SIGNAL(received(VisionItem*)));
        ImageMover* rightMover = movers.value(settings.value("RightShortcutReceiver").toString(),0);
        rightMover->connect(baseMover, SIGNAL(sendRightSignal(VisionItem*)), SIGNAL(received(VisionItem*)));
        settings.endGroup();
    }
}

MainWindow::~MainWindow()
{
    QSettings settings;
    QStringList keys;
    QList<QDockWidget*> dockwidgets = findChildren<QDockWidget*>();
    foreach (QDockWidget* subwindow, dockwidgets) {
        QString key = subwindow->windowTitle();
        settings.beginGroup(key);
        settings.setValue("DockWidgetPosition",(int)dockWidgetArea(subwindow));
        keys << key;
        settings.endGroup();
    }
    foreach (QString key, settings.childGroups()) {
        if (!keys.contains(key)) {
            settings.remove(key);
        }
    }
    delete ui;
}

void MainWindow::moverClosed(QWidget* w)
{
    if (w) {
        QSettings settings;
        settings.remove(w->objectName());
    }
}
