#pragma once
#pragma once
#include "Medicine.h"
#include "Repository.h"
class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};
};
class UndoAdd : public UndoAction {
private:
	MedicineRepository& repo;
	string name;
public:
	UndoAdd(MedicineRepository& repo, string n) : repo{ repo }, name{ n } {}
	void doUndo() override {
		repo.remove(name);
	}

};
class UndoDelete : public UndoAction {
private:
	Medicine med;
	MedicineRepository& repo;
public:
	UndoDelete(MedicineRepository& repo, const Medicine& m) : repo{ repo }, med{ m } {}
	void doUndo() override {
		repo.store(med);
	}
};
class UndoModify : public UndoAction {
private:
	string name;
	int price;
	MedicineRepository& repo;
public:
	UndoModify(MedicineRepository& repo, string n, int p) : repo{ repo }, name{ n }, price{ p } {}
	void doUndo() override {
		repo.modify(name, price);

	}
};