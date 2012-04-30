#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>
#include "ui_mainwindow.h"
#include "Controller.h"
#include <vector>

#define TIMER_TIMEOUT 5000

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

	void setControllersAndMutex(std::vector<Controller *> *, QMutex *);

private:
	Ui::MainWindowClass ui;
	QTimer *timer; //Deleted in this class
	std::vector<Controller *> *controllers; //Deleted in supervisor
	QMutex *mutex; //Deleted in supervisor

	void updateInterface(Controller *);
	void listControllersInTheList(std::vector<Controller *> *);

private slots:
	void timerTimeoutCheckControllersAlive();
	void listClick(QListWidgetItem *);
	
};

#endif // MAINWINDOW_H
