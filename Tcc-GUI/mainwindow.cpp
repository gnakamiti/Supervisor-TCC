#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	timer = new QTimer(this);
    
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listClick(QListWidgetItem *)));

	timer->start(TIMER_TIMEOUT);
}
void MainWindow::listClick(QListWidgetItem * item)
{
	int x = 10;
}

//TODO TIMEOUT!	- update controllers information
void MainWindow::timerTimeout()
{
	int x = 10;

	//To stop!
	//timer->stop();
}

void MainWindow::getControllers(std::vector<Controller *> controllers)
{
	QString qString;
	QListWidgetItem *item;
	ui.listWidget->setSortingEnabled(true);

	for(int row = 0; row < controllers.size(); row++)
	{
		//This conversion is needed because, the class QListWidgetItem just accepts QString :(
		qString = controllers.at(row)->getName().c_str();

		item = new QListWidgetItem(qString);
		ui.listWidget->addItem(item);

		
	}
	
}

MainWindow::~MainWindow()
{
	if(timer->isActive() == true)
		timer->stop();

	delete timer;
	timer = nullptr;
}
