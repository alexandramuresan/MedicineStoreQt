/********************************************************************************
** Form generated from reading UI file 'medicinestoreqt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDICINESTOREQT_H
#define UI_MEDICINESTOREQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MedicineStoreQTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MedicineStoreQTClass)
    {
        if (MedicineStoreQTClass->objectName().isEmpty())
            MedicineStoreQTClass->setObjectName(QStringLiteral("MedicineStoreQTClass"));
        MedicineStoreQTClass->resize(600, 400);
        menuBar = new QMenuBar(MedicineStoreQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MedicineStoreQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MedicineStoreQTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MedicineStoreQTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MedicineStoreQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MedicineStoreQTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MedicineStoreQTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MedicineStoreQTClass->setStatusBar(statusBar);

        retranslateUi(MedicineStoreQTClass);

        QMetaObject::connectSlotsByName(MedicineStoreQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *MedicineStoreQTClass)
    {
        MedicineStoreQTClass->setWindowTitle(QApplication::translate("MedicineStoreQTClass", "MedicineStoreQT", 0));
    } // retranslateUi

};

namespace Ui {
    class MedicineStoreQTClass: public Ui_MedicineStoreQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDICINESTOREQT_H
