#pragma once
#include <string>
#include "hoaReaderWriter/hoaIRW.h"

class hoaSimpleTextIW : public hoaIW {
public:
	void store(int& i) override;
	void store(double& d) override;
	std::vector<char> get() override;

private:
	std::string mStr;
};
