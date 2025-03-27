#include "hoaIRWFabrica.h"
#include "hoaSimpleTextIR.h"
#include "hoaSimpleTextIW.h"
#include <cassert>

std::unique_ptr<hoaIR> hoaIRWFabrica::getR(hoaIRWType type, char * buff, size_t size) {
	if (type == hoaIRWType::SimpleText)
	{
		return  std::make_unique< hoaSimpleTextIR>(buff, size);
	}
	assert(0);
	return {};
}

std::unique_ptr<hoaIW> hoaIRWFabrica::getW(hoaIRWType type) {
	if (type == hoaIRWType::SimpleText)
	{
		return std::make_unique<hoaSimpleTextIW>();
	}
	assert(0);
	return {};
}
