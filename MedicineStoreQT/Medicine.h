#pragma once
#include <string>
using std::string;
class Medicine {
private:
	string name;
	int price;
	string producer;
	string substance;
public:
	Medicine(string n, int p, string pr, string s) :name{ n }, price{ p }, producer{ pr }, substance{ s } {}
	Medicine() :Medicine(" ", 0, " ", " ") {}
	string getName()const {
		return name;
	}
	int getPrice()const {
		return price;
	}
	string getProducer()const {
		return producer;
	}
	string getSubstance()const {
		return substance;
	}
	void setPrice(int price) {
		this->price = price;
	}





};