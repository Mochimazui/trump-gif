/********************************************************************************
** Form generated from reading UI file 'trumpgifmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRUMPGIFMAINWINDOW_H
#define UI_TRUMPGIFMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "displaywidget.h"

QT_BEGIN_NAMESPACE

class Ui_TrumpGIFMainWindowClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    DisplayWidget *displayWidget;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *saveButton;
    QPushButton *initButton;
    QFrame *line;
    QComboBox *animationComboBox;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TrumpGIFMainWindowClass)
    {
        if (TrumpGIFMainWindowClass->objectName().isEmpty())
            TrumpGIFMainWindowClass->setObjectName(QStringLiteral("TrumpGIFMainWindowClass"));
        TrumpGIFMainWindowClass->resize(922, 652);
        centralWidget = new QWidget(TrumpGIFMainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        displayWidget = new DisplayWidget(centralWidget);
        displayWidget->setObjectName(QStringLiteral("displayWidget"));

        horizontalLayout->addWidget(displayWidget);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        previousButton = new QPushButton(widget_2);
        previousButton->setObjectName(QStringLiteral("previousButton"));

        verticalLayout->addWidget(previousButton);

        nextButton = new QPushButton(widget_2);
        nextButton->setObjectName(QStringLiteral("nextButton"));

        verticalLayout->addWidget(nextButton);

        saveButton = new QPushButton(widget_2);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        verticalLayout->addWidget(saveButton);

        initButton = new QPushButton(widget_2);
        initButton->setObjectName(QStringLiteral("initButton"));

        verticalLayout->addWidget(initButton);

        line = new QFrame(widget_2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        animationComboBox = new QComboBox(widget_2);
        animationComboBox->setObjectName(QStringLiteral("animationComboBox"));

        verticalLayout->addWidget(animationComboBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget_2);

        horizontalLayout->setStretch(0, 8);
        horizontalLayout->setStretch(1, 1);
        TrumpGIFMainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TrumpGIFMainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 922, 21));
        TrumpGIFMainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TrumpGIFMainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TrumpGIFMainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TrumpGIFMainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TrumpGIFMainWindowClass->setStatusBar(statusBar);

        retranslateUi(TrumpGIFMainWindowClass);

        QMetaObject::connectSlotsByName(TrumpGIFMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *TrumpGIFMainWindowClass)
    {
        TrumpGIFMainWindowClass->setWindowTitle(QApplication::translate("TrumpGIFMainWindowClass", "TrumpGIFMainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("TrumpGIFMainWindowClass", "Frame", Q_NULLPTR));
        previousButton->setText(QApplication::translate("TrumpGIFMainWindowClass", "\342\206\220", Q_NULLPTR));
        nextButton->setText(QApplication::translate("TrumpGIFMainWindowClass", "\342\206\222", Q_NULLPTR));
        saveButton->setText(QApplication::translate("TrumpGIFMainWindowClass", "Save", Q_NULLPTR));
        initButton->setText(QApplication::translate("TrumpGIFMainWindowClass", "Init", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TrumpGIFMainWindowClass: public Ui_TrumpGIFMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRUMPGIFMAINWINDOW_H
