#include "mainwindow.h"
#include "Supervisor.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	std::vector<Controller *> controllers;

	ui.setupUi(this);
	timer = new QTimer(this);
	mapWidget = new QWidget();
	newProgramFlag = false;


	webPage = new myWebPage();
	ui.gMaps->setPage(webPage);

	ui.listWidget->setSortingEnabled(false);
	ui.listControlledLanes->setSortingEnabled(false);
	ui.listControlledStreets->setSortingEnabled(false);
	ui.listPrograms->setSortingEnabled(false);
    
	connect(timer, SIGNAL(timeout()), this, SLOT(timeoutUpdateUI()));
	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listClick(QListWidgetItem *)));
	connect(ui.listControlledStreets, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listClickStreets(QListWidgetItem *)));
	connect(ui.listPrograms, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listClickProgram(QListWidgetItem *)));
	connect(ui.checkTurnOffIA, SIGNAL(clicked(bool)), this, SLOT(checkTurnOffIA(void)));
	

	//javascript - load map when everything is ready
	connect(ui.gMaps, SIGNAL(loadFinished(bool)), this, SLOT(initializeMap(bool)));
	//javascript - be able to call c++ from javascript
	connect(ui.gMaps->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(mainFrame_javaScriptWindowObjectCleared()));
	connect(ui.btnSend, SIGNAL(pressed()), this, SLOT(btnSendClick()));
	connect(ui.btnCancel, SIGNAL(pressed()), this, SLOT(btnCancelClick()));
	connect(ui.btnNew, SIGNAL(pressed()), this, SLOT(btnNewClick()));
	connect(ui.txtClear, SIGNAL(pressed()), this, SLOT(btnClearClick(void)));

	
	currentRowController = -1;
	currentRowStreet = -1;


	Supervisor::getInstance()->getControllersListClone(&controllers);
	this->listControllersInTheList(controllers);
	deleteInVector(controllers);

	timer->setInterval(GUI_TIMER_UPDATE_UI);
	timer->start();

	QUrl url(GUI_MAP_FILE_LOCATION);

	ui.gMaps->setUrl(url);

	ui.lblTL1->setTextFormat(Qt::RichText);
	ui.lblTL2->setTextFormat(Qt::RichText);

    ui.lblTL1->setText("<img src=\":/MainWindow/light_red.png\">");
    ui.lblTL2->setText("<img src=\":/MainWindow/light_red.png\">");
	ui.txtFitness->append("Check the log in C:\\@CURRENT_USER@\\logs\\fitness.txt");
	ui.checkTurnOffIA->setVisible(false);
}

void MainWindow::checkTurnOffIA(void)
{
	Supervisor *s = Supervisor::getInstance();

	if (ui.checkTurnOffIA->isChecked())
	{
		ui.checkTurnOffIA->setText("Turn on traffic adaptation");
		s->turnIAOnOff(false);
	}
	else
	{
		ui.checkTurnOffIA->setText("Turn off traffic adaptation");
		s->turnIAOnOff(true);
	}
}

