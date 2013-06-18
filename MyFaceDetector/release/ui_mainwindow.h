/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Jun 16 12:04:34 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "imagewindow.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Features;
    QAction *actionAdd_Forest;
    QAction *actionAdd_Forest_2;
    QAction *actionLoad_Forest;
    QAction *actionSave_Forest;
    QAction *actionQuit;
    QAction *actionPredict;
    QAction *actionPredict_features;
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QListView *listViewForest;
    QPushButton *pushButtonLoadForest;
    QPushButton *pushButtonSaveForest;
    QWidget *tabInput;
    QGridLayout *gridLayout;
    QCheckBox *checkBoxOnline;
    QLineEdit *lineEditImagePath;
    QPushButton *pushButtonSelectImage;
    QListView *listViewLoadedImages;
    QScrollArea *scrollAreaForImage;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    ImageWindow *labelImage;
    QPlainTextEdit *plainTextEditLog;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(862, 693);
        actionLoad_Features = new QAction(MainWindow);
        actionLoad_Features->setObjectName(QString::fromUtf8("actionLoad_Features"));
        actionAdd_Forest = new QAction(MainWindow);
        actionAdd_Forest->setObjectName(QString::fromUtf8("actionAdd_Forest"));
        actionAdd_Forest_2 = new QAction(MainWindow);
        actionAdd_Forest_2->setObjectName(QString::fromUtf8("actionAdd_Forest_2"));
        actionLoad_Forest = new QAction(MainWindow);
        actionLoad_Forest->setObjectName(QString::fromUtf8("actionLoad_Forest"));
        actionSave_Forest = new QAction(MainWindow);
        actionSave_Forest->setObjectName(QString::fromUtf8("actionSave_Forest"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionPredict = new QAction(MainWindow);
        actionPredict->setObjectName(QString::fromUtf8("actionPredict"));
        actionPredict_features = new QAction(MainWindow);
        actionPredict_features->setObjectName(QString::fromUtf8("actionPredict_features"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setMaximumSize(QSize(350, 16777215));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        listViewForest = new QListView(tab);
        listViewForest->setObjectName(QString::fromUtf8("listViewForest"));

        gridLayout_3->addWidget(listViewForest, 0, 0, 1, 1);

        pushButtonLoadForest = new QPushButton(tab);
        pushButtonLoadForest->setObjectName(QString::fromUtf8("pushButtonLoadForest"));
        pushButtonLoadForest->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(pushButtonLoadForest, 1, 0, 1, 1);

        pushButtonSaveForest = new QPushButton(tab);
        pushButtonSaveForest->setObjectName(QString::fromUtf8("pushButtonSaveForest"));

        gridLayout_3->addWidget(pushButtonSaveForest, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tabInput = new QWidget();
        tabInput->setObjectName(QString::fromUtf8("tabInput"));
        gridLayout = new QGridLayout(tabInput);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBoxOnline = new QCheckBox(tabInput);
        checkBoxOnline->setObjectName(QString::fromUtf8("checkBoxOnline"));

        gridLayout->addWidget(checkBoxOnline, 0, 0, 1, 1);

        lineEditImagePath = new QLineEdit(tabInput);
        lineEditImagePath->setObjectName(QString::fromUtf8("lineEditImagePath"));

        gridLayout->addWidget(lineEditImagePath, 1, 0, 1, 1);

        pushButtonSelectImage = new QPushButton(tabInput);
        pushButtonSelectImage->setObjectName(QString::fromUtf8("pushButtonSelectImage"));

        gridLayout->addWidget(pushButtonSelectImage, 1, 1, 1, 1);

        listViewLoadedImages = new QListView(tabInput);
        listViewLoadedImages->setObjectName(QString::fromUtf8("listViewLoadedImages"));

        gridLayout->addWidget(listViewLoadedImages, 2, 0, 1, 2);

        tabWidget->addTab(tabInput, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);

        scrollAreaForImage = new QScrollArea(centralWidget);
        scrollAreaForImage->setObjectName(QString::fromUtf8("scrollAreaForImage"));
        scrollAreaForImage->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 486, 651));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelImage = new ImageWindow(scrollAreaWidgetContents);
        labelImage->setObjectName(QString::fromUtf8("labelImage"));

        gridLayout_2->addWidget(labelImage, 0, 0, 1, 1);

        scrollAreaForImage->setWidget(scrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollAreaForImage, 0, 1, 2, 1);

        plainTextEditLog = new QPlainTextEdit(centralWidget);
        plainTextEditLog->setObjectName(QString::fromUtf8("plainTextEditLog"));
        plainTextEditLog->setMaximumSize(QSize(350, 16777215));
        plainTextEditLog->setReadOnly(true);

        gridLayout_4->addWidget(plainTextEditLog, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionLoad_Features->setText(QApplication::translate("MainWindow", "Load Features", 0, QApplication::UnicodeUTF8));
        actionAdd_Forest->setText(QApplication::translate("MainWindow", "Add Forest", 0, QApplication::UnicodeUTF8));
        actionAdd_Forest_2->setText(QApplication::translate("MainWindow", "Add Forest", 0, QApplication::UnicodeUTF8));
        actionLoad_Forest->setText(QApplication::translate("MainWindow", "Load Forest", 0, QApplication::UnicodeUTF8));
        actionSave_Forest->setText(QApplication::translate("MainWindow", "Save Forest", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionPredict->setText(QApplication::translate("MainWindow", "Predict", 0, QApplication::UnicodeUTF8));
        actionPredict_features->setText(QApplication::translate("MainWindow", "Predict features", 0, QApplication::UnicodeUTF8));
        pushButtonLoadForest->setText(QApplication::translate("MainWindow", "Load Forest", 0, QApplication::UnicodeUTF8));
        pushButtonLoadForest->setShortcut(QApplication::translate("MainWindow", "F10", 0, QApplication::UnicodeUTF8));
        pushButtonSaveForest->setText(QApplication::translate("MainWindow", "Save Forest", 0, QApplication::UnicodeUTF8));
        pushButtonSaveForest->setShortcut(QApplication::translate("MainWindow", "F9", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Forest Properties", 0, QApplication::UnicodeUTF8));
        checkBoxOnline->setText(QApplication::translate("MainWindow", "Online", 0, QApplication::UnicodeUTF8));
        pushButtonSelectImage->setText(QApplication::translate("MainWindow", "Browse...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabInput), QApplication::translate("MainWindow", "Images", 0, QApplication::UnicodeUTF8));
        labelImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
