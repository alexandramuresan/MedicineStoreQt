#include "MedicineGUI.h"
#include <vector>
#include "Medicine.h"
#include "BasketCRUD.h"
#include "Repository.h"
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qlayout.h>
#include <QtWidgets\qlistwidget.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qmessagebox.h>
#include <QtWidgets\qmenubar.h>
#include <QtWidgets\qmenu.h>
#include <QtWidgets\qtoolbutton.h>
#include <QtWidgets\qtoolbar.h>
#include "MyListModel.h"
using std::vector;
void MedicineGUI::initGUIcomps() {
	QHBoxLayout* mainlayout = new QHBoxLayout;
	setLayout(mainlayout);
	//Widget pentru lista cu layout vertical.
	QWidget* listwidget = new QWidget;
	QVBoxLayout* listlayout = new QVBoxLayout;
	listwidget->setLayout(listlayout);
	listwidget->setStyleSheet("QListWidget { border-radius: 6px; border: 3px solid #5C493A; }");
	lista = new QListWidget;
	listlayout->addWidget(lista);
	//Widget pentru butoane de adauga si sterge sub lista cu layout orizontal.
	QWidget* butoane = new QWidget;
	QVBoxLayout* lybutoane = new QVBoxLayout;
	butoane->setLayout(lybutoane);
	adauga = new QPushButton("Add");
	adauga->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lybutoane->addWidget(adauga);
	sterge = new QPushButton("Remove");
	sterge->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lybutoane->addWidget(sterge);
	modifica = new QPushButton("Modify");
	modifica->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lybutoane->addWidget(modifica);
	undo = new QPushButton("Undo");
	undo->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lybutoane->addWidget(undo);
	mainlayout->addWidget(butoane);
	mainlayout->addWidget(listwidget);
	//Widget pentru detalii medicament cu layout de form.
	QWidget* detalii = new QWidget;
	QFormLayout* lydetalii = new QFormLayout;
	detalii->setLayout(lydetalii);
	name = new QLineEdit;
	name->setStyleSheet("QLineEdit { border - radius: 6px; border: 2px solid #5C493A;}");
	lydetalii->addRow(new QLabel("Name:"), name);
	price = new QLineEdit;
	price->setStyleSheet("QLineEdit { border - radius: 6px; border: 2px solid #5C493A;}");
	lydetalii->addRow(new QLabel("Price:"), price);
	producer = new QLineEdit;
	producer->setStyleSheet("QLineEdit { border - radius: 6px; border: 2px solid #5C493A;}");
	lydetalii->addRow(new QLabel("Producer:"), producer);
	substance = new QLineEdit;
	substance->setStyleSheet("QLineEdit { border - radius: 6px; border: 2px solid #5C493A;}");
	lydetalii->addRow(new QLabel("Substance:"), substance);
	filterprice = new QPushButton("Filter By Price");
	filterprice->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lydetalii->addWidget(filterprice);
	filtersubstance = new QPushButton("Filter By Substance");
	filtersubstance->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lydetalii->addWidget(filtersubstance);
	showlist = new QPushButton("Show All");
	showlist->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lydetalii->addWidget(showlist);
	mainlayout->addWidget(detalii);
	//Widget pentru butoanele de sortare.
	QWidget* sortari = new QWidget;
	QVBoxLayout* sortly = new QVBoxLayout;
	sortari->setLayout(sortly);
	sortProducer = new QPushButton("Sort By Producer");
	sortProducer->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	sortly->addWidget(sortProducer);
	sortName = new QPushButton("Sort By Name");
	sortName->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	sortly->addWidget(sortName);
	sortSubPrice = new QPushButton("Sort By Substance And Price");
	sortSubPrice->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	sortly->addWidget(sortSubPrice);
	openBasket = new QPushButton("Open Basket");
	openBasket->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	sortly->addWidget(openBasket);
	painter = new QPushButton("Paint medicine");
	painter->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	sortly->addWidget(painter);
	generate = new QPushButton("Generate recipe");
	generate->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	sortly->addWidget(generate);
	fill = new QLineEdit;
	sortly->addWidget(fill);
	mainlayout->addWidget(sortari);
	
}
void MedicineGUI::loadList(vector<Medicine> meds) {
	lista->clear();
	for(auto &m : meds){
		QListWidgetItem* med = new QListWidgetItem(QString::fromStdString(m.getName()), lista);
		lista->addItem(med);

	}
	
}
void MedicineGUI::connectSignals() {
	//Adauga un nou medicament pe baza text fields.
	QObject::connect(adauga, &QPushButton::clicked, [&]() {
		try {
			ctrl.add(name->text().toStdString(), price->text().toInt(), producer->text().toStdString(), substance->text().toStdString());
			loadList(ctrl.getAllMedicine());
		}
		catch(CustomException& msg){
			QMessageBox::warning(this, "Warning", QString::fromStdString(msg.getMsg()));
		}
		name->setText("");
		price->setText("");
		producer->setText("");
		substance->setText("");
	});
	//Incarca detaliile in functie de medicamentul selectat.
	QObject::connect(lista, &QListWidget::itemSelectionChanged, [&]() {
		if (lista->selectedItems().isEmpty()) {
			name->setText("");
			price->setText("");
			producer->setText("");
			substance->setText("");
			return;
		}
		QListWidgetItem* item = lista->selectedItems().at(0);
		QString nume = item->text();
		name->setText(nume);
		int i = ctrl.find(nume.toStdString());
		Medicine m = ctrl.get(i);
		price->setText(QString::number(m.getPrice()));
		producer->setText(QString::fromStdString(m.getProducer()));
		substance->setText(QString::fromStdString(m.getSubstance()));

	});
	//Sterge obiect selectat.
	QObject::connect(sterge, &QPushButton::clicked, [&]() {
		try {
			
			ctrl.removeMed(name->text().toStdString());
			loadList(ctrl.getAllMedicine());
		}
		catch (CustomException& msg) {
			QMessageBox::warning(this, "Warning!", QString::fromStdString(msg.getMsg()));
		}
	});
	//Modifica obiect selectat.
	QObject::connect(modifica, &QPushButton::clicked, [&]() {
		try {
			ctrl.modifyMed(name->text().toStdString(), price->text().toInt());
			loadList(ctrl.getAllMedicine());
		}
		catch (CustomException& msg) {
			QMessageBox::warning(this, "Warning!", QString::fromStdString(msg.getMsg()));
		}
	});
	//Le arata doar pe cele cu un anumit pret.
	QObject::connect(filterprice, &QPushButton::clicked, [&]() {
		loadList(ctrl.filterByPrice(price->text().toInt()));
	});
	//Arata toate din lista.
	QObject::connect(showlist, &QPushButton::clicked, [&]() {
		loadList(ctrl.getAllMedicine());
	});
	//Le arata pe cele cu o anumita substanta.
	QObject::connect(filtersubstance, &QPushButton::clicked, [&]() {
		loadList(ctrl.filterBySubstance(substance->text().toStdString()));
	});
	//Face undo dupa o operatie.
	QObject::connect(undo, &QPushButton::clicked, [&]() {
		try{
			ctrl.undo();
			loadList(ctrl.getAllMedicine());
		}
		catch (CustomException& msg) {
			QMessageBox::warning(this, "Warning!", QString::fromStdString(msg.getMsg()));
		}
		
	});
	QObject::connect(sortProducer, &QPushButton::clicked, [&]() {
		loadList(ctrl.sortByProducer());
	});
	QObject::connect(sortName, &QPushButton::clicked, [&]() {
		loadList(ctrl.sortByName());
	});
	
	QObject::connect(openBasket, &QPushButton::clicked, [&]() {
		basketCRUD* b = new basketCRUD{ ctrl,this };
		b->show();
	});

	QObject::connect(painter, &QPushButton::clicked, [&]() {
		basketDraw* d = new basketDraw{ ctrl,this };
		d->setMinimumSize(500, 100);
		d->show();
	});
	QObject::connect(generate, &QPushButton::clicked, [&]() {
		loadList(ctrl.fill(fill->text().toInt()));
	});
	
	

}
