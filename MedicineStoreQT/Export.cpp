
#include "Export.h"
#include "Medicine.h"
#include <fstream>
#include <string>
#include <vector>
void exportCVS(const std::string& fName, const std::vector<Medicine>& meds) {
	std::ofstream out(fName, std::ios::trunc);
	for (const auto& p : meds) {
		out << p.getName() << ",";
		out << p.getPrice() << ",";
		out << p.getProducer() << ",";
		out << p.getSubstance() << std::endl;
	}
	out.close();
}