#pragma once
#include <string>

class __declspec(dllexport) hoaDataBase {
public:
	hoaDataBase();
	void open(std::string path);
	void save();
	void close();
};
