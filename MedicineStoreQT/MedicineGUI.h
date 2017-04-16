#pragma once
#include "Controller.h"
#include "Medicine.h"
#include <vector>
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qlistwidget.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qlistview.h>
#include "MyListModel.h"
using std::vector;
class MedicineGUI : public QWidget {
private:
	MedicineController& ctrl;
	QListWidget* lista;
	QPushButton* adauga;
	QPushButton* sterge;
	QPushButton* modifica;
	QPushButton* filterprice;
	QPushButton* filtersubstance;
	QPushButton* showlist;
	QPushButton* undo;
	QPushButton* sortProducer;
	QPushButton* sortName;
	QPushButton* sortSubPrice;
	QPushButton* openBasket;
	QPushButton* painter;
	QPushButton* generate;
	QLineEdit* fill;
	QLineEdit* name;
	QLineEdit* price;
	QLineEdit* producer;
	QLineEdit* substance;
	void initGUIcomps();
	void loadList(vector<Medicine> meds);
	void connectSignals();

public:
	MedicineGUI(MedicineController& ctrl): ctrl{ ctrl }{
		this->setWindowFlags(Qt::Window);
		initGUIcomps();
		loadList(ctrl.getAllMedicine());
		connectSignals();
		
	}
	
};