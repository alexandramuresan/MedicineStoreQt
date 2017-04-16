#include "MedicineGUI.h"
#include <QtWidgets/QApplication>
#include "Medicine.h"
#include "Repository.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
	MedicineFileRepository rep{ "medicinestore.txt" };
	MedicineController ctr{ rep };
	QApplication a(argc, argv);
	MedicineGUI w{ ctr };
	w.show();
	return a.exec();
}