void MainWindow::listClickProgram(QListWidgetItem *item)
{
	QString string;
	QTableWidgetItem *tableItem;
	std::vector<Phase *> *phases = nullptr;
	Phase *p = nullptr;
	int currentRowProgramsList = ui.listPrograms->currentRow();
	std::string title = item->text().toStdString();
	Controller *c;
	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);

	/*New, I didn't send it yet
	if(currentRowProgramsList >= controllers.at(currentRowController)->getLogics().size())
	{
		deleteInVector(controllers);
		return;
	}
	
	phases = controllers.at(currentRowController)->getLogics().at(currentRowProgramsList)->phases;*/
	c = controllers.at(currentRowController);
	std::vector<ControllerLogic * > logics = c->getLogics();
	for(int i = 0; i < logics.size(); i++)
	{
		ControllerLogic *l = logics.at(i);
		if(l->subID.compare(title) == 0)
		{
			phases = l->phases;
			break;
		}
	}

	if (phases == nullptr) 
	{
		std::vector<StoredControllerLogic * >sclv = ControllerLogic::getAllStoredLogicFromLogicBase(c->getName());

		for(int i = 0; i < sclv.size(); i++)
		{
			ControllerLogic * l = sclv.at(i)->getControllerLogic();
			if (l->subID.compare(title) == 0) 
			{
				phases = l->phases;
				sclv.at(i)->getGoodDegree();
				//ui.txtProgramQueueCommand->setText(QString::number(sclv.at(i)->));
				ui.txtProgramGrade->setText(QString::number(sclv.at(i)->getGoodDegree()));
				break;
			}
		}
	}

	ui.tablePhases->setRowCount(phases->size());
	ui.tablePhases->setColumnCount(2);
	ui.tablePhases->setHorizontalHeaderLabels(QString("Phase definition;Duration(seconds);").split(";"));
	ui.tablePhases->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	

	for(int i = 0; i < phases->size(); i++)
	{
		p = phases->at(i);

		string = p->phaseDef.c_str();
		tableItem = new QTableWidgetItem(string);
		tableItem->setFlags(Qt::ItemIsSelectable);
		ui.tablePhases->setItem(i, 0, tableItem);

		string = QString::number(p->duration/1000);
		tableItem = new QTableWidgetItem(string);
		ui.tablePhases->setItem(i, 1, tableItem);
		/*
		string = QString::number(p->duration1/1000);
		tableItem = new QTableWidgetItem(string);
		ui.tablePhases->setItem(i, 2, tableItem);

		string = QString::number(p->duration2/1000);
		tableItem = new QTableWidgetItem(string);
		ui.tablePhases->setItem(i, 3, tableItem);*/
	}

	ui.tablePhases->resizeColumnsToContents();
	ui.tablePhases->horizontalHeader()->setStretchLastSection( true ); 
	deleteInVector(controllers);

}

void MainWindow::btnCancelClick(void)
{
	ui.listPrograms->clear();
	ui.tablePhases->clear();
	ui.txtControllerCommand->setText("");
	ui.txtProgramQueueCommand->setText("");
	ui.txtProgramGrade->setText("");
	ui.checkBoxOffOn->setChecked(false);
	newProgramFlag = false;
}

void MainWindow::btnClearClick(void)
{
	ui.txtControllerSituation->clear();
	ui.txtQueueLog->clear();
	ui.txtProgramLog->clear();
	ui.txtInitPrograms->clear();
	ui.txtProgramQueueCommand->setText("");
	ui.txtProgramGrade->setText("");
	ui.txtFuzzyIn->setText("");
	ui.txtFuzzyOut->setText("");
}

void MainWindow::btnSendClick(void)
{
	std::string currentControllerId, newProgramName;
	QMessageBox msgBox;
	ControllerLogic *logic;

	msgBox.setWindowTitle("Information");
	msgBox.setIcon(QMessageBox::Information);

	currentControllerId = ui.txtControllerCommand->text().trimmed().toStdString();

	if(currentControllerId.compare("") == 0)
	{
		msgBox.setText("You need to select a controller first");
		msgBox.exec();
		return;
	}
	
	//Is checked, so just turn off the controller
	if(ui.checkBoxOffOn->isChecked() == false)
	{
		Supervisor::getInstance()->sendSumoCProgramForController(currentControllerId, "off");
		msgBox.setText("The controller is now offline");
		msgBox.exec();
		return;
	}

    if(ui.listPrograms->currentRow() < 0)
	{
		msgBox.setText("You need to select a program first");
		msgBox.exec();
		return;
	}


	newProgramName = ui.listPrograms->currentItem()->text().trimmed().toStdString();

	if (newProgramFlag == true)
	{
		logic = createProgram(newProgramName, currentControllerId);

		if(logic == nullptr)
		{
			msgBox.setText("A problem occured when I tried to create a new program.");
			msgBox.exec();
			return;
		}

		Supervisor::getInstance()->sendSumoCNewProgramForController(currentControllerId, logic);
		std::string str = "------------";
		str += "\nNew Logic for controller: ";
		str += currentControllerId;
		str += "\nLogic:\n";
		str += logic->toString();
		str += "------------\n";
		SupervisorLog::getInstance()->writeOnNewProgram(str);
		Supervisor::getInstance()->emitLogPrograms(str.c_str());
		delete logic;
		logic = nullptr;
	}
	else
	{
		std::vector<Controller*> controllers;
		Supervisor::getInstance()->getControllersListClone(&controllers);
		Controller *c = controllers.at(currentRowController);
		std::vector<ControllerLogic * > logics = c->getLogics();
		bool found = false;
		for (int i = 0; i < logics.size(); i++)
		{
			if(logics.at(i)->subID.compare(newProgramName) == 0)
			{
				found = true;
				std::string str = "------------";
				str += "\nNew Logic for controller: ";
				str += currentControllerId;
				str += "\nLogic:\n";
				str += logics.at(i)->toString();
				str += "------------\n";
				SupervisorLog::getInstance()->writeOnNewProgram(str);
				Supervisor::getInstance()->emitLogPrograms(str.c_str());
				break;
			}
		}

		if (found)
			Supervisor::getInstance()->sendSumoCProgramForController(currentControllerId, newProgramName);
		else
		{
			std::vector<StoredControllerLogic * >sclv = ControllerLogic::getAllStoredLogicFromLogicBase(c->getName());

			for(int i = 0; i < sclv.size(); i++)
			{
				ControllerLogic * l = sclv.at(i)->getControllerLogic();
				if (l->subID.compare(newProgramName) == 0) 
				{
					Supervisor::getInstance()->sendSumoCNewProgramForController(currentControllerId, l);
					std::string str = "------------";
					str += "\nNew Logic for controller: ";
					str += currentControllerId;
					str += "\nLogic:\n";
					str += l->toString();
					str += "------------\n";
					SupervisorLog::getInstance()->writeOnNewProgram(str);
					Supervisor::getInstance()->emitLogPrograms(str.c_str());
					break;
				}
			}
			
		}
		
	}


	newProgramFlag = false;



	QString str("The program:");
	str = str.append(newProgramName.c_str());
	str = str.append(" was sent!");

	msgBox.setText(str);
	msgBox.exec();
}

