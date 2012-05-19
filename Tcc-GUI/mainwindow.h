#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>
#include "ui_mainwindow.h"
#include "Controller.h"
#include <vector>
#include "constants.h"
#include "Utils.h"

class Supervisor; //For circular dependencies

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

	//void setControllersAndMutex(std::vector<Controller *> *, QMutex *);

private:
	Ui::MainWindowClass ui;
	QTimer *timer; //Deleted in this class
	//std::vector<Controller *> *controllers; //Deleted in supervisor
	//QMutex *mutexControllerList; //Deleted in supervisor
	int currentRowController; //Current selected controller
	int currentRowStreet;

	void updateInterface(Controller *);
	void listControllersInTheList(std::vector<Controller *> );
	void setPhaseInTheGui(Phase *);
	void setProgramInTheGui(ControllerLogic *);
	void updateStreetProps(Street);
	QString setColorForStreetSituation(QString);

private slots:
	void timeoutUpdateUI();
	void listClick(QListWidgetItem *);
	void listClickStreets(QListWidgetItem *);
	void phaseSelected(int);
	//void btnRefresh();
	void programSelected(int);
	
};

#endif // MAINWINDOW_H
