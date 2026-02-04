#include "hoaObject.h"

#include "hoaDataBase.h"
#include "hoaDataBaseGuard.h"

#include <iostream>

hoaObject::hoaObject() {
	std::cout << "hoaObject created!" << std::endl;
}

void hoaObject::printMessage() {
	std::cout << "Hello from hoaObject!" << std::endl;
}

int hoaObject::getId() const {
	return mId;
}

void hoaObject::modify() {
	mModify = true;
}

void hoaObject::setDataBaseGuard(std::shared_ptr<hoaDataBaseGuard> dataBaseGuard) {
	mDataBaseGuard = dataBaseGuard;
}

hoaObject::~hoaObject(){
	if (mDataBaseGuard == nullptr)
		return;

	if(!mModify)
		return;

	if (hoaDataBase* dataBase = mDataBaseGuard->getDataBase()) {
		dataBase->modifyObject(this);
	}
}
