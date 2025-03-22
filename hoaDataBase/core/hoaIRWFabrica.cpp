#include "hoaIRWFabrica.h"
#include "hoaSimpleTextIRW.h"
#include <cassert>

static std::unique_ptr<hoaIRW> hoaIRWFabrica::get(hoaIRWType type) {
	if (type == DataBaseType::SimpleText)
	{
		return  std::make_unique< hoaSimpleTextIRW>();
	}
	assert(0);
}
