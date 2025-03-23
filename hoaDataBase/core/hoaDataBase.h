#pragma once
#include "hoaObject.h"
#include <string>
#include <memory>
#include "hoaReaderWriter/hoaIRW.h"
#include <unordered_map>
#include "hoaIRWFabrica.h"

class __declspec(dllexport) hoaDataBase {
public:
	void create(std::string path, hoaIRWType type);
	void open(std::string path);
	void save();
	void close();
	//std::unique_ptr<hoaObject> getObject(unsigned int index);
	void addObject(hoaObject* obj);

private:
	std::string mPath;
	bool mIsOpen = false;
	std::unordered_map<unsigned int, std::vector<char>> mMap;
	hoaIRWType mType;
};
