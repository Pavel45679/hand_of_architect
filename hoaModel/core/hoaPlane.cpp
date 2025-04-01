#include "hoaPlane.h"

void hoaPlane::store(hoaIRW* rw)
{
	rw->store(_center);
	rw->store(_normal);
}

void hoaPlane::setCenter(hoaPoint center)
{
	_center = std::move(center);
}

hoaPoint hoaPlane::getCenter() const
{
	return _center;
}

int hoaPlane::type()
{
	return 1;
}
