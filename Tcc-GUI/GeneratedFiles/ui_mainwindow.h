/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun 29. Apr 22:22:30 2012
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
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QLabel *lblController;
    QLabel *lblControllerName;
    QTextEdit *txtControllerName;
    QLabel *lblControlledLanes;
    QListWidget *listControlledLanes;
    QFrame *line;
    QGroupBox *groupBoxControllersProgram;
    QLabel *lblCurrentPhase;
    QLineEdit *txtCurrentPhase;
    QLabel *lblOperationType;
    QLineEdit *txtOperationType;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(978, 711);
        QIcon icon;
        icon.addFile(QString::fromUtf8("appIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 70, 281, 521));
        lblController = new QLabel(centralWidget);
        lblController->setObjectName(QString::fromUtf8("lblController"));
        lblController->setGeometry(QRect(10, 50, 81, 21));
        lblControllerName = new QLabel(centralWidget);
        lblControllerName->setObjectName(QString::fromUtf8("lblControllerName"));
        lblControllerName->setGeometry(QRect(300, 70, 161, 16));
        txtControllerName = new QTextEdit(centralWidget);
        txtControllerName->setObjectName(QString::fromUtf8("txtControllerName"));
        txtControllerName->setGeometry(QRect(380, 60, 251, 31));
        txtControllerName->setReadOnly(true);
        lblControlledLanes = new QLabel(centralWidget);
        lblControlledLanes->setObjectName(QString::fromUtf8("lblControlledLanes"));
        lblControlledLanes->setGeometry(QRect(300, 100, 141, 21));
        listControlledLanes = new QListWidget(centralWidget);
        listControlledLanes->setObjectName(QString::fromUtf8("listControlledLanes"));
        listControlledLanes->setGeometry(QRect(300, 120, 331, 192));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(300, 320, 671, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBoxControllersProgram = new QGroupBox(centralWidget);
        groupBoxControllersProgram->setObjectName(QString::fromUtf8("groupBoxControllersProgram"));
        groupBoxControllersProgram->setGeometry(QRect(300, 340, 671, 301));
        lblCurrentPhase = new QLabel(groupBoxControllersProgram);
        lblCurrentPhase->setObjectName(QString::fromUtf8("lblCurrentPhase"));
        lblCurrentPhase->setGeometry(QRect(10, 30, 91, 16));
        txtCurrentPhase = new QLineEdit(groupBoxControllersProgram);
        txtCurrentPhase->setObjectName(QString::fromUtf8("txtCurrentPhase"));
        txtCurrentPhase->setGeometry(QRect(120, 30, 131, 22));
        txtCurrentPhase->setReadOnly(true);
        lblOperationType = new QLabel(groupBoxControllersProgram);
        lblOperationType->setObjectName(QString::fromUtf8("lblOperationType"));
        lblOperationType->setGeometry(QRect(10, 60, 91, 21));
        txtOperationType = new QLineEdit(groupBoxControllersProgram);
        txtOperationType->setObjectName(QString::fromUtf8("txtOperationType"));
        txtOperationType->setGeometry(QRect(120, 60, 131, 22));
        txtOperationType->setReadOnly(true);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 978, 26));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Sistema de supervis\303\243o de controladores", 0, QApplication::UnicodeUTF8));
        lblController->setText(QApplication::translate("MainWindowClass", "Controllers", 0, QApplication::UnicodeUTF8));
        lblControllerName->setText(QApplication::translate("MainWindowClass", "Controller ID:", 0, QApplication::UnicodeUTF8));
        lblControlledLanes->setText(QApplication::translate("MainWindowClass", "Controlled Lanes:", 0, QApplication::UnicodeUTF8));
        groupBoxControllersProgram->setTitle(QApplication::translate("MainWindowClass", "Controller's Program", 0, QApplication::UnicodeUTF8));
        lblCurrentPhase->setText(QApplication::translate("MainWindowClass", "Current Phase:", 0, QApplication::UnicodeUTF8));
        lblOperationType->setText(QApplication::translate("MainWindowClass", "Operation Type:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
