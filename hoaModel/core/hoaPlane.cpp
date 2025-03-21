#include "hoaPlane.h"

void hoaPlane::store(hoaIRW& rw) {
	rw.store(_center);
	rw.store(_normal);
}