ControllerLogic *  MainWindow::createProgram(std::string programName, std::string controllerName)
{
	std::vector<QTableWidgetItem*> myList = getAllElementsFromPhasesTable();
	
	std::vector<int> durations = getOnlyDurations(myList);

	if(durations.size() != 4)
	{
		return nullptr;
	}

	return ControllerLogic::createLogicForSumo(programName, 
		durations.at(0), durations.at(1), durations.at(2), durations.at(3), controllerName);
}

std::vector<int> MainWindow::getOnlyDurations(std::vector<QTableWidgetItem*> myList)
{
	std::vector<int> durations;
	int duration;
	bool ok;

	for(int i = 0; i < myList.size(); i++)
	{
		duration = myList.at(i)->text().trimmed().toInt(&ok);

		if(ok == true)
			durations.push_back(duration);
	}

	return durations;
}

std::vector<QTableWidgetItem *> MainWindow::getAllElementsFromPhasesTable()
{
	int iColumns = ui.tablePhases->columnCount();
    int iRows = ui.tablePhases->rowCount();
    std::vector<QTableWidgetItem*> myList;
     
    for(int i = 0; i < iRows; ++i)
    {
		for(int j = 0; j < iColumns; ++j)
		{
			if(j == 1) //I'm only retriving the duration1
			{
				QTableWidgetItem *widget = ui.tablePhases->item(i, j);
				myList.push_back(widget);
				break;
			}
		}
    }

	return myList;
}

void MainWindow::initializeMap(bool b)
{
	QString function;
	ControllerCFG cfg;
	std::vector<ControllerLatLng> controllersLatLng;
	ControllerLatLng actual;
	controllersLatLng = cfg.getLatLng();

	ui.gMaps->page()->mainFrame()->evaluateJavaScript("initialize()");

	for(int i = 0; i < controllersLatLng.size(); i++)
	{
		actual = controllersLatLng.at(i);
		function = "setController('"+actual.name+"','"+actual.lat+"','"+actual.lng+"')";
		ui.gMaps->page()->mainFrame()->evaluateJavaScript(function);
	}

}

QStringList MainWindow::getInformationForController(QString controllerName)
{
	QStringList valuesToReturn;
	std::vector<Street> *streets;
	Street street;
	Controller * c = Supervisor::getInstance()->
		getControllerByName(controllerName.toStdString());
	
	if(c == nullptr) //I didnt find the controller!
		return valuesToReturn;
	
	streets = c->getControlledStreets();

	for(int i = 0; i < streets->size(); i++)
	{
		street = streets->at(i);

		valuesToReturn.push_back(QString(street.streetName.c_str()));
		valuesToReturn.push_back(QString(street.situation.c_str()));
		valuesToReturn.push_back(QString::number(street.queueSize));
		valuesToReturn.push_back(QString::number(street.carStream));
	}

	delete c;
	c = nullptr;

	return valuesToReturn;
}

