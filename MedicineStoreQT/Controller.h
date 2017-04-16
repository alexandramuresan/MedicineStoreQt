#pragma once
#include "Medicine.h"
#include "Repository.h"
#include "Observer.h"
#include "CustomException.h"
#include "Recipe.h"
#include "Export.h"
#include <vector>
#include <string.h>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>
#include "Undo.h"

using std::string;
using std::vector;
using std::iterator;
using std::unique_ptr;
class MedicineController : public Observable{
private:
	MedicineRepository& repo;
	Recipe rep;
	vector<unique_ptr<UndoAction>> undoActions;
public:
	MedicineController(MedicineRepository& repo) : repo{ repo }, rep{ rep } {};
	void add(string name, int price, string producer, string substance) {
		Medicine m{ name,price,producer,substance };
		if (repo.find(m.getName()) == -1 && m.getPrice()>0) {
			repo.store(m);
			undoActions.push_back(std::make_unique<UndoAdd>(repo, m.getName()));
		}
		else {
			throw CustomException("Can't add this medicine!Try again!");
		}
	}
	int find(string name) {
		return repo.find(name);
	}
	Medicine get(int i) {
		return repo.get(i);
	}
	void addRecipe(string name) {
		int poz = repo.find(name);
		if (poz == -1) {
			throw CustomException("This medicine does not exist!");
		}
		else {
			Medicine m = repo.get(poz);
			rep.addRecipe(m);

		}
		notify();

	}
	void clearRecipe() {
		
		rep.clearRecipe();
		notify();
	}
	vector<Medicine> getAllRecipe() {
		return rep.getRecipe();
	}
	int getRecipeSize() {
		return rep.getSize();
	}
	vector<Medicine> fill(int number) {
		int seed = std::chrono::system_clock::now().time_since_epoch().count();
		vector<Medicine> all = { repo.getAll() };
		std::shuffle(all.begin(), all.end(), std::default_random_engine(seed));
		while (getRecipeSize() < number && all.size()>0) {
			rep.addRecipe(all.back());
			all.pop_back();
		}
		notify();
		return getAllRecipe();
	}
	void removeMed(string name) {
		if (repo.find(name) != -1) {
			int i = repo.find(name);
			Medicine m = repo.get(i);
			repo.remove(name);
			undoActions.push_back(std::make_unique<UndoDelete>(repo, m));
		}
		else {
			throw CustomException("Error in deleting!");
		}

	}
	void modifyMed(string name, int price) {

		if (repo.find(name) != -1 && price>0) {
			int i = repo.find(name);
			Medicine m = repo.get(i);
			undoActions.push_back(std::make_unique<UndoModify>(repo, m.getName(), m.getPrice()));
			repo.modify(name, price);
		}
		else {
			throw CustomException("There is no medicine with this name or the price is negative!");
		}
	}
	vector<Medicine> searchByName(string name) {
		vector<Medicine> result;
		auto all = repo.getAll();
		std::copy_if(all.begin(), all.end(), std::back_inserter(result), [name](const Medicine& m) {return m.getName() == name; });
		return result;
	}
	vector<Medicine> filterByPrice(int price) {
		vector<Medicine> result;
		auto all = repo.getAll();
		std::copy_if(all.begin(), all.end(), std::back_inserter(result), [price](const Medicine& m) {return m.getPrice() == price; });
		return result;
	}
	vector<Medicine> filterBySubstance(string substance) {
		vector<Medicine> rez;
		auto all = repo.getAll();
		std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [substance](const Medicine& m) {return m.getSubstance() == substance; });
		return rez;
	}
	vector<Medicine> filterBySum(int price) {
		vector<Medicine> rez;
		auto all = repo.getAll();
		std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [price](const Medicine& m) {return m.getPrice()>price; });
		return rez;
	}
	vector<Medicine> litera(char l) {
		vector<Medicine> rez;
		auto all = repo.getAll();
		std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [l](const Medicine& m) {return m.getName()[0] == l; });
		return rez;
	}
	vector<Medicine> sortByProducer() {
		auto all = repo.getAll();
		std::sort(all.begin(), all.end(), [](const Medicine& m1, const Medicine& m2) {return m1.getProducer().compare(m2.getProducer())<0; });
		return all;

	}
	vector<Medicine> sortByName() {
		auto all = repo.getAll();
		std::sort(all.begin(), all.end(), [](const Medicine& m1, const Medicine& m2) {return m1.getName()<m2.getName() < 0; });
		return all;
	}
	vector<Medicine> sortBySubPrice() {
		auto all = repo.getAll();
		std::sort(all.begin(), all.end(), [](const Medicine& m1, const Medicine& m2) {return m1.getSubstance().compare(m2.getSubstance()) < 0 && m1.getPrice() < m2.getPrice(); });
		return all;
	}
	vector<Medicine> getAllMedicine() {
		return repo.getAll();
	}
	void exportToCVS(string fileName) {
		exportCVS(fileName, rep.getRecipe());
	}
	void undo() {
		if (undoActions.empty()) {
			throw CustomException("You can not undo anymore!");
		}
		undoActions.back()->doUndo();
		undoActions.pop_back();
	}

};