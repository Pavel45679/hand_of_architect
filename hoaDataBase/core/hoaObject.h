#pragma once
#include <string>
#include <memory>

class hoaDataBaseGuard;

class hoaObject {
public:
	hoaObject();
	virtual ~hoaObject();
	void printMessage();
	virtual void store(std::string text) = 0;
	virtual std::string store() = 0;
	virtual int type() = 0;
	void setDataBaseGuard(std::shared_ptr<hoaDataBaseGuard> dataBaseGuard);
	int getId() const;
	void modify();
private:
	bool mModify = false;
	int mId = 0;
	std::shared_ptr<hoaDataBaseGuard> mDataBaseGuard;
};
