/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed 4. Jul 18:05:12 2012
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
#include <QtGui/QComboBox>
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
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QLabel *lblController;
    QTabWidget *tabWidget;
    QWidget *tab;
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
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QListWidget *listControlledStreets;
    QListWidget *listControlledLanes;
    QLabel *lblControlledStreets;
    QLabel *lblControlledLanes;
    QLabel *lblStatusValue;
    QLabel *lblStatus;
    QLineEdit *txtControllerName;
    QLabel *lblControllerName;
    QLabel *lblStreetStatus;
    QLabel *lblStreetStatusValue;
    QLabel *lblQueueSize;
    QLineEdit *txtQueueSize;
    QLabel *lblCarStream;
    QLineEdit *txtCarStream;
    QLabel *lblTL1;
    QLabel *lblTL2;
    QLabel *lblControlledStreet1;
    QLabel *lblControlledStreet2;
    QLabel *label_2;
    QLineEdit *txtCurrentProgram;
    QLabel *lblCurrentPhase;
    QLineEdit *txtCurrentPhase;
    QWidget *tab_3;
    QLabel *label_7;
    QLineEdit *txtControllerCommand;
    QPushButton *btnSend;
    QPushButton *btnCancel;
    QCheckBox *checkBoxOffOn;
    QLabel *label_6;
    QListWidget *listPrograms;
    QLabel *label_8;
    QTableWidget *tablePhases;
    QLabel *label_9;
    QPushButton *btnNew;
    QWidget *tab_2;
    QWebView *gMaps;
    QMenuBar *menuBar;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(1413, 745);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MainWindow/images/appIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 30, 261, 641));
        lblController = new QLabel(centralWidget);
        lblController->setObjectName(QString::fromUtf8("lblController"));
        lblController->setGeometry(QRect(10, 10, 81, 21));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(280, 0, 1121, 681));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBoxControllersProgram = new QGroupBox(tab);
        groupBoxControllersProgram->setObjectName(QString::fromUtf8("groupBoxControllersProgram"));
        groupBoxControllersProgram->setGeometry(QRect(20, 400, 941, 241));
        lblProgramId = new QLabel(groupBoxControllersProgram);
        lblProgramId->setObjectName(QString::fromUtf8("lblProgramId"));
        lblProgramId->setGeometry(QRect(10, 30, 71, 16));
        lblProgramType = new QLabel(groupBoxControllersProgram);
        lblProgramType->setObjectName(QString::fromUtf8("lblProgramType"));
        lblProgramType->setGeometry(QRect(10, 60, 91, 16));
        comboProgram = new QComboBox(groupBoxControllersProgram);
        comboProgram->setObjectName(QString::fromUtf8("comboProgram"));
        comboProgram->setGeometry(QRect(730, 20, 171, 22));
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
        lblAvaliablePrograms->setGeometry(QRect(580, 20, 131, 20));
        groupBoxPhases = new QGroupBox(groupBoxControllersProgram);
        groupBoxPhases->setObjectName(QString::fromUtf8("groupBoxPhases"));
        groupBoxPhases->setGeometry(QRect(10, 90, 901, 141));
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
        lblPhaseDef->setGeometry(QRect(480, 20, 101, 16));
        txtPhaseDef = new QLineEdit(groupBoxPhases);
        txtPhaseDef->setObjectName(QString::fromUtf8("txtPhaseDef"));
        txtPhaseDef->setGeometry(QRect(600, 20, 261, 22));
        txtPhaseDef->setReadOnly(true);
        label = new QLabel(groupBoxPhases);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(480, 100, 101, 16));
        comboProgramPhase = new QComboBox(groupBoxPhases);
        comboProgramPhase->setObjectName(QString::fromUtf8("comboProgramPhase"));
        comboProgramPhase->setGeometry(QRect(600, 100, 171, 22));
        label_3 = new QLabel(groupBoxPhases);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 30, 53, 16));
        label_4 = new QLabel(groupBoxPhases);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(210, 70, 53, 16));
        label_5 = new QLabel(groupBoxPhases);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(210, 110, 53, 16));
        listControlledStreets = new QListWidget(tab);
        listControlledStreets->setObjectName(QString::fromUtf8("listControlledStreets"));
        listControlledStreets->setGeometry(QRect(40, 170, 301, 192));
        listControlledLanes = new QListWidget(tab);
        listControlledLanes->setObjectName(QString::fromUtf8("listControlledLanes"));
        listControlledLanes->setGeometry(QRect(400, 170, 331, 192));
        lblControlledStreets = new QLabel(tab);
        lblControlledStreets->setObjectName(QString::fromUtf8("lblControlledStreets"));
        lblControlledStreets->setGeometry(QRect(10, 140, 111, 16));
        lblControlledLanes = new QLabel(tab);
        lblControlledLanes->setObjectName(QString::fromUtf8("lblControlledLanes"));
        lblControlledLanes->setGeometry(QRect(400, 140, 141, 21));
        lblStatusValue = new QLabel(tab);
        lblStatusValue->setObjectName(QString::fromUtf8("lblStatusValue"));
        lblStatusValue->setGeometry(QRect(130, 50, 201, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        lblStatusValue->setFont(font);
        lblStatus = new QLabel(tab);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(10, 50, 121, 21));
        txtControllerName = new QLineEdit(tab);
        txtControllerName->setObjectName(QString::fromUtf8("txtControllerName"));
        txtControllerName->setGeometry(QRect(100, 10, 151, 22));
        txtControllerName->setReadOnly(true);
        lblControllerName = new QLabel(tab);
        lblControllerName->setObjectName(QString::fromUtf8("lblControllerName"));
        lblControllerName->setGeometry(QRect(10, 10, 161, 16));
        lblStreetStatus = new QLabel(tab);
        lblStreetStatus->setObjectName(QString::fromUtf8("lblStreetStatus"));
        lblStreetStatus->setGeometry(QRect(10, 90, 91, 20));
        lblStreetStatusValue = new QLabel(tab);
        lblStreetStatusValue->setObjectName(QString::fromUtf8("lblStreetStatusValue"));
        lblStreetStatusValue->setGeometry(QRect(100, 80, 201, 31));
        lblStreetStatusValue->setFont(font);
        lblQueueSize = new QLabel(tab);
        lblQueueSize->setObjectName(QString::fromUtf8("lblQueueSize"));
        lblQueueSize->setGeometry(QRect(460, 20, 71, 16));
        txtQueueSize = new QLineEdit(tab);
        txtQueueSize->setObjectName(QString::fromUtf8("txtQueueSize"));
        txtQueueSize->setGeometry(QRect(570, 20, 113, 22));
        txtQueueSize->setReadOnly(true);
        lblCarStream = new QLabel(tab);
        lblCarStream->setObjectName(QString::fromUtf8("lblCarStream"));
        lblCarStream->setGeometry(QRect(460, 50, 71, 16));
        txtCarStream = new QLineEdit(tab);
        txtCarStream->setObjectName(QString::fromUtf8("txtCarStream"));
        txtCarStream->setGeometry(QRect(570, 50, 113, 22));
        txtCarStream->setReadOnly(true);
        lblTL1 = new QLabel(tab);
        lblTL1->setObjectName(QString::fromUtf8("lblTL1"));
        lblTL1->setGeometry(QRect(750, 180, 139, 160));
        lblTL2 = new QLabel(tab);
        lblTL2->setObjectName(QString::fromUtf8("lblTL2"));
        lblTL2->setGeometry(QRect(920, 180, 139, 160));
        lblControlledStreet1 = new QLabel(tab);
        lblControlledStreet1->setObjectName(QString::fromUtf8("lblControlledStreet1"));
        lblControlledStreet1->setGeometry(QRect(750, 140, 161, 16));
        lblControlledStreet2 = new QLabel(tab);
        lblControlledStreet2->setObjectName(QString::fromUtf8("lblControlledStreet2"));
        lblControlledStreet2->setGeometry(QRect(920, 140, 181, 16));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(460, 80, 101, 16));
        txtCurrentProgram = new QLineEdit(tab);
        txtCurrentProgram->setObjectName(QString::fromUtf8("txtCurrentProgram"));
        txtCurrentProgram->setGeometry(QRect(570, 80, 113, 22));
        txtCurrentProgram->setReadOnly(true);
        lblCurrentPhase = new QLabel(tab);
        lblCurrentPhase->setObjectName(QString::fromUtf8("lblCurrentPhase"));
        lblCurrentPhase->setGeometry(QRect(460, 110, 91, 16));
        txtCurrentPhase = new QLineEdit(tab);
        txtCurrentPhase->setObjectName(QString::fromUtf8("txtCurrentPhase"));
        txtCurrentPhase->setGeometry(QRect(570, 110, 113, 22));
        txtCurrentPhase->setReadOnly(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MainWindow/images/network.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon1, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 20, 71, 16));
        txtControllerCommand = new QLineEdit(tab_3);
        txtControllerCommand->setObjectName(QString::fromUtf8("txtControllerCommand"));
        txtControllerCommand->setGeometry(QRect(90, 20, 161, 22));
        txtControllerCommand->setReadOnly(true);
        btnSend = new QPushButton(tab_3);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setGeometry(QRect(20, 580, 121, 51));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/MainWindow/images/send.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSend->setIcon(icon2);
        btnCancel = new QPushButton(tab_3);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(300, 580, 121, 51));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/MainWindow/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon3);
        checkBoxOffOn = new QCheckBox(tab_3);
        checkBoxOffOn->setObjectName(QString::fromUtf8("checkBoxOffOn"));
        checkBoxOffOn->setGeometry(QRect(90, 60, 81, 20));
        checkBoxOffOn->setChecked(true);
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 60, 53, 16));
        listPrograms = new QListWidget(tab_3);
        listPrograms->setObjectName(QString::fromUtf8("listPrograms"));
        listPrograms->setGeometry(QRect(10, 140, 431, 181));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 110, 71, 16));
        tablePhases = new QTableWidget(tab_3);
        tablePhases->setObjectName(QString::fromUtf8("tablePhases"));
        tablePhases->setGeometry(QRect(10, 380, 901, 192));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 350, 51, 16));
        btnNew = new QPushButton(tab_3);
        btnNew->setObjectName(QString::fromUtf8("btnNew"));
        btnNew->setGeometry(QRect(160, 580, 121, 51));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/MainWindow/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNew->setIcon(icon4);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/MainWindow/images/control.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_3, icon5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gMaps = new QWebView(tab_2);
        gMaps->setObjectName(QString::fromUtf8("gMaps"));
        gMaps->setGeometry(QRect(0, 0, 1131, 651));
        gMaps->setUrl(QUrl(QString::fromUtf8("about:blank")));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/MainWindow/images/map2.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_2, icon6, QString());
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1413, 26));
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

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Supervision of controllers ", 0, QApplication::UnicodeUTF8));
        lblController->setText(QApplication::translate("MainWindowClass", "Controllers", 0, QApplication::UnicodeUTF8));
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
        label_3->setText(QApplication::translate("MainWindowClass", "seconds", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindowClass", "seconds", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindowClass", "seconds", 0, QApplication::UnicodeUTF8));
        lblControlledStreets->setText(QApplication::translate("MainWindowClass", "Controlled Streets:", 0, QApplication::UnicodeUTF8));
        lblControlledLanes->setText(QApplication::translate("MainWindowClass", "Controlled Lanes:", 0, QApplication::UnicodeUTF8));
        lblStatusValue->setText(QString());
        lblStatus->setText(QApplication::translate("MainWindowClass", "Controller Status:", 0, QApplication::UnicodeUTF8));
        lblControllerName->setText(QApplication::translate("MainWindowClass", "Controller ID:", 0, QApplication::UnicodeUTF8));
        lblStreetStatus->setText(QApplication::translate("MainWindowClass", "Street Status:", 0, QApplication::UnicodeUTF8));
        lblStreetStatusValue->setText(QString());
        lblQueueSize->setText(QApplication::translate("MainWindowClass", "Queue Size:", 0, QApplication::UnicodeUTF8));
        lblCarStream->setText(QApplication::translate("MainWindowClass", "Car Stream:", 0, QApplication::UnicodeUTF8));
        lblTL1->setText(QString());
        lblTL2->setText(QString());
        lblControlledStreet1->setText(QString());
        lblControlledStreet2->setText(QString());
        label_2->setText(QApplication::translate("MainWindowClass", "Current Program:", 0, QApplication::UnicodeUTF8));
        lblCurrentPhase->setText(QApplication::translate("MainWindowClass", "Current Phase:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindowClass", "General Information", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindowClass", "Controller:", 0, QApplication::UnicodeUTF8));
        btnSend->setText(QApplication::translate("MainWindowClass", "Send", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("MainWindowClass", "Cancel", 0, QApplication::UnicodeUTF8));
        checkBoxOffOn->setText(QApplication::translate("MainWindowClass", "Activated", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindowClass", "Status:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindowClass", "Programs:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindowClass", "Phases:", 0, QApplication::UnicodeUTF8));
        btnNew->setText(QApplication::translate("MainWindowClass", "New", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindowClass", "Commands", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindowClass", "Map", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindowClass", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
