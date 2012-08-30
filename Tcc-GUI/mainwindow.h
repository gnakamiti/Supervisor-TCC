#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtGui/QMainWindow>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>
#include <QMessageBox>
#include <QInputDialog>
#include <QWebFrame>
#include "ui_mainwindow.h"
#include "Controller.h"
#include <vector>
#include <string>
#include "constants.h"
#include "Utils.h"
#include "ui_Gmaps.h"
#include "ControllerCFG.h"

class Supervisor; //For circular dependencies

//Google maps hack - Funfionar perfeitamente
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



private:
	Ui::MainWindowClass ui;
	QWidget *mapWidget;
	QTimer *timer; //Deleted in this class
	int currentRowController; //Current selected controller
	int currentRowStreet;
	bool newProgramFlag;

	myWebPage *webPage;

	void updateInterfaceGeneralInfo(Controller *);
	void updateInterfaceCommands(Controller *);
	void listControllersInTheList(std::vector<Controller *> );
	void setPhaseInTheGui(Phase *);
	void setProgramInTheGui(ControllerLogic *);
	void updateStreetProps(Street);
	QString setColorForStreetSituation(QString);
	void updateGoogleMapsMarker(QString, QString, QString);

	void updateTrafficLight(Controller *);

	void updateInterface(Controller *);

	ControllerLogic *  createProgram(std::string);

	std::vector<QTableWidgetItem *> getAllElementsFromPhasesTable();
	std::vector<int> getOnlyDurations(std::vector<QTableWidgetItem*>);
	

private slots:
	void timeoutUpdateUI();
	void listClick(QListWidgetItem *);
	void listClickProgram(QListWidgetItem *);
	void listClickStreets(QListWidgetItem *);
	void phaseSelected(int);
	void programSelected(int);
	void initializeMap(bool);
	void btnSendClick(void);
	void btnCancelClick(void);
	void btnNewClick(void);

public slots:
		void mainFrame_javaScriptWindowObjectCleared();
		void logControllerSituation(QString s);
		void logFitness(QString s);
		void logQueue(QString s);
		void logPrograms(QString s);
};



#endif // MAINWINDOW_H
