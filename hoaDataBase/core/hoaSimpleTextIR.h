#pragma once
#include <string>
#include "hoaReaderWriter/hoaIRW.h"

class hoaSimpleTextIR : public hoaIR {
public:
	hoaSimpleTextIR(char* buff, size_t size) :hoaIR(buff, size) {};
	void store(int& i) override;
	void store(double& d) override;
};
