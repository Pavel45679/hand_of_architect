#include "hoaDataBase.h"
#include <fstream>

static std::string tho_suffix = ".tho";

void hoaDataBase::create(std::string path, hoaIRWType type){
	mType = type;
	if (mIsOpen)
		return;

	std::ofstream dbFile(path, std::ios::out | std::ios::binary);
	if (!dbFile) {
		return;
	}

	mPath = path;
	mIsOpen = true;
}

void hoaDataBase::open(std::string path) {
	if (mIsOpen)
		return;

	if (path.ends_with(tho_suffix)) {
		mType = hoaIRWType::SimpleText;
	}

	//hoaIRWFabrica::getR(mType);
	std::ifstream dbFile(path, std::ios::in | std::ios::binary);
	if (!dbFile)
		return;

	mPath = path;
	mIsOpen = true;
}

void hoaDataBase::save() {
	if (mIsOpen)
		return;

	std::ofstream dbFile(mPath, std::ios::out | std::ios::binary);
	if (!dbFile)
		return;
}

void hoaDataBase::close() {
	if (mIsOpen)
		return;

	mIsOpen = false;
}

/*std::unique_ptr<hoaObject> hoaDataBase::getObject(unsigned int index) {
	
}*/

void hoaDataBase::addObject(hoaObject* obj) {

}
