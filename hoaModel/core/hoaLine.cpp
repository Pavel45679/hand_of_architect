#include "hoaLine.h"

void hoaLine::store(hoaIRW* rw)
{
	rw->store(_start);
	rw->store(_direct);
}

void hoaLine::setStart(hoaPoint start)
{
	_start = std::move(start);
}

hoaPoint hoaLine::getStart() const
{
	return _start;
}

int hoaLine::type()
{
	return 2;
}
