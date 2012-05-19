/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat 19. May 17:24:44 2012
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
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
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
    QLabel *lblControlledLanes;
    QListWidget *listControlledLanes;
    QFrame *line;
    QGroupBox *groupBoxControllersProgram;
    QLabel *lblProgramId;
    QLabel *lblProgramType;
    QComboBox *comboProgram;
    QLineEdit *txtProgramId;
    QLineEdit *txtProgramType;
    QLabel *lblAvaliablePrograms;
    QGroupBox *groupBoxPhases;
    QLabel *lblDuration;
    QLineEdit *txtPhaseDuration;
    QLabel *lblDuration2;
    QLineEdit *txtPhaseDuration2;
    QLabel *lblDuration3;
    QLineEdit *txtPhaseDuration3;
    QLabel *lblPhaseDef;
    QLineEdit *txtPhaseDef;
    QLabel *label;
    QComboBox *comboProgramPhase;
    QLineEdit *txtCurrentPhase;
    QLabel *lblCurrentPhase;
    QLabel *lblStatus;
    QLabel *lblStatusValue;
    QLineEdit *txtControllerName;
    QListWidget *listControlledStreets;
    QLabel *lblControlledStreets;
    QLabel *lblQueueSize;
    QLabel *lblCarStream;
    QLabel *lblStreetStatus;
    QLabel *lblStreetStatusValue;
    QLineEdit *txtQueueSize;
    QLineEdit *txtCarStream;
    QPushButton *btnShowMap;
    QMenuBar *menuBar;
    QMenu *menuAbout;
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
        listWidget->setGeometry(QRect(10, 30, 281, 511));
        lblController = new QLabel(centralWidget);
        lblController->setObjectName(QString::fromUtf8("lblController"));
        lblController->setGeometry(QRect(10, 10, 81, 21));
        lblControllerName = new QLabel(centralWidget);
        lblControllerName->setObjectName(QString::fromUtf8("lblControllerName"));
        lblControllerName->setGeometry(QRect(300, 30, 161, 16));
        lblControlledLanes = new QLabel(centralWidget);
        lblControlledLanes->setObjectName(QString::fromUtf8("lblControlledLanes"));
        lblControlledLanes->setGeometry(QRect(630, 60, 141, 21));
        listControlledLanes = new QListWidget(centralWidget);
        listControlledLanes->setObjectName(QString::fromUtf8("listControlledLanes"));
        listControlledLanes->setGeometry(QRect(630, 90, 331, 192));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(300, 370, 671, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBoxControllersProgram = new QGroupBox(centralWidget);
        groupBoxControllersProgram->setObjectName(QString::fromUtf8("groupBoxControllersProgram"));
        groupBoxControllersProgram->setGeometry(QRect(300, 400, 671, 241));
        lblProgramId = new QLabel(groupBoxControllersProgram);
        lblProgramId->setObjectName(QString::fromUtf8("lblProgramId"));
        lblProgramId->setGeometry(QRect(10, 30, 71, 16));
        lblProgramType = new QLabel(groupBoxControllersProgram);
        lblProgramType->setObjectName(QString::fromUtf8("lblProgramType"));
        lblProgramType->setGeometry(QRect(10, 60, 91, 16));
        comboProgram = new QComboBox(groupBoxControllersProgram);
        comboProgram->setObjectName(QString::fromUtf8("comboProgram"));
        comboProgram->setGeometry(QRect(462, 20, 171, 22));
        txtProgramId = new QLineEdit(groupBoxControllersProgram);
        txtProgramId->setObjectName(QString::fromUtf8("txtProgramId"));
        txtProgramId->setGeometry(QRect(110, 30, 113, 22));
        txtProgramId->setReadOnly(true);
        txtProgramType = new QLineEdit(groupBoxControllersProgram);
        txtProgramType->setObjectName(QString::fromUtf8("txtProgramType"));
        txtProgramType->setGeometry(QRect(110, 60, 113, 22));
        txtProgramType->setReadOnly(true);
        lblAvaliablePrograms = new QLabel(groupBoxControllersProgram);
        lblAvaliablePrograms->setObjectName(QString::fromUtf8("lblAvaliablePrograms"));
        lblAvaliablePrograms->setGeometry(QRect(320, 20, 131, 20));
        groupBoxPhases = new QGroupBox(groupBoxControllersProgram);
        groupBoxPhases->setObjectName(QString::fromUtf8("groupBoxPhases"));
        groupBoxPhases->setGeometry(QRect(10, 80, 661, 151));
        lblDuration = new QLabel(groupBoxPhases);
        lblDuration->setObjectName(QString::fromUtf8("lblDuration"));
        lblDuration->setGeometry(QRect(10, 30, 61, 16));
        txtPhaseDuration = new QLineEdit(groupBoxPhases);
        txtPhaseDuration->setObjectName(QString::fromUtf8("txtPhaseDuration"));
        txtPhaseDuration->setGeometry(QRect(90, 30, 113, 22));
        txtPhaseDuration->setReadOnly(true);
        lblDuration2 = new QLabel(groupBoxPhases);
        lblDuration2->setObjectName(QString::fromUtf8("lblDuration2"));
        lblDuration2->setGeometry(QRect(10, 70, 71, 16));
        txtPhaseDuration2 = new QLineEdit(groupBoxPhases);
        txtPhaseDuration2->setObjectName(QString::fromUtf8("txtPhaseDuration2"));
        txtPhaseDuration2->setGeometry(QRect(90, 70, 113, 22));
        txtPhaseDuration2->setReadOnly(true);
        lblDuration3 = new QLabel(groupBoxPhases);
        lblDuration3->setObjectName(QString::fromUtf8("lblDuration3"));
        lblDuration3->setGeometry(QRect(10, 110, 71, 16));
        txtPhaseDuration3 = new QLineEdit(groupBoxPhases);
        txtPhaseDuration3->setObjectName(QString::fromUtf8("txtPhaseDuration3"));
        txtPhaseDuration3->setGeometry(QRect(90, 110, 113, 22));
        txtPhaseDuration3->setReadOnly(true);
        lblPhaseDef = new QLabel(groupBoxPhases);
        lblPhaseDef->setObjectName(QString::fromUtf8("lblPhaseDef"));
        lblPhaseDef->setGeometry(QRect(250, 30, 101, 16));
        txtPhaseDef = new QLineEdit(groupBoxPhases);
        txtPhaseDef->setObjectName(QString::fromUtf8("txtPhaseDef"));
        txtPhaseDef->setGeometry(QRect(360, 30, 261, 22));
        txtPhaseDef->setReadOnly(true);
        label = new QLabel(groupBoxPhases);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 110, 101, 16));
        comboProgramPhase = new QComboBox(groupBoxPhases);
        comboProgramPhase->setObjectName(QString::fromUtf8("comboProgramPhase"));
        comboProgramPhase->setGeometry(QRect(360, 110, 171, 22));
        txtCurrentPhase = new QLineEdit(groupBoxControllersProgram);
        txtCurrentPhase->setObjectName(QString::fromUtf8("txtCurrentPhase"));
        txtCurrentPhase->setGeometry(QRect(460, 50, 171, 22));
        lblCurrentPhase = new QLabel(groupBoxControllersProgram);
        lblCurrentPhase->setObjectName(QString::fromUtf8("lblCurrentPhase"));
        lblCurrentPhase->setGeometry(QRect(320, 60, 91, 16));
        lblStatus = new QLabel(centralWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(590, 30, 121, 21));
        lblStatusValue = new QLabel(centralWidget);
        lblStatusValue->setObjectName(QString::fromUtf8("lblStatusValue"));
        lblStatusValue->setGeometry(QRect(700, 20, 201, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        lblStatusValue->setFont(font);
        txtControllerName = new QLineEdit(centralWidget);
        txtControllerName->setObjectName(QString::fromUtf8("txtControllerName"));
        txtControllerName->setGeometry(QRect(380, 30, 151, 22));
        txtControllerName->setReadOnly(true);
        listControlledStreets = new QListWidget(centralWidget);
        listControlledStreets->setObjectName(QString::fromUtf8("listControlledStreets"));
        listControlledStreets->setGeometry(QRect(300, 90, 301, 192));
        lblControlledStreets = new QLabel(centralWidget);
        lblControlledStreets->setObjectName(QString::fromUtf8("lblControlledStreets"));
        lblControlledStreets->setGeometry(QRect(300, 60, 111, 16));
        lblQueueSize = new QLabel(centralWidget);
        lblQueueSize->setObjectName(QString::fromUtf8("lblQueueSize"));
        lblQueueSize->setGeometry(QRect(310, 310, 71, 16));
        lblCarStream = new QLabel(centralWidget);
        lblCarStream->setObjectName(QString::fromUtf8("lblCarStream"));
        lblCarStream->setGeometry(QRect(310, 350, 71, 16));
        lblStreetStatus = new QLabel(centralWidget);
        lblStreetStatus->setObjectName(QString::fromUtf8("lblStreetStatus"));
        lblStreetStatus->setGeometry(QRect(590, 310, 91, 20));
        lblStreetStatusValue = new QLabel(centralWidget);
        lblStreetStatusValue->setObjectName(QString::fromUtf8("lblStreetStatusValue"));
        lblStreetStatusValue->setGeometry(QRect(690, 300, 201, 31));
        lblStreetStatusValue->setFont(font);
        txtQueueSize = new QLineEdit(centralWidget);
        txtQueueSize->setObjectName(QString::fromUtf8("txtQueueSize"));
        txtQueueSize->setGeometry(QRect(400, 310, 113, 22));
        txtQueueSize->setReadOnly(true);
        txtCarStream = new QLineEdit(centralWidget);
        txtCarStream->setObjectName(QString::fromUtf8("txtCarStream"));
        txtCarStream->setGeometry(QRect(400, 350, 113, 22));
        txtCarStream->setReadOnly(true);
        btnShowMap = new QPushButton(centralWidget);
        btnShowMap->setObjectName(QString::fromUtf8("btnShowMap"));
        btnShowMap->setGeometry(QRect(10, 550, 121, 51));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("map2.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnShowMap->setIcon(icon1);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 978, 26));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuAbout->menuAction());

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Supervision of controllers ", 0, QApplication::UnicodeUTF8));
        lblController->setText(QApplication::translate("MainWindowClass", "Controllers", 0, QApplication::UnicodeUTF8));
        lblControllerName->setText(QApplication::translate("MainWindowClass", "Controller ID:", 0, QApplication::UnicodeUTF8));
        lblControlledLanes->setText(QApplication::translate("MainWindowClass", "Controlled Lanes:", 0, QApplication::UnicodeUTF8));
        groupBoxControllersProgram->setTitle(QApplication::translate("MainWindowClass", "Controller's Program", 0, QApplication::UnicodeUTF8));
        lblProgramId->setText(QApplication::translate("MainWindowClass", "Program ID:", 0, QApplication::UnicodeUTF8));
        lblProgramType->setText(QApplication::translate("MainWindowClass", "Program Type:", 0, QApplication::UnicodeUTF8));
        lblAvaliablePrograms->setText(QApplication::translate("MainWindowClass", "Avaliable Programs:", 0, QApplication::UnicodeUTF8));
        groupBoxPhases->setTitle(QApplication::translate("MainWindowClass", "Phases", 0, QApplication::UnicodeUTF8));
        lblDuration->setText(QApplication::translate("MainWindowClass", "Duration:", 0, QApplication::UnicodeUTF8));
        lblDuration2->setText(QApplication::translate("MainWindowClass", "Duration 2:", 0, QApplication::UnicodeUTF8));
        lblDuration3->setText(QApplication::translate("MainWindowClass", "Duration 3:", 0, QApplication::UnicodeUTF8));
        lblPhaseDef->setText(QApplication::translate("MainWindowClass", "Phase Definition:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowClass", "Avaliable Phases:", 0, QApplication::UnicodeUTF8));
        lblCurrentPhase->setText(QApplication::translate("MainWindowClass", "Current Phase:", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("MainWindowClass", "Controller Status:", 0, QApplication::UnicodeUTF8));
        lblStatusValue->setText(QString());
        lblControlledStreets->setText(QApplication::translate("MainWindowClass", "Controlled Streets:", 0, QApplication::UnicodeUTF8));
        lblQueueSize->setText(QApplication::translate("MainWindowClass", "Queue Size:", 0, QApplication::UnicodeUTF8));
        lblCarStream->setText(QApplication::translate("MainWindowClass", "Car Stream:", 0, QApplication::UnicodeUTF8));
        lblStreetStatus->setText(QApplication::translate("MainWindowClass", "Street Status:", 0, QApplication::UnicodeUTF8));
        lblStreetStatusValue->setText(QString());
        btnShowMap->setText(QApplication::translate("MainWindowClass", "Map", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindowClass", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
