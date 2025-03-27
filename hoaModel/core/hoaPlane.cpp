#include "hoaPlane.h"

void hoaPlane::store(hoaIRW* rw)
{
	rw->store(_center);
	rw->store(_normal);
}

int hoaPlane::type()
{
	return 1;
}