void MainWindow::mainFrame_javaScriptWindowObjectCleared() {
    ui.gMaps->page()->mainFrame()->addToJavaScriptWindowObject("qtBridge", this);
}


void MainWindow::updateGoogleMapsMarker(QString controllerName, QString queue, QString stream)
{
	QString  text;

	text = "Controller:"+controllerName
		+"<br>Queue Size is:"+queue+"<br>"
		+"Car Stream:"+stream;

	ui.gMaps->page()->mainFrame()->
		evaluateJavaScript("setLabelForMarker('"+controllerName+"','"+text+"')");
}

//Set the controller props in the GUI
void MainWindow::listClick(QListWidgetItem * item)
{
	this->currentRowStreet = -1;
	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);

	currentRowController = ui.listWidget->currentRow();

	this->updateInterface(controllers.at(currentRowController));
	
	deleteInVector(controllers);
	
	
}

void MainWindow::updateInterfaceCommands(Controller *c)
{
	QString string;
	QListWidgetItem *item;
	ControllerLogic *logic;
	std::vector<StoredControllerLogic *> sclv;

	string = c->getName().c_str();
	std::vector<ControllerLogic *> logics = c->getLogics();

	ui.txtControllerCommand->setText(string);

	if(c->isActive())
	{
		ui.checkBoxOffOn->setChecked(true);
	}
	else
	{
		ui.checkBoxOffOn->setChecked(false);
	}

	ui.listPrograms->clear();

	for(int i = 0; i < logics.size(); i++)
	{
		logic = logics.at(i);

		string = logic->subID.c_str();

		item = new QListWidgetItem(string);

		ui.listPrograms->addItem(item);
	}
	
	sclv = ControllerLogic::getAllStoredLogicFromLogicBase(c->getName());

	for(int i = 0; i < sclv.size(); i++)
	{
		StoredControllerLogic * scl = sclv.at(i);
		string = scl->getControllerLogic()->subID.c_str();
		item = new QListWidgetItem(string);
		ui.listPrograms->addItem(item);
	}

	ui.tablePhases->clear();
}

void MainWindow::btnNewClick(void)
{
	bool ok;
	QListWidgetItem *item;
	std::string currentControllerId;
	std::vector<std::string> phaseDefs;
	QString string;
	QTableWidgetItem *tableItem;

	QMessageBox msgBox;
	msgBox.setWindowTitle("Information");
	msgBox.setIcon(QMessageBox::Information);

	currentControllerId = ui.txtControllerCommand->text().trimmed().toStdString();

	if(currentControllerId.compare("") == 0)
	{
		msgBox.setText("You need to select a controller first");
		msgBox.exec();
		return;
	}

    QString text = QInputDialog::getText(this, tr("New Program"),
                                          tr("Program's name"), QLineEdit::Normal,
                                          "", &ok);
     if(ok && !text.isEmpty())
	 {
		item = new QListWidgetItem(text);
		ui.listPrograms->addItem(item);

		phaseDefs = ControllerLogic::getDefaultPhaseDefForTheSimulation();

		ui.tablePhases->clear();
		ui.tablePhases->setRowCount(phaseDefs.size());
	    ui.tablePhases->setColumnCount(2);

		ui.tablePhases->setHorizontalHeaderLabels(QString("Phase definition;Duration(seconds);").split(";"));

		ui.tablePhases->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	    

		for(int i = 0; i < phaseDefs.size(); i++)
		{
			string = phaseDefs.at(i).c_str();
			tableItem = new QTableWidgetItem(string);
			tableItem->setFlags(Qt::ItemIsSelectable);
			ui.tablePhases->setItem(i, 0, tableItem);

			tableItem = new QTableWidgetItem("");
			ui.tablePhases->setItem(i, 1, tableItem);
		}

		ui.tablePhases->resizeColumnsToContents();
		ui.tablePhases->horizontalHeader()->setStretchLastSection( true ); 
		ui.listPrograms->setCurrentRow((ui.listPrograms->count() - 1));
	 }
	 newProgramFlag = true;
}

