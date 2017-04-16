#ifndef MEDICINESTOREQT_H
#define MEDICINESTOREQT_H

#include <QtWidgets/QMainWindow>
#include "ui_medicinestoreqt.h"

class MedicineStoreQT : public QMainWindow
{
	Q_OBJECT

public:
	MedicineStoreQT(QWidget *parent = 0);
	~MedicineStoreQT();

private:
	Ui::MedicineStoreQTClass ui;
};

#endif // MEDICINESTOREQT_H
