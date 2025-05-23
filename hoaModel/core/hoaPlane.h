#pragma once
#include "hoaObject.h"
#include "hoaPoint.h"
#include "hoaVector.h"

class hoaPlane: public hoaObject {
public:
	void store(hoaIRW* rw) override;
	int type() override;

	void setCenter(hoaPoint center);
	hoaPoint getCenter() const;

private:
	hoaPoint _center;
	hoaVector _normal;
};
