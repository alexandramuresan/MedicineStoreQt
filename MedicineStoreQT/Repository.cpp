#include "Medicine.h"
#include "Repository.h"
#include <assert.h>
#include <fstream>

void MedicineFileRepository::loadFromFile() {
	std::ifstream in(fileName);
	while (!(in.eof())) {
		string name;
		in >> name;
		int price;
		in >> price;
		string producer;
		in >> producer;
		string substance;
		in >> substance;
		if (name != "" && producer != "" && substance != "") {
			Medicine m{ name,price,producer,substance };
			MedicineRepository::store(m);
		}
	}
	in.close();
}
void MedicineFileRepository::writeToFile() {
	std::ofstream out(fileName);
	for (auto& m : getAll()) {
		out << m.getName();
		out << std::endl;
		out << m.getPrice();
		out << std::endl;
		out << m.getProducer();
		out << std::endl;
		out << m.getSubstance();
		out << std::endl;


	}
	out.close();
}