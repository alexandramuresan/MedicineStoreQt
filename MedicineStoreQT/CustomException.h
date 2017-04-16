#pragma once
#include <string>
using std::string;
class CustomException {
private:
	string msg;
public:
	CustomException(string msg) : msg{ msg } {}
	string getMsg() const {
		return msg;
	}
};