#pragma once
#include "hoaObject.h"
#include "hoaPoint.h"
#include "hoaVector.h"

class hoaLine: public hoaObject {
public:
	void store(hoaIRW* rw) override;
	int type() override;

	void setStart(hoaPoint start);
	hoaPoint getStart() const;

private:
	hoaPoint _start;
	hoaVector _direct;
};
