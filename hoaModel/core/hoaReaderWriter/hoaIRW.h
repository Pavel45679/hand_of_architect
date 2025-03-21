#pragma once
#include "hoaPoint.h"
#include "hoaVector.h"

class hoaIRW {

public:
	virtual ~hoaIRW() = 0;
	virtual void store(int& i) = 0;
	virtual void store(double& d) = 0;
	virtual void store(hoaPoint& p);
	virtual void store(hoaVector& v);
};
