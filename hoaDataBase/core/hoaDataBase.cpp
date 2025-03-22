#include "hoaDataBase.h"


void hoaDataBase::create(std::string path, hoaIRWType type){
	mType = type;
	if (isOpen)
		return;

	std::ofstream dbFile(path, std::ios::out | std::ios::binary);
	if (!dbFile) {
		return;
	}

	mPath = path;
	isOpen = true;
}

void hoaDataBase::open(std::string path) {
	if (isOpen)
		return;

	std::ifstream dbFile(path, std::ios::in | std::ios::binary);
	if (!dbFile)
		return;

	mPath = path;
	isOpen = true;
}

void hoaDataBase::save() {
	if (isOpen)
		return;

	std::ofstream dbFile(dbPath, std::ios::out | std::ios::binary);
	if (!dbFile)
		return;
}

void hoaDataBase::close() {
	if (isOpen)
		return;

	isOpen = false;
}

std::unique_ptr<hoaObject> hoaDataBase::getObject(unsigned int index) {

}