void MainWindow::listClickStreets(QListWidgetItem * item)
{
	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);
	currentRowStreet = ui.listControlledStreets->currentRow();
	this->updateStreetProps(controllers.at(currentRowController)->getControlledStreets()->at(currentRowStreet));
	deleteInVector(controllers);
}
QString MainWindow::setColorForStreetSituation(QString situation)
{
	QString color;

	if(situation.compare(FUZZY_OUTPUT_VALUE_SHOW_SCREEN_NOTHING) == 0 ||
		situation.compare(FUZZY_OUTPUT_VALUE_SHOW_SCREEN_SMALL) == 0)
	{
		color = "green";
	}
	else if(situation.compare(FUZZY_OUTPUT_VALUE_SHOW_SCREEN_REGULAR) == 0)
	{
		color = "yellow";
	}
	else
	{
		color = "red";
	}

	return color;
}
void MainWindow::updateStreetProps(Street street)
{
	QString qString;
	QListWidgetItem *item;

	ui.txtCarStream->setText(QString::number(street.carStream));

	ui.txtQueueSize->setText(QString::number(street.queueSize));
	qString = street.situation.c_str();

	ui.lblStreetStatusValue->
		setText("<font color='"+setColorForStreetSituation(qString)+"'>"+qString+"</font>");

	ui.listControlledLanes->clear();

	for(int i = 0; i < street.lanes.size(); i++)
	{
		
		qString = street.lanes.at(i).laneName.c_str();

		item = new QListWidgetItem(qString);
		ui.listControlledLanes->addItem(item);
	}
}

void MainWindow::phaseSelected(int index)
{
	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);

	this->setPhaseInTheGui(controllers.at(this->currentRowController)->getLogics().at(ui.comboProgram->currentIndex())->phases->at(index));	
	deleteInVector(controllers);
	
}
void MainWindow::programSelected(int index)
{
	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);

	this->setProgramInTheGui(controllers.at(this->currentRowController)->getLogics().at(index));
	deleteInVector(controllers);
	
}

