/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QFormLayout *formLayout_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_SSID;
    QLabel *label_MAC;
    QLabel *label_allFrames;
    QLabel *label_checkSum;
    QLabel *label_dataFrames;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_SetLog;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Start;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_SaveToFile;
    QSpacerItem *horizontalSpacer_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(806, 416);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 60));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 60));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 60));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 60));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 30));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(0, 30));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_6);

        label_SSID = new QLabel(centralWidget);
        label_SSID->setObjectName(QString::fromUtf8("label_SSID"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, label_SSID);

        label_MAC = new QLabel(centralWidget);
        label_MAC->setObjectName(QString::fromUtf8("label_MAC"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, label_MAC);


        formLayout_2->setLayout(3, QFormLayout::FieldRole, formLayout_3);

        label_allFrames = new QLabel(centralWidget);
        label_allFrames->setObjectName(QString::fromUtf8("label_allFrames"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, label_allFrames);

        label_checkSum = new QLabel(centralWidget);
        label_checkSum->setObjectName(QString::fromUtf8("label_checkSum"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, label_checkSum);

        label_dataFrames = new QLabel(centralWidget);
        label_dataFrames->setObjectName(QString::fromUtf8("label_dataFrames"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, label_dataFrames);


        verticalLayout->addLayout(formLayout_2);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_SetLog = new QPushButton(widget);
        pushButton_SetLog->setObjectName(QString::fromUtf8("pushButton_SetLog"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_SetLog->sizePolicy().hasHeightForWidth());
        pushButton_SetLog->setSizePolicy(sizePolicy1);
        pushButton_SetLog->setMinimumSize(QSize(200, 0));
        pushButton_SetLog->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(pushButton_SetLog);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Start = new QPushButton(widget);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));
        sizePolicy1.setHeightForWidth(pushButton_Start->sizePolicy().hasHeightForWidth());
        pushButton_Start->setSizePolicy(sizePolicy1);
        pushButton_Start->setMinimumSize(QSize(200, 0));
        pushButton_Start->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(pushButton_Start);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_SaveToFile = new QPushButton(widget);
        pushButton_SaveToFile->setObjectName(QString::fromUtf8("pushButton_SaveToFile"));
        sizePolicy1.setHeightForWidth(pushButton_SaveToFile->sizePolicy().hasHeightForWidth());
        pushButton_SaveToFile->setSizePolicy(sizePolicy1);
        pushButton_SaveToFile->setMinimumSize(QSize(200, 0));
        pushButton_SaveToFile->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(pushButton_SaveToFile);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(widget);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 806, 26));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);
        QObject::connect(pushButton_SetLog, SIGNAL(clicked()), MainWindowClass, SLOT(setLogButtonClicked()));
        QObject::connect(pushButton_Start, SIGNAL(clicked()), MainWindowClass, SLOT(startButtonClicked()));
        QObject::connect(pushButton_SaveToFile, SIGNAL(clicked()), MainWindowClass, SLOT(saveToFIleButtonClicked()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QCoreApplication::translate("MainWindowClass", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindowClass", "\320\222\321\201\320\265\320\263\320\276 \321\204\321\200\320\265\320\271\320\274\320\276\320\262 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\260\320\275\320\276:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindowClass", "\320\237\321\200\320\276\321\210\320\273\320\276 \320\272\320\276\320\275\321\202\321\200\320\276\320\273\321\214\320\275\321\203\321\216 \321\201\321\203\320\274\320\274\321\203:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindowClass", "Data \321\204\321\200\320\265\320\271\320\274\320\276\320\262 \320\276\321\202 \320\264\321\200\320\276\320\275\320\260 \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\276:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindowClass", "\320\224\321\200\320\276\320\275:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindowClass", "SSID:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindowClass", "MAC-\320\260\320\264\321\200\320\265\321\201:", nullptr));
        label_SSID->setText(QString());
        label_MAC->setText(QString());
        label_allFrames->setText(QString());
        label_checkSum->setText(QString());
        label_dataFrames->setText(QString());
        pushButton_SetLog->setText(QCoreApplication::translate("MainWindowClass", "\320\227\320\260\320\264\320\260\321\202\321\214 \320\262\321\205\320\276\320\264\320\275\320\276\320\271 \321\204\320\260\320\271\320\273", nullptr));
        pushButton_Start->setText(QCoreApplication::translate("MainWindowClass", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\321\203 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        pushButton_SaveToFile->setText(QCoreApplication::translate("MainWindowClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265 \320\262 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
