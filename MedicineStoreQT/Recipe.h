#pragma once
#include "Repository.h"
#include "Medicine.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>  
using std::vector;
class Recipe {
private:
	vector<Medicine> recipe;
	MedicineRepository& repo;
public:
	Recipe(MedicineRepository& repo) : repo{ repo } {}
	void addRecipe(const Medicine& m) {
		recipe.push_back(m);
	}
	void clearRecipe() {
		recipe.clear();
	}
	vector<Medicine> getRecipe() {
		return recipe;
	}
	int getSize() {
		return recipe.size();
	}
	vector<Medicine> fill(int number) {
		int seed = std::chrono::system_clock::now().time_since_epoch().count();
		vector<Medicine> all = { repo.getAll() };
		std::shuffle(all.begin(), all.end(), std::default_random_engine(seed));
		while (getSize() < number && all.size()>0) {
			recipe.push_back(all.back());
			all.pop_back();
		}
		return getRecipe();
	}

};