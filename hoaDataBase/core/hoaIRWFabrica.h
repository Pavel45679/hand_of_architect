#pragma once
#include "hoaReaderWriter/hoaIRW.h"
#include <memory>

enum class hoaIRWType
{
	SimpleText
};

class hoaIRWFabrica {
public:
	static std::unique_ptr<hoaIR> getR(hoaIRWType type, char* buff, size_t size);
	static std::unique_ptr<hoaIW> getW(hoaIRWType type);
};
