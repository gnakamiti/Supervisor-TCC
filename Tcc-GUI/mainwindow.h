#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtGui/QMainWindow>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>
#include <QWebFrame>
#include "ui_mainwindow.h"
#include "Controller.h"
#include <vector>
#include "constants.h"
#include "Utils.h"
#include "ui_Gmaps.h"
#include "ControllerCFG.h"

class Supervisor; //For circular dependencies

//Google maps hack
class myWebPage : public QWebPage
{
    virtual QString userAgentForUrl(const QUrl& url) const {
        return "Chrome/1.0";
    }
};

class MainWindow : public QMainWindow
{
	
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();
	//Javascript will call this
	Q_INVOKABLE QStringList getInformationForController(QString);


	//void setControllersAndMutex(std::vector<Controller *> *, QMutex *);

private:
	Ui::MainWindowClass ui;
	//Ui::gMapsForm gMaps;
	QWidget *mapWidget;
	QTimer *timer; //Deleted in this class
	//std::vector<Controller *> *controllers; //Deleted in supervisor
	//QMutex *mutexControllerList; //Deleted in supervisor
	int currentRowController; //Current selected controller
	int currentRowStreet;

	myWebPage *webPage;

	void updateInterface(Controller *);
	void listControllersInTheList(std::vector<Controller *> );
	void setPhaseInTheGui(Phase *);
	void setProgramInTheGui(ControllerLogic *);
	void updateStreetProps(Street);
	QString setColorForStreetSituation(QString);
	void updateGoogleMapsMarker(QString, QString, QString);

	void updateTrafficLight(Controller *);
	

private slots:
	void timeoutUpdateUI();
	void listClick(QListWidgetItem *);
	void listClickStreets(QListWidgetItem *);
	void phaseSelected(int);
	//void btnMapPush();
	//void btnRefresh();
	void programSelected(int);
	void initializeMap(bool);

public slots:
		void mainFrame_javaScriptWindowObjectCleared();
	
	
	
	
};



#endif // MAINWINDOW_H
