#pragma once
#include "hoaPoint.h"
#include "hoaVector.h"
#include <utility>
#include <vector>

class __declspec(dllexport) hoaIRW {
public:
	virtual ~hoaIRW() = default;
	virtual void store(int& i) = 0;
	virtual void store(double& d) = 0;
	virtual void store(hoaPoint& p);
	virtual void store(hoaVector& v);
};

class __declspec(dllexport) hoaIR : public hoaIRW {
public:
	hoaIR(char* buff, size_t size) :mBuff(buff), mSize(size){};

protected:
	char * mBuff;
	size_t mSize;
};

class __declspec(dllexport) hoaIW : public hoaIRW {
public:
	virtual std::vector<char> get() = 0;
};
