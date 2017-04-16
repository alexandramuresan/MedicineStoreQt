#pragma once
#include "Controller.h"
#include "Recipe.h"
#include "Medicine.h"
#include <vector>
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qlistwidget.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qlistview.h>
#include "Observer.h"
#include <qpainter.h>
#include <QPaintEvent>
#include <qlineedit.h>

class basketCRUD : public QWidget , public Observer{
private:
	MedicineController& ctrl;
	QPushButton* btnClear;
	QPushButton* btnGenerate;
	QListView* list;
	QLineEdit* fill;
	void initGUIcomps();
	void loadList(vector<Medicine> recipe);
	void connectSignals();
	
public:
	basketCRUD(MedicineController& ctrl, QWidget* parent) : ctrl{ ctrl }, QWidget{ parent } {
		this->setWindowFlags(Qt::Window);
		initGUIcomps();
		loadList(ctrl.getAllRecipe());
		connectSignals();
		
	}
	void update() override {
		loadList(ctrl.getAllRecipe());
	}

	~basketCRUD() {
		ctrl.removeObserver(this);
	}
};

class basketDraw : public QWidget, public Observer {
private:
	MedicineController& ctrl;
public:
	basketDraw(MedicineController& ctrl, QWidget* parent) : ctrl{ ctrl }, QWidget{ parent } {
		this->setWindowFlags(Qt::Window);
		ctrl.addObserver(this);
		update();
	}

	void update() override {
		QWidget::update();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		for (int i = 0; i < ctrl.getRecipeSize(); i++) {
			p.drawImage(75 * i + 10, 10, QImage("pill.png"));
			
		}
	}

	~basketDraw() {
		ctrl.removeObserver(this);
	}
};