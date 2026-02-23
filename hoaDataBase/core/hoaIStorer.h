#pragma once
#include <string>
#include <memory>
#include "hoaPoint.h"
#include "hoaVector.h"

class hoaIStorer {
public:
	hoaIStorer() = default;
	virtual ~hoaIStorer() = default;
	virtual void store(int& value) = 0;
	virtual void store(double& value) = 0;
	virtual void store(hoaPoint& value) = 0;
	virtual void store(hoaVector& value) = 0;
	virtual bool isWriter() = 0;
};
