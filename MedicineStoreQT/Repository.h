#pragma once
#include <vector>
#include <algorithm>
#include <string.h>
#include "Medicine.h"
#include "CustomException.h"
using std::vector;
using std::string;
class MedicineRepository {
private:
	vector<Medicine> all;
public:
	virtual void store(const Medicine& m) {
		all.push_back(m);

	}
	int find(string name) {
		for (int i = 0; i < all.size(); i++) {
			if (all[i].getName() == name) {
				return i;
			}
		}
		return -1;
	}
	virtual void remove(string name) {
		int poz;
		for (int i = 0; i < all.size(); i++) {
			if (all[i].getName() == name) {
				poz = i;
			}
		}
		all.erase(all.begin() + poz);
	}
	virtual void modify(string name, int price) {
		for (int i = 0; i < all.size(); i++) {
			if (all[i].getName() == name) {
				all[i].setPrice(price);
			}
		}
	}
	Medicine get(int i) {
		return all[i];
	}
	vector<Medicine> getAll() {
		return all;
	}
	int length() {
		return all.size();
	}
};
class MedicineFileRepository : public MedicineRepository {
private:
	string fileName;
	void loadFromFile();
	void writeToFile();
public:
	MedicineFileRepository(string fileName) : MedicineRepository(), fileName{ fileName } { loadFromFile(); }
	void store(const Medicine& m) override {
		MedicineRepository::store(m);
		writeToFile();
	}
	void remove(string name) override {
		MedicineRepository::remove(name);
		writeToFile();
	}
	void modify(string name, int price) override {
		MedicineRepository::modify(name, price);
		writeToFile();
	}
};