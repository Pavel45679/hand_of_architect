#pragma once
#include "hoaObject.h"
#include "hoaDataBaseGuard.h"
#include <string>
#include <memory>
#include <map>
#include <functional>

class hoaDataBaseGuard;

class hoaDataBase {
public:
	hoaDataBase();
	~hoaDataBase();
	void create(std::string path);
	void open(std::string path);
	void save();
	void saveAs(std::string newPath);
	void close();

	std::unique_ptr<hoaObject> getObject(unsigned int index);
	int addObject(hoaObject* obj);
	void modifyObject(hoaObject* obj);

	template<typename T>
	void registerClass(int type) {
		creators[type] = []() {
			return std::make_unique<T>();
			};
	}

	std::unique_ptr<hoaObject> create(int type) {
		auto it = creators.find(type);
		if (it != creators.end()) {
			return it->second();
		}
		return nullptr;
	}
private:
	class Impl;
	Impl* pImpl;
	std::unordered_map<int, std::function<std::unique_ptr<hoaObject>()>> creators;
	std::shared_ptr<hoaDataBaseGuard> mDataBaseGuard;
};