void MainWindow::setProgramInTheGui(ControllerLogic *logic)
{
	QString qString;

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
void MainWindow::updateInterfaceGeneralInfo(Controller *controller)
{
	QString qString;
	QListWidgetItem *item;
	ControllerLogic *logic;
	Phase *phase;
	std::vector<Phase *> *phases;
	std::vector<Street> *controlledStreets = controller->getControlledStreets();
	std::vector<ControllerLogic *>  logics = controller->getLogics();



	//We need to disconnect the signals or we will have a deadlock!
	//Because when i update the combo box the method the slot method is called!
	disconnect(ui.comboProgramPhase, SIGNAL(currentIndexChanged(int)), this, SLOT(phaseSelected(int)));
	disconnect(ui.comboProgram, SIGNAL(currentIndexChanged(int)), this, SLOT(programSelected(int)));

	ui.txtControllerName->setText(controller->getName().c_str());
	
	ui.txtQueueSize->setText("");
	ui.txtCarStream->setText("");
	ui.lblStreetStatusValue->setText("");
	ui.listControlledLanes->clear();
	ui.listControlledStreets->clear();
	ui.comboProgramPhase->clear();
	ui.comboProgram->clear();

	if(controller->isActive())
	{
		ui.lblStatusValue->setText("<font color='green'>Online</font>");
	}
	else
	{
		ui.lblStatusValue->setText("<font color='red'>Offline</font>");
	}

	for(int i = 0; i < controlledStreets->size(); i++)
	{
		//controlledStreets->at(i);
		
		qString = controlledStreets->at(i).streetName.c_str();

		item = new QListWidgetItem(qString);
		ui.listControlledStreets->addItem(item);
	}

	if(controlledStreets->size() == 2)
	{
		qString = controlledStreets->at(0).streetName.c_str();
		ui.lblControlledStreet1->setText(qString);
		qString = controlledStreets->at(1).streetName.c_str();
		ui.lblControlledStreet2->setText(qString);
	}

	qString = controller->getCurrentLogicAsString().c_str();
	ui.txtCurrentProgram->setText(qString);

	for(int i = 0; i < logics.size(); i++)
	{
		logic = logics.at(i);

		qString = logic->subID.c_str();
		ui.comboProgram->addItem(qString);
	}

	this->setProgramInTheGui(logic);

	phases = logic->phases;

	for(int k = 0; k < phases->size(); k++)
	{
		phase = phases->at(k);
		ui.comboProgramPhase->addItem(QString::number(k));
	}


	if(logic->subID.compare("off") == 0)
		return;

	this->setPhaseInTheGui(phases->at(logic->currentPhaseIndex));
	ui.comboProgramPhase->setCurrentIndex(logic->currentPhaseIndex);
	//Now we can connect again

	connect(ui.comboProgramPhase, SIGNAL(currentIndexChanged(int)), this, SLOT(phaseSelected(int)));
	connect(ui.comboProgram, SIGNAL(currentIndexChanged(int)), this, SLOT(programSelected(int)));
	
}
/**
  No need to use mutex here, because when I'm here i already got the lock
  or I guarantee that there is no race conditition!
*/
void MainWindow::listControllersInTheList(std::vector<Controller *> controllers)
{
	QString qString;
	QListWidgetItem *item;


	ui.listWidget->clear();

	for(int row = 0; row < controllers.size(); row++)
	{
		//This conversion is needed because, the class QListWidgetItem just accepts QString :(
		qString = controllers.at(row)->getName().c_str();

		item = new QListWidgetItem(qString);
		ui.listWidget->addItem(item);

		
	}
}


void MainWindow::timeoutUpdateUI()
{
	std::vector<Controller *> controllers;
	Supervisor::getInstance()->getControllersListClone(&controllers);

	if(this->currentRowController != -1)
	{
		this->updateInterfaceGeneralInfo(controllers.at(currentRowController));

		this->updateTrafficLight(controllers.at(currentRowController));
	}

	if(this->currentRowStreet != -1)
	{
		this->updateStreetProps(controllers.at(currentRowController)->getControlledStreets()->at(currentRowStreet));
		ui.listControlledStreets->setCurrentRow(this->currentRowStreet);
	}

	deleteInVector(controllers);
}

void MainWindow::updateInterface(Controller *c)
{

	//I'm in the first tab - general information
	if(ui.tabWidget->currentIndex() == 0)
	{
		this->updateInterfaceGeneralInfo(c);
	}
	else //Command tab
	{
		this->updateInterfaceCommands(c);
	}
}

void MainWindow::updateTrafficLight(Controller *c)
{

	//Only works if 2 traffic lights

	if(c->getControlledStreets()->size() != 2)
		return;

   ControllerLogic * logic = c->getCurrentLogic();

   if(logic->subID.compare("off") == 0)
   {
	   ui.lblTL1->setText("<img src=\":/MainWindow/light_off.png\">");
	   ui.lblTL2->setText("<img src=\":/MainWindow/light_off.png\">");
	   return;
   }

   int currentPhase = logic->currentPhaseIndex;
   QString img;
   int count = 1;

   QString phaseDef(logic->phases->at(currentPhase)->phaseDef.c_str());
  
   phaseDef = phaseDef.toLower();

   QChar current = '8';

   for(int i = 0; i < phaseDef.size(); i++)
   {
	   if(phaseDef.at(i) != current)
	   {
		   current = phaseDef.at(i);

		   if(current == 'r')//red
		   {
			   img = "light_red";
		   }
		   else if(current == 'y') //yellow
		   {
			   img = "light_yellow";
		   }
		   else  //green
		   {
			   img = "light_green";
		   }

		   if(count == 1)
		   {
			   ui.lblTL1->setText("<img src=\":/MainWindow/"+img+".png\">");
			   count++;
		   }
		   else
		   {
			   ui.lblTL2->setText("<img src=\":/MainWindow/"+img+".png\">");
			   break;
		   }
	   }
   }
   
   
   
   
   

}
MainWindow::~MainWindow()
{
	if(timer->isActive() == true)
		timer->stop();

	delete timer;
	timer = nullptr;

	delete mapWidget;
	mapWidget = nullptr;

	
}

void MainWindow::logControllerSituation(QString s)
{
	ui.txtControllerSituation->append(s);
}

void MainWindow::logFitness(QString s)
{
	ui.txtFitness->append(s);
}

void MainWindow::logQueue(QString s)
{
	ui.txtQueueLog->append(s);
}

void MainWindow::logPrograms(QString s)
{
	ui.txtProgramLog->append(s);
}

void MainWindow::logInitPrograms(QString s)
{
	ui.txtInitPrograms->append(s);
}

void MainWindow::logFuzzyIn(QString s)
{
	ui.txtFuzzyIn->append(s);
}

void MainWindow::logFuzzyOut(QString s)
{
	ui.txtFuzzyOut->append(s);
}
