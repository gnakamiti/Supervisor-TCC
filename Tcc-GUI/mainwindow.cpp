#include "mainwindow.h"
#include "Supervisor.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	std::vector<Controller *> controllers;

	ui.setupUi(this);
	timer = new QTimer(this);
	ui.listWidget->setSortingEnabled(true);
    
	//connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeoutCheckControllersAlive()));
	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listClick(QListWidgetItem *)));
	connect(ui.btnRefresh, SIGNAL(click()), this, SLOT(btnRefresh()));

	currentRow = -1;



	Supervisor::getInstance()->getControllersListClone(&controllers);
	this->listControllersInTheList(controllers);
	deleteInVector(controllers);


}
//Set the controller props in the GUI
void MainWindow::listClick(QListWidgetItem * item)
{

	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);

	currentRow = ui.listWidget->currentRow();
	this->updateInterface(controllers.at(currentRow));
	deleteInVector(controllers);
	
	
}

void MainWindow::phaseSelected(int index)
{
	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);

	this->setPhaseInTheGui(controllers.at(this->currentRow)->getLogics().at(ui.comboProgram->currentIndex())->phases->at(index));	
	deleteInVector(controllers);
	
}
void MainWindow::programSelected(int index)
{
	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);

	this->setProgramInTheGui(controllers.at(this->currentRow)->getLogics().at(index));
	deleteInVector(controllers);
	
}

void MainWindow::setProgramInTheGui(ControllerLogic *logic)
{
	QString qString;
	//ui.txtCurrentPhase->setText(QString::number(logic->currentPhaseIndex));
	qString = logic->subID.c_str();

	ui.txtProgramId->setText(qString);
	

	qString = logic->intToStrType().c_str();

	ui.txtProgramType->setText(qString);

	ui.txtCurrentPhase->setText(QString::number(logic->currentPhaseIndex));
}

void  MainWindow::setPhaseInTheGui(Phase *phase)
{
	QString qString;
	
	//It's in milisecs
			
	ui.txtPhaseDuration->setText(QString::number((phase->duration / 1000)));
	ui.txtPhaseDuration2->setText(QString::number((phase->duration1 / 1000)));
	ui.txtPhaseDuration3->setText(QString::number((phase->duration2 / 1000)));

	qString = phase->phaseDef.c_str();
	ui.txtPhaseDef->setText(qString);
}

//Just update
void MainWindow::updateInterface(Controller *controller)
{
	QString qString;
	QListWidgetItem *item;
	ControllerLogic *logic;
	Phase *phase;
	std::vector<Phase *> *phases;

	std::vector<std::string> controlledLanes = controller->getControlledLanes();
	std::vector<ControllerLogic *>  logics = controller->getLogics();


	//We need to disconnect the signals or we will have a deadlock!
	//Because when i update the combo box the method the slot method is called!
	disconnect(ui.comboProgramPhase, SIGNAL(currentIndexChanged(int)), this, SLOT(phaseSelected(int)));
	disconnect(ui.comboProgram, SIGNAL(currentIndexChanged(int)), this, SLOT(programSelected(int)));

	ui.txtControllerName->setText(controller->getName().c_str());
	

	ui.listControlledLanes->clear();

	if(controller->isActive())
	{
		ui.lblStatusValue->setText("<font color='green'>Online</font>");
	}
	else
	{
		ui.lblStatusValue->setText("<font color='red'>Offline</font>");
	}

	for(int i = 0; i < controlledLanes.size(); i++)
	{
		qString = controlledLanes.at(i).c_str();

		item = new QListWidgetItem(qString);
		ui.listControlledLanes->addItem(item);
	}


	ui.comboProgram->clear();

	for(int i = 0; i < logics.size(); i++)
	{
		logic = logics.at(i);
		
		
		qString = logic->subID.c_str();
		ui.comboProgram->addItem(qString);
		this->setProgramInTheGui(logic);
		phases = logic->phases;

		ui.comboProgramPhase->clear();

		for(int k = 0; k < phases->size(); k++)
		{
			phase = phases->at(i);
			ui.comboProgramPhase->addItem(QString::number(k));
			this->setPhaseInTheGui(phase);
		}
	}
	//Now we can connect again
	connect(ui.comboProgramPhase, SIGNAL(currentIndexChanged(int)), this, SLOT(phaseSelected(int)));
	connect(ui.comboProgram, SIGNAL(currentIndexChanged(int)), this, SLOT(programSelected(int)));
}
/*
//Check if the controllers are alive!
void MainWindow::timerTimeoutCheckControllersAlive()
{
	//No one can use the controller's list now
	QMutexLocker locker(mutexControllerList);

	//Or a controller went down or a it is up again!
	
	if(this->controllers->size() != this->ui.listWidget->count())
	{
		listControllersInTheList(this->controllers);
	}

	if(this->currentRow != -1)
	{
		this->updateInterface(controllers->at(currentRow));
	}
	//To stop!
	//timer->stop();
}*/

void MainWindow::btnRefresh()
{
	/*
	if(this->currentRow != -1)
	{
		this->updateInterface(controllers->at(currentRow));
	}*/
}

/**
  No need to use mutex here, because when I'm here i already got the lock
  or I guarantee that there is no race conditition!
*/
void MainWindow::listControllersInTheList(std::vector<Controller *> controllers)
{
	QString qString;
	QListWidgetItem *item;

	//QMutexLocker locker(mutexControllerList);
	ui.listWidget->clear();

	for(int row = 0; row < controllers.size(); row++)
	{
		//This conversion is needed because, the class QListWidgetItem just accepts QString :(
		qString = controllers.at(row)->getName().c_str();

		item = new QListWidgetItem(qString);
		ui.listWidget->addItem(item);

		
	}
}
/*
//Setting values
void MainWindow::setControllersAndMutex(std::vector<Controller *> *controllers, QMutex *mutexControllerList)
{

	this->controllers = controllers;
	this->mutexControllerList = mutexControllerList;
	this->listControllersInTheList(this->controllers);
	
}*/

MainWindow::~MainWindow()
{
	if(timer->isActive() == true)
		timer->stop();

	delete timer;
	timer = nullptr;
}
