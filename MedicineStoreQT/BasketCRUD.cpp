#include <vector>
#include "Medicine.h"
#include "BasketCRUD.h"
#include "Repository.h"
#include <QtWidgets\qwidget.h>
#include "MyListModel.h"
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

void basketCRUD::initGUIcomps() {

	ctrl.addObserver(this);
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);
	list = new QListView;
	QVBoxLayout* listly = new QVBoxLayout;
	list->setLayout(listly);
	mainLayout->addWidget(list);
	QWidget *buttons = new QWidget;
	QVBoxLayout *lybuttons = new QVBoxLayout;
	buttons->setLayout(lybuttons);
	btnClear = new QPushButton("Clear recipe");
	btnClear->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lybuttons->addWidget(btnClear);
	btnGenerate = new QPushButton("Generate recipe");
	btnGenerate->setStyleSheet("QPushButton {background-color: #C0AF8F; color: black}");
	lybuttons->addWidget(btnGenerate);
	fill = new QLineEdit;
	lybuttons->addWidget(fill);
	mainLayout->addWidget(buttons);
	

}
void basketCRUD::loadList(vector<Medicine> recipe) {
	MyListModel* model = new MyListModel{ recipe };
	list->setModel(model);
}
void basketCRUD::connectSignals() {
	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		loadList(ctrl.fill(fill->text().toInt()));
	});
	QObject::connect(btnClear, &QPushButton::clicked, [&]() {
		ctrl.clearRecipe();
		loadList(ctrl.getAllRecipe());
		fill->setText(" ");
	});
}
