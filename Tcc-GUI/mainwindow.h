#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include "ui_mainwindow.h"
#include "Controller.h"

#define TIMER_TIMEOUT 5000

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

	void getControllers(std::vector<Controller *>);

private:
	Ui::MainWindowClass ui;
	QTimer *timer;

private slots:
	void timerTimeout();
	void listClick(QListWidgetItem *);
};

#endif // MAINWINDOW_H
