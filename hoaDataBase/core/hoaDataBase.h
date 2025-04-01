#pragma once
#include "hoaObject.h"
#include <string>
#include <memory>
#include "hoaReaderWriter/hoaIRW.h"
#include <unordered_map>
#include "hoaIRWFabrica.h"

class hoaDataBase {
public:
	hoaDataBase();
	~hoaDataBase();
	void create(std::string path, hoaIRWType type);
	void open(std::string path);
	void save();
	void close();

	std::unique_ptr<hoaObject> getObject(unsigned int index);
	int addObject(hoaObject* obj);

private:
	class Impl;
	Impl* pImpl;
};
