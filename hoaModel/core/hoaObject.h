#pragma once
#include "hoaReaderWriter/hoaIRW.h"

class hoaObject {
public:
	hoaObject();
	virtual ~hoaObject() = default;
	void printMessage();
	//int getId() const;
	virtual void store(hoaIRW* rw) = 0;
	virtual int type() = 0;

private:
	int mId = 0;
};
