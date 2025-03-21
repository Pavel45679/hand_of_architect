#pragma once
#include "hoaObject.h"
#include "hoaPoint.h"
#include "hoaVector.h"

class __declspec(dllexport) hoaPlane: public hoaObject {
public:
	void store(hoaIRW& rw) override;
	hoaPoint _center;
	hoaVector _normal;
};
