#pragma once
#include <string>

class hoaSimpleTextIRW {
public:
	void store(int& i) override;
	void store(double& d) override;

private:
	std::string mStr;
};
