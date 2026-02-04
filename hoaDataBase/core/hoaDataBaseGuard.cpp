#include "hoaDataBaseGuard.h"

hoaDataBaseGuard::hoaDataBaseGuard(hoaDataBase* dataBase):mDataBase(dataBase){
}

hoaDataBase* hoaDataBaseGuard::getDataBase() {
	return mDataBase;
}

void hoaDataBaseGuard::invalid(){
	mDataBase = nullptr;
}

bool hoaDataBaseGuard::isValid() const{
	return mDataBase == nullptr;
}
