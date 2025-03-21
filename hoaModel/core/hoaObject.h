#pragma once
#include "hoaReaderWriter/hoaIRW.h"

class __declspec(dllexport) hoaObject {
public:
	hoaObject();
	virtual ~hoaObject() = default;
	void printMessage();
	virtual void store(hoaIRW& rw) = 0;
};
