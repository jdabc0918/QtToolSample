/********************************************************************************
** Form generated from reading UI file 'tttool.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TTTOOL_H
#define UI_TTTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "glview.h"

QT_BEGIN_NAMESPACE

class Ui_ttTool
{
public:
    QTableWidget *pairTable;
    QGraphicsView *graphicsView;
    GLView *widget;
    QListWidget *listWidget;
    QPushButton *autoSelection;
    QPushButton *saveButton;
    QCheckBox *textOnOff;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *pointSizeLabel;
    QSpinBox *pointSize;

    void setupUi(QWidget *ttTool)
    {
        if (ttTool->objectName().isEmpty())
            ttTool->setObjectName(QStringLiteral("ttTool"));
        ttTool->resize(1142, 585);
        pairTable = new QTableWidget(ttTool);
        pairTable->setObjectName(QStringLiteral("pairTable"));
        pairTable->setGeometry(QRect(530, 420, 231, 151));
        graphicsView = new QGraphicsView(ttTool);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(160, 10, 480, 360));
        widget = new GLView(ttTool);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(650, 10, 480, 360));
        listWidget = new QListWidget(ttTool);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 141, 361));
        autoSelection = new QPushButton(ttTool);
        autoSelection->setObjectName(QStringLiteral("autoSelection"));
        autoSelection->setGeometry(QRect(820, 490, 75, 23));
        saveButton = new QPushButton(ttTool);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(820, 530, 75, 23));
        textOnOff = new QCheckBox(ttTool);
        textOnOff->setObjectName(QStringLiteral("textOnOff"));
        textOnOff->setGeometry(QRect(920, 380, 81, 16));
        horizontalLayoutWidget = new QWidget(ttTool);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(1020, 370, 111, 31));
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
        pointSize->setValue(5);

        horizontalLayout->addWidget(pointSize);


        retranslateUi(ttTool);
        QObject::connect(saveButton, SIGNAL(clicked()), ttTool, SLOT(s_Save()));
        QObject::connect(textOnOff, SIGNAL(stateChanged(int)), widget, SLOT(s_ShowTextFlagChanged(int)));
        QObject::connect(pointSize, SIGNAL(valueChanged(int)), widget, SLOT(s_PointSizeChanged(int)));

        QMetaObject::connectSlotsByName(ttTool);
    } // setupUi

    void retranslateUi(QWidget *ttTool)
    {
        ttTool->setWindowTitle(QApplication::translate("ttTool", "ttTool", 0));
        autoSelection->setText(QApplication::translate("ttTool", "\350\207\252\345\213\225\346\216\250\345\256\232", 0));
        saveButton->setText(QApplication::translate("ttTool", "\344\277\235\345\255\230", 0));
        textOnOff->setText(QApplication::translate("ttTool", "\343\203\206\343\202\255\343\202\271\343\203\210\350\241\250\347\244\272", 0));
        pointSizeLabel->setText(QApplication::translate("ttTool", "\347\202\271\343\201\256\345\244\247\343\201\215\343\201\225", 0));
    } // retranslateUi

};

namespace Ui {
    class ttTool: public Ui_ttTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TTTOOL_H
