#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	ui.listWidget->setSortingEnabled(true);
    
	connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeoutCheckControllersAlive()));
	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listClick(QListWidgetItem *)));

	timer->start(TIMER_TIMEOUT);
}
//Set the controller props in the GUI
void MainWindow::listClick(QListWidgetItem * item)
{
	//No one can use the controllers list now!
	QMutexLocker locker(mutex);
	
	this->updateInterface(controllers->at(ui.listWidget->currentRow()));
}

//Just update
void MainWindow::updateInterface(Controller *controller)
{
	QString qString;
	QListWidgetItem *item;
	ControllerLogic *logic;

	std::vector<std::string> controlledLanes = controller->getControlledLanes();
	std::vector<ControllerLogic *>  logics = controller->getLogics();

	ui.txtControllerName->setText(controller->getName().c_str());

	ui.listControlledLanes->clear();

	for(int i = 0; i < controlledLanes.size(); i++)
	{
		qString = controlledLanes.at(i).c_str();

		item = new QListWidgetItem(qString);
		ui.listControlledLanes->addItem(item);
	}

	for(int i = 0; i < logics.size(); i++)
	{
		logic = logics.at(i);
		
		ui.txtCurrentPhase->setText(QString::number(logic->currentPhaseIndex));

		qString = logic->intToStrType().c_str();

		ui.txtOperationType->setText(qString);
	}
}

//Check if the controllers are alive!
void MainWindow::timerTimeoutCheckControllersAlive()
{
	QMutexLocker locker(mutex);

	//Or a controller went down or a it is up again!
	if(this->controllers->size() != this->ui.listWidget->count())
	{
		listControllersInTheList(this->controllers);
	}
	//To stop!
	//timer->stop();
}
/**
  No need to use mutex here, because when I'm here i already got the lock
  or I guarantee that there is no race conditition!
*/
void MainWindow::listControllersInTheList(std::vector<Controller *> *controllers)
{
	QString qString;
	QListWidgetItem *item;
	
	ui.listWidget->clear();

	for(int row = 0; row < controllers->size(); row++)
	{
		//This conversion is needed because, the class QListWidgetItem just accepts QString :(
		qString = controllers->at(row)->getName().c_str();

		item = new QListWidgetItem(qString);
		ui.listWidget->addItem(item);

		
	}
}

//Setting values
void MainWindow::setControllersAndMutex(std::vector<Controller *> *controllers, QMutex *mutex)
{

	this->controllers = controllers;
	this->mutex = mutex;
	this->listControllersInTheList(this->controllers);
	
}

MainWindow::~MainWindow()
{
	if(timer->isActive() == true)
		timer->stop();

	delete timer;
	timer = nullptr;
}
