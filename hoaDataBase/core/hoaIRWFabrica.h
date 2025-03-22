#pragma once
#include "hoaIRW.h"
#include <unique_ptr>

enum class hoaIRWType
{
	SimpleText
};

class hoaIRWFabrica {
public:
	static std::unique_ptr<hoaIRW> get(hoaIRWType type);
};
