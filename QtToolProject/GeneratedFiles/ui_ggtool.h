/********************************************************************************
** Form generated from reading UI file 'ggtool.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GGTOOL_H
#define UI_GGTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glview.h"

QT_BEGIN_NAMESPACE

class Ui_ggToolClass
{
public:
    QWidget *centralWidget;
    GLView *widget;
    QTableWidget *coordinateList;
    QCheckBox *textOnOff;
    QPushButton *saveButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *pointSizeLabel;
    QSpinBox *pointSize;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ggToolClass)
    {
        if (ggToolClass->objectName().isEmpty())
            ggToolClass->setObjectName(QStringLiteral("ggToolClass"));
        ggToolClass->resize(1241, 754);
        centralWidget = new QWidget(ggToolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new GLView(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(400, 10, 831, 651));
        coordinateList = new QTableWidget(centralWidget);
        coordinateList->setObjectName(QStringLiteral("coordinateList"));
        coordinateList->setGeometry(QRect(10, 10, 380, 651));
        textOnOff = new QCheckBox(centralWidget);
        textOnOff->setObjectName(QStringLiteral("textOnOff"));
        textOnOff->setGeometry(QRect(400, 670, 81, 16));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(1080, 670, 75, 23));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(690, 670, 111, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pointSizeLabel = new QLabel(horizontalLayoutWidget);
        pointSizeLabel->setObjectName(QStringLiteral("pointSizeLabel"));

        horizontalLayout->addWidget(pointSizeLabel);

        pointSize = new QSpinBox(horizontalLayoutWidget);
        pointSize->setObjectName(QStringLiteral("pointSize"));
        pointSize->setMinimum(1);
        pointSize->setMaximum(20);
        pointSize->setValue(10);

        horizontalLayout->addWidget(pointSize);

        ggToolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ggToolClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1241, 21));
        ggToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ggToolClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ggToolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ggToolClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ggToolClass->setStatusBar(statusBar);

        retranslateUi(ggToolClass);
        QObject::connect(textOnOff, SIGNAL(stateChanged(int)), widget, SLOT(s_ShowTextFlagChanged(int)));
        QObject::connect(coordinateList, SIGNAL(cellPressed(int,int)), widget, SLOT(s_TableSelectionChanged(int,int)));
        QObject::connect(saveButton, SIGNAL(clicked()), ggToolClass, SLOT(s_Save()));
        QObject::connect(pointSize, SIGNAL(valueChanged(int)), widget, SLOT(s_PointSizeChanged(int)));

        QMetaObject::connectSlotsByName(ggToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *ggToolClass)
    {
        ggToolClass->setWindowTitle(QApplication::translate("ggToolClass", "ggTool", 0));
        textOnOff->setText(QApplication::translate("ggToolClass", "\343\203\206\343\202\255\343\202\271\343\203\210\350\241\250\347\244\272", 0));
        saveButton->setText(QApplication::translate("ggToolClass", "\343\202\263\343\203\241\343\203\263\343\203\210\343\202\222\344\277\235\345\255\230", 0));
        pointSizeLabel->setText(QApplication::translate("ggToolClass", "\347\202\271\343\201\256\345\244\247\343\201\215\343\201\225", 0));
    } // retranslateUi

};

namespace Ui {
    class ggToolClass: public Ui_ggToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GGTOOL_H
