#include "hoaReaderWriter/hoaIRW.h"

void hoaIRW::store(hoaPoint& p)
{
	store(p.x);
	store(p.y);
	store(p.z);
}

void hoaIRW::store(hoaVector& v)
{
	store(v.x);
	store(v.y);
	store(v.z);
}

